#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <iostream>
#include <csignal>
using namespace wfrest;
using std::cout;
using std::endl;
using std::string;
static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum)
{
    cout << "signum=" << signum << endl;
    gWaitGroup.done(); // 计数器减一
}

int main()
{
    signal(SIGINT, handler);
    wfrest::HttpServer server;
    server.POST("/abc", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp)
                { resp->append_output_body("123"); });
    server.POST("/xyz", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp)
                { resp->append_output_body("789"); });
    server.POST("/login", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series)
                {
        std::map<string,string> queryMap=req->query_list();
        string user=queryMap["user"];
        string password=queryMap["password"];
        cout<<"user:"<<user<<"password:"<<password<<"\n";
        cout << ">>> DEBUG USER: [" << user << "], Length: " << user.length() << "\n";
        WFRedisTask * redisTask=WFTaskFactory::create_redis_task("redis://127.0.0.1:6379/0",0,[=](WFRedisTask * redisTask){
            int state = redisTask->get_state();
            int error = redisTask->get_error();
            if (state != WFT_STATE_SUCCESS) {
                cout << "[ERROR] Redis Task Failed! state=" << state << ", error=" << error << "\n";
                resp->String("Redis Connection Failed");
                return;
            }
            
            protocol::RedisResponse *Redisresp=redisTask->get_resp();
            protocol::RedisValue value;
            Redisresp->get_result(value);
            if(value.is_string()&&value.string_value()==password){
                resp->String("OK");
            }else{
                resp->String("NO");
            }
        });
        redisTask->get_req()->set_request("HGET",{"43user",user});
        series->push_back(redisTask); });
    if (server.start(1234) == 0)
    {
        server.list_routes();
        gWaitGroup.wait();
    }
    return 0;
}