#include "scheduler.h"

static bool debug = false;

namespace sylar {

static thread_local Scheduler* t_scheduler = nullptr;

Scheduler* Scheduler::GetThis()
{
	return t_scheduler;
}

void Scheduler::SetThis()
{
	t_scheduler = this;
}

Scheduler::Scheduler(size_t threads, bool use_caller, const std::string &name):
m_useCaller(use_caller), m_name(name)
{
	//判断线程池是否启动，调度器是不是还没有初始化（验证代码执行顺序）
	assert(threads>0 && Scheduler::GetThis()==nullptr);

	SetThis(); // 设置当前调度器对象

	Thread::SetName(m_name); //设置当前线程的名字为调度器的名称 m_name

	// 使用主线程当作工作线程,创建协程的主要原因是为了实现更高效的任务调度和管理
	if(use_caller)	//如果user_caller为true，表示当前线程也要作为一个工作线程使用
	{
		threads --; //因此线程数量减一

		// 创建主协程
		Fiber::GetThis();

		// 创建调度协程
		m_schedulerFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, false)); // false -> 该调度协程退出后将返回主协程
		Fiber::SetSchedulerFiber(m_schedulerFiber.get()); //设置协程的调度器对象
		m_rootThread = Thread::GetThreadId(); //获取主线程id
		m_threadIds.push_back(m_rootThread);
	}

	m_threadCount = threads;	//将剩余的线程数量（即总线程数量减去是否使用调用者线程）赋值给m_threadCount
	if(debug) std::cout << "Scheduler::Scheduler() success\n";
}

Scheduler::~Scheduler()
{
	assert(stopping()==true); //判断调度器是否以及停止
	if (GetThis() == this) 	//获取调度器对象
	{
        t_scheduler = nullptr; //将其设置为nullptr防止悬空指针
    }
    if(debug) std::cout << "Scheduler::~Scheduler() success\n";
}

//初始化调度线程池
void Scheduler::start()
{
	std::lock_guard<std::mutex> lock(m_mutex); //加锁
	if(m_stopping) //看调度器有没有关闭
	{
		std::cerr << "Scheduler is stopped" << std::endl;
		return;
	}

	assert(m_threads.empty()); //判断线程池是否为空
	m_threads.resize(m_threadCount); //重置线程池
	for(size_t i=0;i<m_threadCount;i++)
	{
		m_threads[i].reset(new Thread(std::bind(&Scheduler::run, this), m_name + "_" + std::to_string(i))); 
		m_threadIds.push_back(m_threads[i]->getId());
	}
	if(debug) std::cout << "Scheduler::start() success\n";
}

//调度器核心，负责从任务队列中取出任务并通过协程执行
void Scheduler::run()
{
	int thread_id = Thread::GetThreadId();
	if(debug) std::cout << "Schedule::run() starts in thread: " << thread_id << std::endl;
	
	// set_hook_enable(true);

	SetThis(); // 设置当前调度器对象

	// 运行在新创建的线程 -> 需要创建主协程
	if(thread_id != m_rootThread) //如果不是主线程，创建主协程
	{
		Fiber::GetThis(); //创建主协程 ，分配了线程的主协程和调度协程；创建了主协程当成调度协程用

	}
	//创建空闲协程，用于在没有任务时执行协程
	std::shared_ptr<Fiber> idle_fiber = std::make_shared<Fiber>(std::bind(&Scheduler::idle, this));
	ScheduleTask task;
	
	while(true)
	{
		task.reset(); //清空任务
		bool tickle_me = false; //是否唤醒了其他线程进行任务调度

		{
			std::lock_guard<std::mutex> lock(m_mutex);
			auto it = m_tasks.begin();
			// 1 遍历任务队列
			while(it!=m_tasks.end())
			{
				if(it->thread!=-1&&it->thread!=thread_id)
				{
					it++;
					tickle_me = true;
					continue;
				}

				// 2 取出任务
				assert(it->fiber||it->cb);
				task = *it;
				m_tasks.erase(it); 
				m_activeThreadCount++;
				break;
			}	
			tickle_me = tickle_me || (it != m_tasks.end());
		}

		if(tickle_me)
		{
			tickle();
		}

		// 3 执行任务
		if(task.fiber)
		{
			{					
				std::lock_guard<std::mutex> lock(task.fiber->m_mutex);
				if(task.fiber->getState()!=Fiber::TERM)
				{
					task.fiber->resume();	
				}
			}
			m_activeThreadCount--;
			task.reset();
		}
		else if(task.cb)
		{
			std::shared_ptr<Fiber> cb_fiber = std::make_shared<Fiber>(task.cb);
			{
				std::lock_guard<std::mutex> lock(cb_fiber->m_mutex);
				cb_fiber->resume();			
			}
			m_activeThreadCount--;
			task.reset();	
		}
		// 4 无任务 -> 执行空闲协程
		else
		{		
			// 系统关闭 -> idle协程将从死循环跳出并结束 -> 此时的idle协程状态为TERM -> 再次进入将跳出循环并退出run()
            if (idle_fiber->getState() == Fiber::TERM) 
            {
            	if(debug) std::cout << "Schedule::run() ends in thread: " << thread_id << std::endl;
                break;
            }
			m_idleThreadCount++;
			idle_fiber->resume();				
			m_idleThreadCount--;
		}
	}
	
}

void Scheduler::stop()
{
	if(debug) std::cout << "Schedule::stop() starts in thread: " << Thread::GetThreadId() << std::endl;
	
	if(stopping())
	{
		return;
	}

	m_stopping = true;	

    if (m_useCaller) 
    {
        assert(GetThis() == this);
    } 
    else 
    {
        assert(GetThis() != this);
    }
	//调用tickle()的目的唤醒空间线程或协程，防止m_scheduler或其他线程处于永久阻塞在等待任务的状态中
	for (size_t i = 0; i < m_threadCount; i++) 
	{
		tickle(); //唤醒空闲线程
	}

	if (m_schedulerFiber) 
	{
		tickle(); //唤醒可能处于挂起状态，等待下一个任务的调度的协程
	}
	//当只有主线程或调度线程作为工作线程的情况，只能从stop()方法开始任务调度
	if(m_schedulerFiber)
	{
		m_schedulerFiber->resume(); //开始执行调度协程
		if(debug) std::cout << "m_schedulerFiber ends in thread:" << Thread::GetThreadId() << std::endl;
	}

	std::vector<std::shared_ptr<Thread>> thrs;
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		thrs.swap(m_threads);
	}

	for(auto &i : thrs)
	{
		i->join();
	}
	if(debug) std::cout << "Schedule::stop() ends in thread:" << Thread::GetThreadId() << std::endl;
}

void Scheduler::tickle()
{
}

void Scheduler::idle()
{
	while(!stopping())
	{
		if(debug) std::cout << "Scheduler::idle(), sleeping in thread: " << Thread::GetThreadId() << std::endl;	
		sleep(1);	
		Fiber::GetThis()->yield();
	}
}

//判断调度器是否已经停止运行
bool Scheduler::stopping() 
{
	//访问共享资源需要加锁 ： 防止多个线程同时访问共享资源导致的不一致状态
	//共享资源：m_stopping（调度器是否停止运行，是一个标记bool,类似于flag）, m_tasks（任务队列vector<ScheduleTask>）， m_activeThreadCount（活跃线程数）
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_stopping && m_tasks.empty() && m_activeThreadCount == 0;
}


}