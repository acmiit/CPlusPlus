#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
    : _queSize(queSize), _que(), _mutex(), _notfull(_mutex), _notempty(_mutex),flag(true)
{
}
TaskQueue::~TaskQueue()
{
}
void TaskQueue::push(ElemTpye ptask)
{
    // 利用ARII技术实现自动解锁
    MutexLockGuard autoLock(_mutex);
    // _mutex.lock();
    while (full())
    {
        _notfull.wait();
    }
    _que.push(ptask);
    _notempty.notify();
    // _mutex.unlock();
}
ElemTpye TaskQueue::pop()
{
    ElemTpye tmp;
    //大括号让ARII的作用域缩小，让加锁的作用域最小
    {
        // 利用ARII技术实现自动解锁
        MutexLockGuard autoLock(_mutex);
        // _mutex.lock();
        //pthread_signal 会唤醒至少一个，存在虚假唤醒，需要使用while
        while (empty()&&flag) 
        {
            _notempty.wait();
        }
        if(flag){
            tmp = _que.front();
            _que.pop();
            _notfull.notify();
            // _mutex.unlock();
            return tmp;
        }else{
            return nullptr;
        }

    }


}
void TaskQueue::wakeup(){
    flag=false;
    _notempty.notifyALL();
}
bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}