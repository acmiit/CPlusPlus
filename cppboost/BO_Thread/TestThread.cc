#include <iostream>
#include <memory>
#include "Thread.h"
#include <unistd.h>
using namespace std;
class MyTask
{
public:
    void process(int x)
    {
        while (1)
        {
            cout << "Mytask is running!" << endl;
            sleep(1);
        }
    }
};
void test()
{
    MyTask task;
    Thread thd(std::bind(&MyTask::process, &task, 1)); //绑定两个参数，this和x
    thd.start();
    thd.stop();
}
void test2(){
    MyTask task;
    unique_ptr<Thread> up(new Thread(bind(&MyTask::process,&task,1)));
    up->start();
    up->stop();
}
int main()
{
    test2();
    return 0;
}