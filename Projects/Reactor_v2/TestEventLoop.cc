#include"EventLoop.h"
#include"Acceptor.h"
#include"TcpConnection.h"
#include<iostream>

using std::cout;
using std::endl;

void onNewConnection(const TcpConnectionPtr &con){
    cout<<con->toString()<<"has connected"<<endl;
}
void onMessage(const TcpConnectionPtr &con){
    string msg=con->receive();
    cout<<">>recv client msg="<<msg<<endl;

    con->send(msg);
}
void onClose(const TcpConnectionPtr &con){
    cout<<con->toString()<<"has closed"<<endl;
    
}
void test(){
    Acceptor acceptor("172.22.195.222",8888);
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.setNewConnectionCallback(std::move(onNewConnection));
    loop.setNewMessageCallback(std::move(onMessage));
    loop.setNewCloseCallback(std::move(onClose));

    loop.loop();
}
int main(){
    test();

    return 0;
}