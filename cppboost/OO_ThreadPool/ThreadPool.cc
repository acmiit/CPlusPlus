#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"
#include <iostream>
#include <unistd.h>
ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    : _threadNum(threadNum), _queSize(queSize), _taskQue(_queSize), _isExit(false)
{
    // 预留空间
    _threads.reserve(_threadNum);
}
ThreadPool::~ThreadPool()
{
}
void ThreadPool::start()
{
    for (size_t idx = 0; idx != _threadNum; ++idx)
    {
        _threads.push_back(std::unique_ptr<Thread>(new WorkThread(*this)));
    }
    for (auto &th : _threads)
    {
        th->start();
    }
}
void ThreadPool::stop()
{
    //任务全部完成才退出
    while(!_taskQue.empty()){
        sleep(1);
    }
    _isExit=true;
    //回收之前将所有的工作线程唤醒
    _taskQue.wakeup(); 
    for (auto &th : _threads)
    {
        th->stop();
    }
}
void ThreadPool::addTask(Task *ptask)
{
    if (ptask)
    {
        _taskQue.push(ptask);
    }
}
Task *ThreadPool::getTask()
{
    return _taskQue.pop();
}

//用的是线程池是否退出的标志位？？？
//子线程（工作线程）在获取完任务之后，那么任务队列就为空
//接下来子线程会执行任务，也就是执行process函数，而主线程
//会执行stop函数将标志位_isExit设置为true。如果子线程执行
//process的速率非常慢，那么当子线程执行任务之前，主线程已
//经将标志位设置为了true，那么子线程就不会进入到while循环
//中，那么程序就可以正常结束；如果子线程执行任务process的
//速率非常的快，但是主线程还没有将标志位设置为true，那么子
//线程执行完process后，有进入了while循环中，在执行getTask
//的时候，也就会执行TaskQueue中的stop，然后睡眠
void ThreadPool::doTask()
{
    while (!_isExit)
    {
        Task *ptask = getTask();
        if (ptask)
        {
            ptask->process();
            // sleep(3); //process运行的时间大于stop中修改标志位的时间;
        }
        else
        {
            std::cout << "nullptr==ptask" << std::endl;
        }
    }
}