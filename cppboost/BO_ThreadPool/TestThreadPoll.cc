#include"ThreadPool.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;
class MyTask
{
public:
    void process()
    {
        ::srand(::clock());          // 种随机种子
        int random = ::rand() % 100; // 随机数
        cout<<">>BO_MyTask random= "<<random<<endl;
        // sleep(1);
    }
};
void test()
{
    unique_ptr<MyTask> ptask(new MyTask());
    ThreadPool pool(4,10);
    pool.start();
    int cnt=20;
    while(cnt){
        cnt--;
        pool.addTask(bind(&MyTask::process,ptask.get()));
        cout<<"<<cnt= "<<cnt<<endl;
    }
    pool.stop();
}
int main()
{
    test();
    return 0;
}