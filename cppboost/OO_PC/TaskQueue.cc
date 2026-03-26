#include"TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_que()
,_mutex()
,_notfull(_mutex)
,_notempty(_mutex)
{

}
TaskQueue::~TaskQueue(){

}
void TaskQueue::push(int value){
    _mutex.lock();
    if(full()){
        _notfull.wait();
    }
    _que.push(value);
    _notempty.notify();
    _mutex.unlock();
}
int TaskQueue::pop(){
    _mutex.lock();
    if(empty()){
        _notempty.wait();
    }
    int tmp=_que.front();
    _que.pop();
    _notfull.notify();
    _mutex.unlock();
    return tmp;
}
bool TaskQueue::full() const{
    return _que.size()==_queSize;
}
bool TaskQueue::empty() const{
    return _que.size()==0;
}