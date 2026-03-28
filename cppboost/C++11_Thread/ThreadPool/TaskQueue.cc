#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
    : _queSize(queSize), _que(), _mutex(), _notfull(), _notempty(),flag(true)
{
}
TaskQueue::~TaskQueue()
{
}
void TaskQueue::push(ElemTpye ptask)
{
    // 利用ARII技术实现自动解锁
    std::unique_lock<std::mutex> autoLock(_mutex);
    // _mutex.lock();
    while (full())
    {
        _notfull.wait(autoLock);
    }
    _que.push(ptask);
    _notempty.notify_one();
    // _mutex.unlock();
}
ElemTpye TaskQueue::pop()
{
    ElemTpye tmp;
    //大括号让ARII的作用域缩小，让加锁的作用域最小
    {
        // 利用ARII技术实现自动解锁
        std::unique_lock<std::mutex> autoLock(_mutex);
        // _mutex.lock();
        //pthread_signal 会唤醒至少一个，存在虚假唤醒，需要使用while
        while (empty()&&flag) 
        {
            _notempty.wait(autoLock);
        }
        if(flag){
            tmp = _que.front();
            _que.pop();
            _notfull.notify_one();
            // _mutex.unlock();
            return tmp;
        }else{
            return nullptr;
        }

    }


}
void TaskQueue::wakeup(){
    flag=false;
    _notempty.notify_all();
}
bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}