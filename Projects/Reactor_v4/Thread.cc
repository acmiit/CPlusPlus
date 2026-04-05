#include "Thread.h"
#include<stdio.h>
#include<iostream>
using namespace std;
Thread::Thread(ThreadCallback &&cb)
:_thid(0)
,_isRunning(false)
,_cb(std::move(cb))
{

}
Thread::~Thread(){
    if(_isRunning){
        stop();
    }
}
//线程启动
void Thread::start(){
    //threadFunc参数前面有一个隐藏的this指针，需要将threadFunc函数设置为static
    // int ret=pthread_create(&_thid,nullptr,threadFunc,nullptr);
    int ret=pthread_create(&_thid,nullptr,threadFunc,this);
    if(ret!=0){
        perror("pthread_create");
        return ;
    }
    _isRunning=true;
}
//线程停止
void Thread::stop(){
    if(_isRunning){
        int ret=pthread_join(_thid,nullptr);
        if(ret!=0){
            perror("pthread_join");
            return ;
        }
    }
    _isRunning=false;
}
//线程入口函数
void *Thread::threadFunc(void * arg){
    Thread *pth=static_cast<Thread *>(arg);
    if(pth){
        pth->_cb();
    }else{
        cout<<"nullptr==pth"<<endl;
    }
    return nullptr;
}