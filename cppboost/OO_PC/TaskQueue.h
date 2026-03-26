#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include <pthread.h>
#include <queue>
#include"MutexLock.h"
#include"Condition.h"
class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    void push(int value);
    int pop();
    bool full() const;
    bool empty() const;
private:
    size_t _queSize;
    std::queue<int> _que;
    MutexLock _mutex;
    Condition _notfull;
    Condition _notempty;
};
#endif //__TASKQUEUE_H__