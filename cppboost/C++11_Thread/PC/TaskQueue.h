#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include <queue>
#include <mutex>
#include<condition_variable>
using std::mutex;
using std::condition_variable;
using std::unique_lock;
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
    mutex _mutex;
    condition_variable _notfull;
    condition_variable _notempty;
};
#endif //__TASKQUEUE_H__