#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
EventLoop::EventLoop(Acceptor &acceptor)
    : _epfd(createEpollFd()), _evtList(1024), _isLooping(false), _acceptor(acceptor)
{
    // 将listenfd放在红黑树上监听
    int listenfd = _acceptor.fd();
    addEpollReadFd(listenfd);
}
EventLoop::~EventLoop()
{
    close(_epfd);
}
// 循环与否
void EventLoop::loop()
{
    _isLooping = true;
    while (_isLooping)
    {
        waitEpollFd();
    }
}
void EventLoop::unloop()
{
    _isLooping = false;
}
// 封装类epoll_wait函数
void EventLoop::waitEpollFd()
{
    int readyNum = 0;
    do
    {
        readyNum = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000); //3秒
    } while (-1 == readyNum && errno == EINTR);
    if (-1 == readyNum)
    {
        cerr << "-1==readyNum" << endl;
    }
    else if (0 == readyNum)
    {
        cout << ">>epoll_wait timeout" << endl;
    }
    else
    {
        // 可以判断一下，文件描述符是不是已经达到了1024
        // 如果达到1024就需要进行扩容
        if (readyNum == (int)_evtList.size())
        {
            _evtList.reserve(2 * readyNum);
        }

        for (int idx = 0; idx < readyNum; ++idx)
        {
            int fd = _evtList[idx].data.fd;
            if (fd == _acceptor.fd())
            {
                if (_evtList[idx].events & EPOLLIN)
                {
                    // 处理新的连接
                    handleNewConncetion();
                }
            }
            else
            {
                if (_evtList[idx].events & EPOLLIN)
                {
                    // 处理老的连接
                    handleMessage(fd);
                }
            }
        }
    }
}
// 处理新的连接
void EventLoop::handleNewConncetion()
{
    int connfd = _acceptor.accept();
    if (connfd < 0)
    {
        perror("handleNewConncetion accept");
        return;
    }
    addEpollReadFd(connfd);
    // 就表明三次握手已经建立成功
    TcpConnectionPtr con(new TcpConnection(connfd));

    // 将三个回调函数注册给TcpConnection
    con->setNewConnectionCallback(_onNewConnectCb);
    con->setMessageCallback(_onMessageCb);
    con->setCloseCallback(_onCloseCb);

    // 以键值对的形式存起来
    //  _conns.insert(std::make_pair(connfd,con));
    _conns[connfd] = con;

    con->handleNewConnectionCallback();
}
// 处理消息
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if (it != _conns.end())
    {
        // 连接是存在的，可以进行数据的收发
        bool flag = it->second->isClosed();
        if (flag)
        {
            it->second->handleCloseCallback();
            delEpollReadFd(fd); //将文件描述符从红黑树中删除
            _conns.erase(it);   //同时将该链接从map中删除
        }
        else
        {
            it->second->handleMessageCallback();
        }
    }
    else
    {
        // 连接不存在，可以直接让程序退出来
        cout << "连接不存在" << endl;
    }
}
// epfd的创建
int EventLoop::createEpollFd()
{
    // int fd=epoll_create1(0);
    int fd = epoll_create(100);
    if (fd < 0)
    {
        perror("epoll_create1");
        return fd;
    }
    else
    {
        return fd;
    }
}
// 监听文件描述符
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
    if (ret < 0)
    {
        perror("epoll_ctl add");
        return;
    }
}
// 取消文件描述符的监听
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &ev);
    if (ret < 0)
    {
        perror("epoll_ctl del");
        return;
    }
}
void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onNewConnectCb = std::move(cb);
}
void EventLoop::setNewMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessageCb = std::move(cb);
}
void EventLoop::setNewCloseCallback(TcpConnectionCallback &&cb)
{
    _onCloseCb = std::move(cb);
}
