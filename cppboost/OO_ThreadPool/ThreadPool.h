#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include <cstddef>
#include <vector>
#include <memory>
#include "TaskQueue.h"
class Thread;
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
    std::vector<std::unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};
#endif //__THREADPOOL_H__