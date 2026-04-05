#ifndef __EVENTFD_H__
#define __EVENTFD_H__
#include <functional>
using std::function;
using EventFdCallback = function<void()>;
class EventFd
{
public:
    EventFd(EventFdCallback &&cb);
    ~EventFd();
    void start();
    void stop();
    void wakeup();

private:
    void handleRead();
    int createEventFd();

private:
    int _evtfd;
    EventFdCallback _cb;
    bool _isStarted;
};

#endif //__EVENTFD_H__