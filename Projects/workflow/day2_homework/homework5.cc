#include<iostream>
#include<string>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/RedisMessage.h>
#include <workflow/Workflow.h>
#include <csignal>
using namespace std;
static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum){
    cout<<"signum="<<signum<<endl;
    gWaitGroup.done(); //计数器减一
}

int main(){
    signal(SIGINT,handler);
    //利用工厂函数创建一个任务
    WFHttpTask * http_task=WFTaskFactory::create_http_task("http://www.baidu.com",2,3,[](WFHttpTask *http_task){
        int state=http_task->get_state();
        int error=http_task->get_error();
        if(state!=WFT_STATE_SUCCESS){
            cerr<<"HTTP 请求失败 ！ state："<<state<<", Error: "<<error<<endl;
            gWaitGroup.done();
        }
        const void * body;
        size_t body_len;
        http_task->get_resp()->get_parsed_body(&body,&body_len);

        string html_content((const char *)body,body_len);

        WFRedisTask * redis_task=WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",2,[](WFRedisTask *redis_task){
            int r_state = redis_task->get_state();
            if (r_state == WFT_STATE_SUCCESS) {
                cout << "\n网页源码已成功存入 Redis! Key: [" << "http://www.baidu.com" << "]" << endl;
            } else {
                cerr << "存入 Redis 失败! Error: " << redis_task->get_error() << endl;
            }
            gWaitGroup.done();
        });
        redis_task->get_req()->set_request("SET",{"http://www.baidu.com",html_content});
        series_of(http_task)->push_back(redis_task);

    });
    http_task->start();
    gWaitGroup.wait();
    return 0;
}