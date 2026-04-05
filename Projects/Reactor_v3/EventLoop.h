#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include <vector>
#include <map>
#include <memory>
#include <functional>

using std::function;
using std::map;
using std::shared_ptr;
using std::vector;
class Acceptor;
class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
class EventLoop
{
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();
    // 循环与否
    void loop();
    void unloop();
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setNewMessageCallback(TcpConnectionCallback &&cb);
    void setNewCloseCallback(TcpConnectionCallback &&cb);
private:
    // 封装类epoll_wait函数
    void waitEpollFd();
    // 处理新的连接
    void handleNewConncetion();
    // 处理消息
    void handleMessage(int fd);
    // epfd的创建
    int createEpollFd();
    // 监听文件描述符
    void addEpollReadFd(int fd);
    // 取消文件描述符的监听
    void delEpollReadFd(int fd);



private:
    int _epfd;                           // epoll_create 创建的文件描述符
    vector<struct epoll_event> _evtList; // 存放满足条件的文件描述符的数据结构
    bool _isLooping;                     // 表示循环是否咋爱运行的标志
    Acceptor &_acceptor;                 // 因为需要条用其中的accept函数
    map<int, TcpConnectionPtr> _conns;   // 存放的是文件描述符与连接的键值对

    TcpConnectionCallback _onNewConnectCb; // 连接建立
    TcpConnectionCallback _onCloseCb;      // 连接断开
    TcpConnectionCallback _onMessageCb;    // 消息到达
};

#endif //__EVENTLOOP_H__