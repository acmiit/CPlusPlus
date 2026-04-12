#include <54func.h>
#include <iostream>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include<workflow/WFHttpServer.h>
using std::cout;
using std::endl;
using std::string;
static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum)
{
    cout << "signum=" << signum << endl;
    gWaitGroup.done(); // 计数器减一
}
void process(WFHttpTask * serverTask){
    cout<<"process is called!\n";
}

int main()
{
    signal(SIGINT, handler);
    WFHttpServer server(process);
    server.start(8888);
    gWaitGroup.wait();
}