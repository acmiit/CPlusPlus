#include "TimerFd.h"
#include <unistd.h>
#include <sys/eventfd.h>
#include <poll.h>
#include <iostream>
using std::cout;
using std::endl;
TimerFd::TimerFd(TimerFdCallback &&cb, int initSec, int peidocSec)
    : _tfd(createTimerFd()), _cb(std::move(cb)), _isStarted(false), _initSec(initSec), _peidocSec(peidocSec)
{
}
TimerFd::~TimerFd()
{
    setTimer(0, 0);
    close(_tfd);
}
void TimerFd::start()
{
    _isStarted = true;
    struct pollfd pfd;
    pfd.fd = _tfd;
    pfd.events = POLLIN;

    setTimer(_initSec, _peidocSec);
    while (_isStarted)
    {
        int nready = poll(&pfd, 1, 3000);
        if (-1 == nready && errno == EINTR)
        {
            continue;
        }
        else if (-1 == nready)
        {
            perror("-1==nready");
            return;
        }
        else if (0 == nready)
        {
            cout << ">>poll time_out!!!" << endl;
        }
        else
        {
            if (pfd.revents & POLLIN)
            {
                handleRead();
                if (_cb)
                {
                    _cb();
                }
            }
        }
    }
}
void TimerFd::stop()
{
    if (_isStarted)
    {
        _isStarted = false;
        setTimer(0, 0);
    }
}

void TimerFd::handleRead()
{
    uint64_t two;
    ssize_t ret = read(_tfd, &two, sizeof(uint64_t));
    if (ret != sizeof(uint64_t))
    {
        perror("read");
        return;
    }
}
int TimerFd::createTimerFd()
{
    // 第一个参数clockid：相对时间（CLOCK_REALTIME）、绝对时间（CLOCK_MONOTONIC）
    // 第二个参数flag：非阻塞（TFD_NONBLOCK）、TFD_CLOEXEC ,Linux版本大于2.6.26就为0
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if (fd < 0)
    {
        perror("timerfd_create");
        return fd;
    }
    return fd;
}
void TimerFd::setTimer(int initSec, int peidocSec)
{
    //value为0表示停止计时器
    struct itimerspec value;
    value.it_value.tv_sec=initSec;
    value.it_value.tv_nsec=0;

    value.it_interval.tv_sec=peidocSec;
    value.it_interval.tv_nsec=0;
    int ret=timerfd_settime(_tfd,0,&value,nullptr);
    if(ret){
        perror("timerfd_settime");
        return ;
    }
}