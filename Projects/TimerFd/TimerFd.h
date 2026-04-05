#ifndef __TIMERFD_H__
#define __TIMERFD_H__
#include <functional>
#include<sys/timerfd.h>
using std::function;
using TimerFdCallback = function<void()>;
class TimerFd
{
public:
    TimerFd(TimerFdCallback &&cb,int initSec,int peidocSec);
    ~TimerFd();
    void start();
    void stop();
    

private:
    void handleRead();
    int createTimerFd();
    void setTimer(int initSec,int peidocSec);
private:
    int _tfd;
    TimerFdCallback _cb;
    bool _isStarted;
    int _initSec;
    int _peidocSec;
};

#endif //__TIMERFD_H__