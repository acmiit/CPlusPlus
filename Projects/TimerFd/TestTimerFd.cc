#include"TimerFd.h"
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
    TimerFd tf(bind(&MyTask::process,&task),1,5);
    thread _th(&TimerFd::start,&tf);
    
    // int cnt=20;
    // while(cnt--){
    //     sleep(1);
    //     cout<<"cnt = "<<cnt<<endl;
    // }
    // cout<<"before stop"<<endl;
    tf.stop();
    // cout<<"after stop"<<endl;
    _th.join();
}
int main(int argc,char *argv[]){
    test();
    return 0;
}