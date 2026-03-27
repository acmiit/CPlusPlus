#include "TaskQueue.h"
#include "Consumer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<iostream>
Consumer::~Consumer()
{
}
void Consumer::run(TaskQueue &taskQue)
{
    while (1)
    {
        int value=taskQue.pop();
        std::cout<<"value="<<value<<std::endl;
        sleep(1);
    }
}