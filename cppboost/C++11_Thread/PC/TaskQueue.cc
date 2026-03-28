#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
    : _queSize(queSize), _que(), _mutex(), _notfull(), _notempty()
{
}
TaskQueue::~TaskQueue()
{
}
void TaskQueue::push(int value)
{
    unique_lock<mutex> autoLock(_mutex);
    while (full())
    {
        _notfull.wait(autoLock);
    }
    _que.push(value);
    _notempty.notify_one();
    // _mutex.unlock();
}
int TaskQueue::pop()
{
    int tmp = 0;
    //大括号让ARII的作用域缩小，让加锁的作用域最小
    {
        // 利用ARII技术实现自动解锁
        unique_lock<mutex> autoLock(_mutex);
        // _mutex.lock();
        //pthread_signal 会唤醒至少一个，存在虚假唤醒，需要使用while
        while (empty()) 
        {
            _notempty.wait(autoLock);
        }
        tmp = _que.front();
        _que.pop();
        _notfull.notify_one();
        // _mutex.unlock();
    }

    return tmp;
}
bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}