#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <vector>
#include "TaskQueue.h"
#include<memory>
#include<thread>
class ThreadPool
{
public:
    friend class WorkThread;
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(Task *ptask);
    Task *getTask();

private:
    void doTask();

private:
    size_t _threadNum;
    size_t _queSize;
    std::vector<std::thread> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};
#endif //__THREADPOOL_H__