#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

//#include "hook.h"
#include "fiber.h"
#include "thread.h"

#include <mutex>
#include <vector>
#include <string>
namespace sylar {

//协程调度器类
class Scheduler
{
public:
	//threads指定线程池的线程数量，use_caller指定是否主线程为工作线程，name调度器名称
	Scheduler(size_t threads = 1, bool use_caller = true, const std::string& name="Scheduler");
	virtual ~Scheduler();	//资源释放
	
	const std::string& getName() const {return m_name;}	//获取调度器名称

public:	
	// 获取正在运行的调度器
	static Scheduler* GetThis();

protected:
	// 设置正在运行的调度器
	void SetThis();
	
public:	
	// 添加任务到任务队列
	//FiberOrCb调度任务类型，可以是协程对象或函数指针
    template <class FiberOrCb>
    void scheduleLock(FiberOrCb fc, int thread = -1) 
    {
    	bool need_tickle; //用于标记任务队列是否为空， 从而判断是否需要唤醒线程 ，原子操作（互斥锁）
    	{
    		std::lock_guard<std::mutex> lock(m_mutex); //会自动释放
    		// empty ->  all thread is idle -> need to be waken up
    		need_tickle = m_tasks.empty();
	        //创建Task的任务对象
	        ScheduleTask task(fc, thread);
	        if (task.fiber || task.cb) //存在就加入任务队列中
	        {
	            m_tasks.push_back(task);
	        }
    	}
    	
    	if(need_tickle) //如果任务队列为空， 则需要唤醒线程
    	{
    		tickle();
    	}
    }
	
	// 启动线程池
	virtual void start();
	// 关闭线程池，停止调度器，等所有调度任务都执行完之后在返回
	virtual void stop();	
	
protected:
	virtual void tickle(); //唤醒线程
	
	// 线程函数
	virtual void run();

	// 空闲协程函数，没有任务调度时候执行idle协程
	virtual void idle();
	
	// 是否可以关闭
	virtual bool stopping();

	//返回是否有空闲线程
	//当调度协程进入idle时空闲线程数+1，从idle协程返回时候空闲 线程数减1
	bool hasIdleThreads() {return m_idleThreadCount>0;}

private:
	// 任务
	struct ScheduleTask
	{
		std::shared_ptr<Fiber> fiber;
		std::function<void()> cb;
		int thread; // 指定任务需要运行的线程id

		ScheduleTask()
		{
			fiber = nullptr;
			cb = nullptr;
			thread = -1;
		}

		ScheduleTask(std::shared_ptr<Fiber> f, int thr)
		{
			fiber = f;
			thread = thr;
		}

		ScheduleTask(std::shared_ptr<Fiber>* f, int thr)
		{
			//将内容转移也就是指针内部的转移和上面的赋值不同，引用计数不会增加
			fiber.swap(*f);
			thread = thr;
		}	

		ScheduleTask(std::function<void()> f, int thr)
		{
			cb = f;
			thread = thr;
		}		

		ScheduleTask(std::function<void()>* f, int thr)
		{
			cb.swap(*f);
			thread = thr;
		}

		void reset()//重置
		{
			fiber = nullptr;
			cb = nullptr;
			thread = -1;
		}	
	};

private:
	std::string m_name; //调度器的名称
	// 互斥锁 -> 保护任务队列
	std::mutex m_mutex;
	// 线程池，存初始化好的线程
	std::vector<std::shared_ptr<Thread>> m_threads;
	// 任务队列
	std::vector<ScheduleTask> m_tasks;
	// 存储工作线程的线程id
	std::vector<int> m_threadIds;
	// 需要额外创建的线程数
	size_t m_threadCount = 0;
	// 活跃线程数
	//赋值好可以省略，m_activeThreadCount = 0; 统一初始化列表
	std::atomic<size_t> m_activeThreadCount = {0};
	// 空闲线程数
	std::atomic<size_t> m_idleThreadCount = {0};

	// 主线程是否用作工作线程
	bool m_useCaller;
	// 如果是 -> 需要额外创建调度协程
	std::shared_ptr<Fiber> m_schedulerFiber;
	// 如果是 -> 记录主线程的线程id
	int m_rootThread = -1;
	// 是否正在关闭
	bool m_stopping = false;	
};

}

#endif