#ifndef __CONSUMER_H__
#define __CONSUMER_H__
#include "Thread.h"
class TaskQueue;
class Consumer
{
public:
    Consumer() = default;
    ~Consumer();
    void run(TaskQueue &taskQue);

private:
};

#endif //__CONSUMER_H__