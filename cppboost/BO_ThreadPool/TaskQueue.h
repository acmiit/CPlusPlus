#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include <pthread.h>
#include <queue>
#include<functional>
#include "MutexLock.h"
#include "Condition.h"
using ElemTpye =std::function<void()>;
class TaskQueue
{

public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    void push(ElemTpye &&task);
    ElemTpye pop();
    void wakeup();
    bool full() const;
    bool empty() const;

private:
    size_t _queSize;
    std::queue<ElemTpye> _que;
    MutexLock _mutex;
    Condition _notfull;
    Condition _notempty;
    bool flag;
};
#endif //__TASKQUEUE_H__