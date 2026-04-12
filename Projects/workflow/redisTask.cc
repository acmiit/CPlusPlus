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


int main(){
    signal(SIGINT,handler);

    //利用工厂函数创建一个任务
    WFRedisTask *redisTask=WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",0,
        [](WFRedisTask * redistask){
            protocol::RedisRequest *req =redistask->get_req();
            protocol::RedisResponse *resp =redistask->get_resp();
            protocol::RedisValue value;
            int state=redistask->get_state();
            int error=redistask->get_error();
            switch(state){
                case WFT_STATE_SYS_ERROR:
                    cout<<"system error:"<<strerror(error)<<endl;
                    break;
                case WFT_STATE_DNS_ERROR:
                    cout<<"dns error:"<<strerror(error)<<endl;
                    break;
                case WFT_STATE_SUCCESS:
                    resp->get_result(value);
                    if(value.is_error()){
                        cout<<"redos error\n";
                        state=WFT_STATE_TASK_ERROR;
                    }
                    break;
            }
            if(state==WFT_STATE_SUCCESS){
                cout<<"SUCCESS"<<endl;
            }else{
                cout<<"FAILED"<<endl;
                return ;
            }
            if(value.is_string()){
                cout<<"value is a string ,value = "<<value.string_value()<<"\n";
            }else if(value.is_array()){
                for(size_t i=0;i<value.arr_size();++i){
                    cout<<"value is arr, i = "<<i<<", arr[i] = "<<value.arr_at(i).string_value()<<"\n";
                }
            }
        });
   
    //设置httpTask的属性 请求
    protocol::RedisRequest *req=redisTask->get_req();
    // req->set_request("SET",{"x","54"});
    req->set_request("HGETALL",{"h1"});
    //启动 交给框架来做
    redisTask->start();
    gWaitGroup.wait();
}