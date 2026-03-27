#include "TaskQueue.h"
#include "Producer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
Producer::~Producer()
{
}
void Producer::run(TaskQueue &taskQue)
{
    // 匿名空间。表示这几个是C语言函数
    ::srand(::clock()); // 种随机种子
    while (1)
    {
        int random = ::rand() % 100; // 随机数
        taskQue.push(random);
        sleep(1);
    }
}