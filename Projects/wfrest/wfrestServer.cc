#include <wfrest/HttpServer.h>
#include<wfrest/json.hpp>
#include <workflow/WFFacilities.h>
#include <iostream>
#include <csignal>
using namespace wfrest;
using std::cout;
using std::endl;
using std::pair;
using std::map;
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
    server.GET("/abc",[](const HttpReq *req,HttpResp * resp){
        resp->headers["key"]="value";
    });
    server.POST("/def",[](const HttpReq *req,HttpResp * resp){
        if(req->content_type()==APPLICATION_URLENCODED){
            map<string,string> body=req->form_kv();
            for(auto mypair:body){
                cout<<"key= "<<mypair.first<<" ,value="<<mypair.second<<endl;
            }
        }
    });
    server.GET("/postform.html",[](const HttpReq *req,HttpResp * resp){
        resp->File("postform.html");
    });
    server.Static("/static","./static_res");

    server.POST("/formdata",[](const HttpReq *req,HttpResp * resp){
        if(req->content_type()==MULTIPART_FORM_DATA){
            map<string,pair<string,string>> &body=req->form();
            for(auto mypair:body){
                cout<<"key= "<<mypair.first<<" ,value1="<<mypair.second.first<<" ,value2="<<mypair.second.second<<endl;
            }
        }
    });
    using Json=nlohmann::json;
    server.POST("/json",[](const HttpReq *req,HttpResp * resp){
        string body=req->body();
        Json info=Json::parse(body);
        cout<<"filename:"<<info["filename"]<<",filecontent:"<<info["filecontent"]<<",filesize:"<<info["filesize"]<<endl;
        
    });
    if (server.start(1234) == 0)
    {
        server.list_routes();
        gWaitGroup.wait();
        server.stop();
    }

    
    return 0;
}