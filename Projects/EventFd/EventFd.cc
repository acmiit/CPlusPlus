#include"EventFd.h"
#include <unistd.h>
#include<sys/eventfd.h>
#include<poll.h>
#include<iostream>
using std::cout;
using std::endl;
EventFd::EventFd(EventFdCallback &&cb)
:_evtfd(createEventFd())
,_cb(std::move(cb))
,_isStarted(false)
{

}
EventFd::~EventFd(){
    close(_evtfd);
}
void EventFd::start(){
    _isStarted=true;
    struct pollfd pfd;
    pfd.fd=_evtfd;
    pfd.events=POLLIN;
    while(_isStarted){
        int nready=poll(&pfd,1,3000);
        if(-1==nready&&errno==EINTR){
            continue;
        }else if(-1 == nready){
            perror("-1==nready");
            return ;
        }else if(0==nready){
           cout<<">>poll time_out!!!"<<endl;
        }else{
            if(pfd.revents&POLLIN){
                handleRead();
                if(_cb){
                    _cb();
                }
            }
        }
    }
}
void EventFd::stop(){
    _isStarted=false;
}
void EventFd::wakeup(){
    uint64_t one=1;
    ssize_t ret = write(_evtfd,&one,sizeof(uint64_t));
    if(ret!=sizeof(uint64_t)){
        perror("write");
        return ;
    }
}

void EventFd::handleRead(){
    uint64_t two;
    ssize_t ret = read(_evtfd,&two,sizeof(uint64_t));
    if(ret!=sizeof(uint64_t)){
        perror("read");
        return ;
    }
}
int EventFd::createEventFd(){
    int fd=eventfd(10,0);
    if(fd<0){
        perror("eventfd");
        return fd;
    }
    return fd;
}