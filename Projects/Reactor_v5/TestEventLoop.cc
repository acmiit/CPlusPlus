#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include"EchoServer.h"
#include <iostream>

using std::cout;
using std::endl;

// ThreadPool *gPool=nullptr;
// class MyTask
// {
// public:
//     MyTask(const string &msg, TcpConnectionPtr con)
//         : _msg(msg), _con(con)
//     {
//     }
//     void process()
//     {
//     }

// private:
//     string _msg;
//     TcpConnectionPtr _con;
// };

// void onNewConnection(const TcpConnectionPtr &con)
// {
//     cout << con->toString() << "has connected" << endl;
// }
// void onMessage(const TcpConnectionPtr &con)
// {
//     string msg = con->receive();
//     cout << ">>recv client msg=" << msg << endl;

//     MyTask task(msg,con);
//     gPool->addTask(std::bind(&MyTask::process,task));

//     con->send(msg);
// }
// void onClose(const TcpConnectionPtr &con)
// {
//     cout << con->toString() << "has closed" << endl;
// }
// void test()
// {
//     Acceptor acceptor("172.22.195.222", 8888);
//     acceptor.ready();

//     EventLoop loop(acceptor);
//     loop.setNewConnectionCallback(std::move(onNewConnection));
//     loop.setNewMessageCallback(std::move(onMessage));
//     loop.setNewCloseCallback(std::move(onClose));

//     loop.loop();
// }
// void test1()
// {
//     TcpServer server("172.22.195.222", 8888);
//     server.setAllCallback(std::move(onNewConnection), std::move(onMessage), std::move(onClose));
//     server.start();
// }
// void test2()
// {
//     ThreadPool pool(4, 10);
//     pool.start();
//     gPool=&pool;
//     TcpServer server("172.22.195.222", 8888);
//     server.setAllCallback(std::move(onNewConnection), std::move(onMessage), std::move(onClose));
//     server.start();
// }
void test3(){
    EchoServer server(4,10,"172.22.195.222", 8888);
    server.start();
    server.stop();
}
int main()
{
    test3();

    return 0;
}