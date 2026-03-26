#ifndef __CONSUMER_H__
#define __CONSUMER_H__
#include"Thread.h"
class TaskQueue;
class Consumer
{
public:
Consumer(TaskQueue & taskQue);
    ~Consumer();
    void run();

private:
    TaskQueue &_taskQue;
};

#endif //__CONSUMER_H__