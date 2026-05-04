#include "scheduler.h"

static bool debug = true;

namespace sylar {

static thread_local Scheduler* t_scheduler = nullptr;
static thread_local int t_threadIndex = -1;

Scheduler* Scheduler::GetThis()
{
	return t_scheduler;
}

void Scheduler::SetThis()
{
	t_scheduler = this;
}

int Scheduler::getThreadIndex()
{
	if (t_threadIndex >= 0) {
		return t_threadIndex;
	}
	for (size_t i = 0; i < m_threadIds.size(); i++) {
		if (m_threadIds[i] == Thread::GetThreadId()) {
			t_threadIndex = i;
			return t_threadIndex;
		}
	}
	return -1;
}

Scheduler::Scheduler(size_t threads, bool use_caller, const std::string &name):
m_useCaller(use_caller), m_name(name)
{
	assert(threads>0 && Scheduler::GetThis()==nullptr);

	Thread::SetName(m_name);

	if(use_caller)
	{
		threads--;

		SetThis();

		Fiber::GetThis();

		m_schedulerFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, false));
		Fiber::SetSchedulerFiber(m_schedulerFiber.get());

		m_rootThread = Thread::GetThreadId();
		m_threadIds.push_back(m_rootThread);
	}

	m_threadCount = threads;
	m_localQueues.resize(threads + 1);

	if(debug) std::cout << "Scheduler::Scheduler() success\n";
}

Scheduler::~Scheduler()
{
	assert(stopping()==true);
	if (GetThis() == this)
	{
		t_scheduler = nullptr;
	}
	if(debug) std::cout << "Scheduler::~Scheduler() success\n";
}

void Scheduler::start()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if(m_stopping)
	{
		std::cerr << "Scheduler is stopped" << std::endl;
		return;
	}

	assert(m_threads.empty());
	m_threads.resize(m_threadCount);
	for(size_t i=0;i<m_threadCount;i++)
	{
		m_threads[i].reset(new Thread(std::bind(&Scheduler::run, this), m_name + "_" + std::to_string(i)));
		m_threadIds.push_back(m_threads[i]->getId());
	}
	if(debug) std::cout << "Scheduler::start() success\n";
}

void Scheduler::run()
{
	int thread_id = Thread::GetThreadId();
	if(debug) std::cout << "Scheduler::run() starts in thread: " << thread_id << std::endl;

	SetThis();

	if(thread_id != m_rootThread)
	{
		Fiber::GetThis();
	}

	if(debug) std::cout << "Scheduler::run() thread " << thread_id << " before idle_fiber creation" << std::endl;

	std::shared_ptr<Fiber> idle_fiber = std::make_shared<Fiber>(std::bind(&Scheduler::idle, this));

	if(debug) std::cout << "Scheduler::run() thread " << thread_id << " idle_fiber created, state=" << idle_fiber->getState() << std::endl;

	ScheduleTask task;

	while(true)
	{
		task.reset();
		bool tickle_me = false;

		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (!m_globalQueue.empty()) {
				tickle_me = true;
			}
		}

		if(tickle_me)
		{
			tickle();
		}

		task = popFromLocal();

		if (!task.isValid()) {
			auto stolen = stealFromGlobal(50);
			if (!stolen.empty()) {
				task = stolen.front();
				stolen.pop_front();

				int curIdx = getThreadIndex();
				if(debug) std::cout << "Scheduler::run() thread " << thread_id << " stole " << stolen.size() << " tasks, curIdx=" << curIdx << std::endl;
				for (auto& t : stolen) {
					if (curIdx >= 0) {
						m_localQueues[curIdx].push_back(t);
					}
				}
			}
		}

		if (!task.isValid()) {
			if (idle_fiber->getState() == Fiber::TERM)
			{
				if(debug) std::cout << "Scheduler::run() ends in thread: " << thread_id << std::endl;
				break;
			}
			m_idleThreadCount++;
			idle_fiber->resume();
			m_idleThreadCount--;
			continue;
		}

		m_activeThreadCount++;

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
			if(debug) std::cout << "Scheduler::run() thread " << thread_id << " executing cb task" << std::endl;
			std::shared_ptr<Fiber> cb_fiber = std::make_shared<Fiber>(task.cb);
			{
				std::lock_guard<std::mutex> lock(cb_fiber->m_mutex);
				cb_fiber->resume();
			}
			if(debug) std::cout << "Scheduler::run() thread " << thread_id << " returned from cb_fiber->resume()" << std::endl;
			m_activeThreadCount--;
			task.reset();
		}
	}

}

void Scheduler::stop()
{
	if(debug) std::cout << "Scheduler::stop() starts in thread: " << Thread::GetThreadId() << std::endl;

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

	for (size_t i = 0; i < m_threadCount; i++)
	{
		tickle();
	}

	if (m_schedulerFiber)
	{
		tickle();
	}

	if(m_schedulerFiber)
	{
		m_schedulerFiber->resume();
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
	if(debug) std::cout << "Scheduler::stop() ends in thread:" << Thread::GetThreadId() << std::endl;
}

void Scheduler::tickle()
{
	if(debug) std::cout << "Scheduler::tickle()\n";
}

bool Scheduler::stopping()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_stopping && m_globalQueue.empty() && m_activeThreadCount == 0;
}

Scheduler::ScheduleTask Scheduler::popFromLocal()
{
	int idx = getThreadIndex();
	if (idx < 0) {
		return ScheduleTask();
	}

	auto& queue = m_localQueues[idx];
	if (!queue.empty()) {
		ScheduleTask task = queue.front();
		queue.pop_front();
		return task;
	}
	return ScheduleTask();
}

std::list<Scheduler::ScheduleTask> Scheduler::stealFromGlobal(int count)
{
	std::list<ScheduleTask> result;

	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_globalQueue.empty()) {
		return result;
	}

	int stealCount = std::min(count, (int)(m_globalQueue.size() / 2));
	if (stealCount == 0 && !m_globalQueue.empty()) {
		stealCount = 1;
	}

	for (int i = 0; i < stealCount; i++) {
		result.push_back(m_globalQueue.front());
		m_globalQueue.pop_front();
	}

	return result;
}

void Scheduler::idle()
{
	while(!stopping())
	{
		if(debug) std::cout << "Scheduler::idle(), sleeping in thread: " << Thread::GetThreadId() << std::endl;
		if(debug) std::cout << "Scheduler::idle() about to sleep(1)" << std::endl;
		sleep(1);
		if(debug) std::cout << "Scheduler::idle() about to Fiber::GetThis()->yield()" << std::endl;
		Fiber::GetThis()->yield();
		if(debug) std::cout << "Scheduler::idle() returned from yield()" << std::endl;
	}
}

}