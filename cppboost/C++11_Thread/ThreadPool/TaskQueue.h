#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include <queue>
#include<mutex>
#include<condition_variable>
class Task;
using ElemTpye = Task *;
class TaskQueue
{

public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    void push(ElemTpye ptask);
    ElemTpye pop();
    void wakeup();
    bool full() const;
    bool empty() const;

private:
    size_t _queSize;
    std::queue<ElemTpye> _que;
    std::mutex _mutex;
    std::condition_variable _notfull;
    std::condition_variable _notempty;
    bool flag;
};
#endif //__TASKQUEUE_H__