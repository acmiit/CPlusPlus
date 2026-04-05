#include"EventFd.h"
#include<iostream>
#include <functional>
#include <thread>
#include <unistd.h>
using std::cout;
using std::endl;
using std::function;
using std::bind;
using std::thread;

class MyTask{
public:
void process(){
    cout<<"MyTask is running!"<<endl;
}
};
void test(){
    MyTask task;
    EventFd ef(bind(&MyTask::process,&task));
    thread _th(&EventFd::start,&ef);
    
    int cnt=20;
    while(cnt--){
        ef.wakeup(); //主线程唤醒子线程，线程之间的通信
        sleep(1);
        cout<<"cnt = "<<cnt<<endl;
    }

    ef.stop();
    _th.join();
}
int main(int argc,char *argv[]){
    test();
    return 0;
}