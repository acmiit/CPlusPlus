#include <54func.h>
#include <iostream>
#include <string>
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <wfrest/json.hpp>
#include <wfrest/Json.h>
#include<vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using Json = nlohmann::json;
static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum)
{
    cout << "signum=" << signum << endl;
    gWaitGroup.done(); // 计数器减一
}
void process(WFHttpTask *serverTask)
{
    // http://172.22.195.222:1234/file/mupload/init
    // http://172.22.195.222:1234/file/mupload/uppart?uploadID=root114405&chkidx=2
    // http://172.22.195.222:1234/file/mupload/complete?uploadID=root114405
    protocol::HttpResponse *resp = serverTask->get_resp();
    protocol::HttpRequest *req = serverTask->get_req();
    string method = req->get_method();
    string uri = req->get_request_uri();
    // 分离路径和查询参数
    string path = uri;
    string query = "";
    size_t pos = uri.find("?");
    if (pos != string::npos)
    {
        path = uri.substr(0, pos);
        query = uri.substr(pos + 1);
    }
    cout << "path: " << path << endl;
    cout << "query: " << query << endl;
    cout << method << endl;
    if (method == "GET")
    {
        // 处理GET请求
        resp->set_status_code("200");
        resp->append_output_body("GET method received\n");
    }
    else if (method == "POST")
    {
        cout << "POST" << endl;
        if (path == "/file/mupload/init")
        {
            cout << "init" << endl;
            // 1、解析请求报文
            const void *body;
            size_t size;
            req->get_parsed_body(&body, &size);
            // 2、字符串解析成json
            Json fileInfo = Json::parse(static_cast<const char *>(body));
            string filename = fileInfo["filename"];
            int filesize = fileInfo["filesize"];
            string filehash = fileInfo["filehash"];
            cout << "filename:" << filename << "  filehash:" << filehash << "  filesize" << filesize << endl; // ok
            // 3、生成响应内容
            string uploadID = "root";
            time_t now = time(NULL);
            struct tm *ptm = localtime(&now);
            char timeStamp[30] = {0};
            sprintf(timeStamp, "%02d%02d%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
            uploadID = uploadID + timeStamp;
            cout << "uploadID:" << uploadID << endl;

            //分块大小：数量
            int chunksize=1024*1024;
            int chunkcount=0;
            if(filesize%chunksize!=0){
                chunkcount=filesize/chunksize+1;
            }else{
                chunkcount=filesize/chunksize;
            }
            cout<<"chunksize:"<<chunksize<<"  chunkcount:"<<chunkcount<<endl;

            //将数据存入缓存
            // 初始化redis
            // HSET uploadID chunkcount 6
            // HSET uploadID filehash xxx
            // HSET uploadID filesize xxx
            vector<vector<string>> argsVec={
                {uploadID,"chunkcount",std::to_string(chunkcount)},
                {uploadID,"filehash",filehash},
                {uploadID,"filesize",std::to_string(filesize)}
            };
            for(int i=0;i<3;i++){
                WFRedisTask * redisTask=WFTaskFactory::create_redis_task("redis://localhost",0,nullptr);
                redisTask->get_req()->set_request("HSET",argsVec[i]);
                redisTask->start();
            }
            //生成响应报文  报文体内容：status、uploadID、chunkcount、chunksize、filesize、filehash
            Json  uppartInfo;
            uppartInfo["status"]="OK";
            uppartInfo["uploadID"]=uploadID;
            uppartInfo["chunkcount"]=chunkcount;
            uppartInfo["chunksize"]=chunksize;
            uppartInfo["filesize"]=filesize;
            uppartInfo["filehash"]=filehash;
            resp->append_output_body(uppartInfo.dump());
        }
        else if (path == "/file/mupload/uppart")
        {
            cout << "uppart" << endl;
            //解析uri
            string uploadIDKV=query.substr(0,query.find("&"));
            string uploadID=uploadIDKV.substr(uploadIDKV.find("=")+1);
            string chkidxKV=query.substr(query.find("&")+1);
            string chkidx=chkidxKV.substr(chkidxKV.find("=")+1);
            cout<<"uploadID:"<<uploadID<<" chkidx:"<<chkidx<<endl; //OK
            // 保存单个分片 ./filehash/1 filehash需要从redis当中获取 HGET uploadID filehash
            WFRedisTask * redisTaskHGET=WFTaskFactory::create_redis_task("redis://localhost",0,[chkidx,req](WFRedisTask * redisTaskHGET){
                protocol::RedisValue value;
                redisTaskHGET->get_resp()->get_result(value);
                string filehash=value.string_value();
                mkdir(filehash.c_str(),0777);
                string filepath=filehash+"/"+chkidx;
                //文件IO任务
                int fd=open(filepath.c_str(),O_RDWR|O_CREAT,0666);
                const void *body;
                size_t size;
                req->get_parsed_body(&body,&size);
                write(fd,body,size);
                close(fd);
            });
            redisTaskHGET->get_req()->set_request("HGET",{uploadID,"filehash"});
            series_of(serverTask)->push_back(redisTaskHGET);
            //记录下载进度
            WFRedisTask * redisTaskHSET=WFTaskFactory::create_redis_task("redis://localhost",0,nullptr);
            redisTaskHSET->get_req()->set_request("HSET",{uploadID,"chkidx_"+chkidx,"1"});
            series_of(serverTask)->push_back(redisTaskHSET);
            resp->append_output_body("OK");


        }
        else if (path == "/file/mupload/complete")
        {
            cout << "complete" << endl;
            //解析uri 
            string uploadID= query.substr(query.find("=")+1);
            //查询上传进度 redis 中 chkidx_是已经上传的，chunkcount是总数量 ，看是否相等
            WFRedisTask * redisTask=WFTaskFactory::create_redis_task("redis://localhost",0,[resp](WFRedisTask * redisTask){
                protocol::RedisValue value;
                redisTask->get_resp()->get_result(value);
                int chunkcount;
                int chunknow=0;
                for(int i=0;i<value.arr_size();i+=2){
                    string key=value.arr_at(i).string_value();
                    string val=value.arr_at(i+1).string_value();
                    if(key=="chunkcount"){
                        chunkcount=std::stoi(val);
                    }else if(key.substr(0,7)=="chkidx_"){
                        ++chunknow;
                    }
                }
                cout<<"chunkcount:"<<chunkcount<<"  chunknow:"<<chunknow<<endl;
                if(chunknow==chunkcount){
                    resp->append_output_body("SUCCESS");
                }else{
                    resp->append_output_body("FAIL");
                }
            });
            redisTask->get_req()->set_request("HGETALL",{uploadID});
            cout<<"uploadID:"<<uploadID<<endl;
            series_of(serverTask)->push_back(redisTask);
        }
    }
}
int main()
{
    signal(SIGINT, handler);
    WFHttpServer server(process);
    if (server.start(1234) == 0)
    {
        gWaitGroup.wait();
        server.stop();
    }
    else
    {
        perror("Cannot start server");
        exit(1);
    }

    return 0;
}