#include<54func.h>
#include<iostream>
#include<string>
#include<workflow/WFFacilities.h>
#include<workflow/HttpMessage.h>
#include<workflow/HttpUtil.h>
using std::cout;
using std::endl;
using std::string;
static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum){
    cout<<"signum="<<signum<<endl;
    gWaitGroup.done(); //计数器减一
}

void httpCallback(WFHttpTask * httptask){
    cout<<"4"<<endl;
    //处理请求响应
    protocol::HttpRequest *req=httptask->get_req();
    protocol::HttpResponse* resp=httptask->get_resp();
    int state=httptask->get_state();
    int error=httptask->get_error();
    switch(state){
        case WFT_STATE_SYS_ERROR:
            cout<<"system error:"<<strerror(error)<<endl;
            break;
        case WFT_STATE_DNS_ERROR:
            cout<<"dns error:"<<strerror(error)<<endl;
            break;
        case WFT_STATE_SUCCESS:
            break;
    }
    if(state==WFT_STATE_SUCCESS){
        cout<<"SUCCESS"<<endl;
    }else{
        cout<<"FAILED"<<endl;
        return ;
    }

    protocol::HttpHeaderCursor cursorReq(req);
    string key;
    string value;
    while(cursorReq.next(key,value)){
        cout<<"request key = "<<key<<", value = "<<value<<"\n";
    }
    cout<<endl<<endl;
    protocol::HttpHeaderCursor cursorResp(resp);
    while(cursorResp.next(key,value)){
        cout<<"response key = "<<key<<", value = "<<value<<"\n";
    }

    const void *body;
    size_t size;
    resp->get_parsed_body(&body,&size);
    cout<<string((char *)body,size)<<"\n";
}
int main(){
    signal(SIGINT,handler);
    cout<<"1"<<endl;
    //利用工厂函数创建一个任务
    WFHttpTask * httpTask=WFTaskFactory::create_http_task("http://172.22.195.222:8888",10,0,httpCallback);
    // WFHttpTask * httpTask=WFTaskFactory::create_http_task("http://www.baidu.com",10,0,httpCallback);
    cout<<"2"<<endl;
    //设置httpTask的属性 请求
    protocol::HttpRequest *req=httpTask->get_req();
    req->add_header_pair("Accept","*/*");
    //启动 交给框架来做
    httpTask->start();
    cout<<"3"<<endl;


    gWaitGroup.wait();
}