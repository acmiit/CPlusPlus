#include "TcpServer.h"

TcpServer::TcpServer(const string &ip, unsigned short port)
    : _acceptor(ip, port), _loop(_acceptor)
{
}
TcpServer::~TcpServer()
{
}
void TcpServer::start()
{
    _acceptor.ready();
    _loop.loop();
}
void TcpServer::stop(){
    _loop.unloop();
}
void TcpServer::setAllCallback(TcpConnectionCallback &&cb1, TcpConnectionCallback &&cb2, TcpConnectionCallback &&cb3){
    _loop.setNewConnectionCallback(std::move(cb1));
    _loop.setNewMessageCallback(std::move(cb2));
    _loop.setNewCloseCallback(std::move(cb3));
}