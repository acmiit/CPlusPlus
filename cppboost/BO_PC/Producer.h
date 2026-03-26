#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include"Thread.h"
class TaskQueue;
class Producer
{
public:
    Producer(TaskQueue & taskQue);
    ~Producer();
    void run();

private:
    TaskQueue &_taskQue;
};

#endif //__PRODUCER_H__