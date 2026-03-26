#include "TaskQueue.h"
#include "Consumer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<iostream>
Consumer::Consumer(TaskQueue &taskQue)
    : _taskQue(taskQue)
{
}
Consumer::~Consumer()
{
}
void Consumer::run()
{
    while (1)
    {
        int value=_taskQue.pop();
        std::cout<<"value="<<value<<std::endl;
        sleep(1);
    }
}