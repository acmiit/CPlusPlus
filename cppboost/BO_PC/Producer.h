#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include"Thread.h"
class TaskQueue;
class Producer
{
public:
    Producer()=default;
    ~Producer();
    void run(TaskQueue &taskQue);

private:
};

#endif //__PRODUCER_H__