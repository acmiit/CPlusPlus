#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "hook.h"
#include "fiber.h"
#include "thread.h"

#include <mutex>
#include <vector>
#include <list>

namespace sylar {

class Scheduler
{
public:
	Scheduler(size_t threads = 1, bool use_caller = true, const std::string& name="Scheduler");
	virtual ~Scheduler();

	const std::string& getName() const {return m_name;}

public:
	static Scheduler* GetThis();

protected:
	void SetThis();

public:
	template <class FiberOrCb>
	void scheduleLock(FiberOrCb fc, int thread = -1)
	{
		bool need_tickle;
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			need_tickle = m_globalQueue.empty();

			ScheduleTask task(fc, thread);
			if (task.fiber || task.cb)
			{
				m_globalQueue.push_back(task);
			}
		}

		if(need_tickle)
		{
			tickle();
		}
	}

	virtual void start();
	virtual void stop();

protected:
	virtual void tickle();
	virtual void run();
	virtual void idle();
	virtual bool stopping();

	bool hasIdleThreads() {return m_idleThreadCount>0;}

public:
	struct ScheduleTask
	{
		std::shared_ptr<Fiber> fiber;
		std::function<void()> cb;
		int thread;

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

		void reset()
		{
			fiber = nullptr;
			cb = nullptr;
			thread = -1;
		}

		bool isValid() const
		{
			return fiber || cb;
		}
	};

private:
	ScheduleTask popFromLocal();
	std::list<ScheduleTask> stealFromGlobal(int count);
	int getThreadIndex();

private:
	std::string m_name;
	std::mutex m_mutex;

	std::vector<std::shared_ptr<Thread>> m_threads;
	std::vector<int> m_threadIds;

	std::vector<std::list<ScheduleTask>> m_localQueues;
	std::list<ScheduleTask> m_globalQueue;

	size_t m_threadCount = 0;
	std::atomic<size_t> m_activeThreadCount = {0};
	std::atomic<size_t> m_idleThreadCount = {0};

	bool m_useCaller;
	std::shared_ptr<Fiber> m_schedulerFiber;
	int m_rootThread = -1;
	bool m_stopping = false;
};

}

#endif