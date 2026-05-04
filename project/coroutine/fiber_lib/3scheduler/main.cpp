#include "scheduler.h"

using namespace sylar;

static unsigned int test_number;
std::mutex mutex_cout;
void task()
{
	{
		std::lock_guard<std::mutex> lock(mutex_cout);
		std::cout << "task " << test_number ++ << " is under processing in thread: " << Thread::GetThreadId() << std::endl;		
	}
	sleep(1);
}

int main(int argc, char const *argv[])
{
	{
		// 创建调度器：3个工作线程，1个主线程=4个线程，主线程作为工作线程
		std::shared_ptr<Scheduler> scheduler = std::make_shared<Scheduler>(3, true, "scheduler_1");
		
		scheduler->start(); //创建3个工作线程

		sleep(2);

		std::cout << "\nbegin post\n\n"; 
		//添加五个任务
		for(int i=0;i<5;i++)
		{
			std::shared_ptr<Fiber> fiber = std::make_shared<Fiber>(task);
			scheduler->scheduleLock(fiber);
		}

		sleep(6);

		std::cout << "\npost again\n\n"; 
		//添加15个任务
		for(int i=0;i<15;i++)
		{
			std::shared_ptr<Fiber> fiber = std::make_shared<Fiber>(task);
			scheduler->scheduleLock(fiber);
		}		

		sleep(3);
		// scheduler如果有设置将加入工作处理
		scheduler->stop(); //关闭调度器，等所有调度任务都执行完之后在返回
	}
	return 0;
}