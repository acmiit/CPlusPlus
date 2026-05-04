#include "fiber.h"

static bool debug = false;

namespace sylar {

// 当前线程上的协程控制信息

// 正在运行的协程
static thread_local Fiber* t_fiber = nullptr;
// 主协程
static thread_local std::shared_ptr<Fiber> t_thread_fiber = nullptr;
// 调度协程
static thread_local Fiber* t_scheduler_fiber = nullptr;

// 全局协程 id 计数器
static std::atomic<uint64_t> s_fiber_id{0};
// 活跃协程数量计数器
static std::atomic<uint64_t> s_fiber_count{0};

void Fiber::SetThis(Fiber *f) //设置当前运行的协程
{
	t_fiber = f;
}

// 首先运行该函数创建主协程
// 得到当前运行的协程 
// 如果当前线程没有协程，创建一个主协程
// 如果当前线程有协程，返回当前协程
// 如果当前线程有主协程，返回主协程
std::shared_ptr<Fiber> Fiber::GetThis()
{
	if(t_fiber)
	{	
		return t_fiber->shared_from_this();
	}

	std::shared_ptr<Fiber> main_fiber(new Fiber());
	t_thread_fiber = main_fiber;
	t_scheduler_fiber = main_fiber.get(); // 除非主动设置 主协程默认为调度协程
	
	assert(t_fiber == main_fiber.get());
	return t_fiber->shared_from_this();
}

void Fiber::SetSchedulerFiber(Fiber* f) //设置调度协程
{
	t_scheduler_fiber = f;
}

uint64_t Fiber::GetFiberId()
{
	if(t_fiber)
	{
		return t_fiber->getId();
	}
	return (uint64_t)-1;
}
//构造线程主协程对象。设置状态，初始化上下文，并分配ID
Fiber::Fiber()
{
	SetThis(this); //在getThis中使用了无参的FIber来构建t_fiber
	m_state = RUNNING;	//设置协程的状态为可运行
	
	if(getcontext(&m_ctx))
	{
		std::cerr << "Fiber() failed\n";
		pthread_exit(NULL);
	}
	
	m_id = s_fiber_id++; //协程id从0开始，用完加1
	s_fiber_count ++; //活跃协程数量加1
	if(debug) std::cout << "Fiber(): main id = " << m_id << std::endl;
}

//构造⼦协程对象 sylar采取的是独⽴栈的形式，每个协程都⾃⼰固定⼤⼩的栈空间
// cb 协程函数 协程入口函数
// stacksize 栈大小 默认大小为128KB
// run_in_scheduler 是否在调度协程中运行
// 默认在调度协程中运行
// 如果在调度协程中运行，协程函数必须在调度协程中调用resume()函数
// 如果不在调度协程中运行，协程函数必须在当前线程中调用resume()函数
Fiber::Fiber(std::function<void()> cb, size_t stacksize, bool run_in_scheduler):
m_cb(cb), m_runInScheduler(run_in_scheduler)
{
	m_state = READY; //初始化状态

	// 分配协程栈空间
	m_stacksize = stacksize ? stacksize : 128000;
	m_stack = malloc(m_stacksize);

	if(getcontext(&m_ctx))
	{
		std::cerr << "Fiber(std::function<void()> cb, size_t stacksize, bool run_in_scheduler) failed\n";
		pthread_exit(NULL);
	}
	
	m_ctx.uc_link = nullptr; //设置上下文链接为nullptr，表示当前协程没有前一个协程，运行完mainfunc后协程退出，会调用一次yield返回主协程
	m_ctx.uc_stack.ss_sp = m_stack;
	m_ctx.uc_stack.ss_size = m_stacksize;
	makecontext(&m_ctx, &Fiber::MainFunc, 0);
	
	m_id = s_fiber_id++;
	s_fiber_count ++;
	if(debug) std::cout << "Fiber(): child id = " << m_id << std::endl;
}

Fiber::~Fiber()
{
	s_fiber_count --;	//活跃协程数量减1
	if(m_stack)
	{
		free(m_stack);
	}else{
		assert(m_state==RUNNING);
		Fiber *cur=t_fiber; //此时运行的肯定是主协程
		if(cur==this){
			SetThis(nullptr);
		}
	}
	if(debug) std::cout << "~Fiber(): id = " << m_id << std::endl;	
}
//这⾥为了简化状态管理，强制只有TERM状态的协程才可以重置，但其实刚创建好但没执⾏过的协程也应该允许重置的
void Fiber::reset(std::function<void()> cb)
{
	assert(m_stack != nullptr&&m_state == TERM);

	m_state = READY;
	m_cb = cb;

	if(getcontext(&m_ctx))
	{
		std::cerr << "reset() failed\n";
		pthread_exit(NULL);
	}

	m_ctx.uc_link = nullptr;
	m_ctx.uc_stack.ss_sp = m_stack;
	m_ctx.uc_stack.ss_size = m_stacksize;
	makecontext(&m_ctx, &Fiber::MainFunc, 0);
}

//将当前协程切换到执行状态
// 如果当前协程状态不是READY，直接返回
// 如果当前协程状态是READY，切换到执行状态
void Fiber::resume()
{
	assert(m_state==READY);
	
	m_state = RUNNING;

	if(m_runInScheduler)
	{
		SetThis(this);
		if(swapcontext(&(t_scheduler_fiber->m_ctx), &m_ctx))
		{
			std::cerr << "resume() to t_scheduler_fiber failed\n";
			pthread_exit(NULL);
		}		
	}
	else
	{
		SetThis(this);
		if(swapcontext(&(t_thread_fiber->m_ctx), &m_ctx))
		{
			std::cerr << "resume() to t_thread_fiber failed\n";
			pthread_exit(NULL);
		}	
	}
}

//当前协程让出执行权给其他协程
// 如果当前协程状态不是RUNNING或TERM，直接返回
// 如果当前协程状态是RUNNING，切换到READY状态
void Fiber::yield()
{
	assert(m_state==RUNNING || m_state==TERM);

	if(m_state!=TERM)
	{
		m_state = READY;
	}

	if(m_runInScheduler)
	{
		SetThis(t_scheduler_fiber);
		if(swapcontext(&m_ctx, &(t_scheduler_fiber->m_ctx)))
		{
			std::cerr << "yield() to to t_scheduler_fiber failed\n";
			pthread_exit(NULL);
		}		
	}
	else
	{
		SetThis(t_thread_fiber.get());
		if(swapcontext(&m_ctx, &(t_thread_fiber->m_ctx)))
		{
			std::cerr << "yield() to t_thread_fiber failed\n";
			pthread_exit(NULL);
		}	
	}	
}

//协程入口函数
// 协程函数必须在当前协程中调用resume()函数
// 协程函数必须在当前协程中调用yield()函数让出执行权
//这⾥没有处理协程函数出现异常的情况，同样是为了简化状态管理，并且个⼈认为协程的异常不应该由框架处理，应该由开发者⾃⾏处理
void Fiber::MainFunc()
{
	std::shared_ptr<Fiber> curr = GetThis(); //GetThis()的shared_from_this()⽅法让引⽤计数加1
	assert(curr!=nullptr);

	curr->m_cb();  // 这⾥真正执⾏协程的⼊⼝函数
	curr->m_cb = nullptr;
	curr->m_state = TERM;

	// 运行完毕 -> 让出执行权
	auto raw_ptr = curr.get();  // ⼿动让t_fiber的引⽤计数减1
	curr.reset(); 
	raw_ptr->yield();   // 协程结束时⾃动yield，以回到主协程
}

}