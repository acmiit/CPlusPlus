#include<alibabacloud/oss/OssClient.h>
#include<54func.h>
#include<iostream>
#include<string>
using std::string;
using std::cout;
using namespace AlibabaCloud::OSS;
struct OSSInfo{
    string EndPoint="oss-cn-guangzhou.aliyuncs.com";
<<<<<<< 3d6094e2102d1a0079b59a546a00489b963bc92c
    string AccessKetID="LTAI5tB617wtdbFhJqck9kiJ";
    string AccessKeySecret="RvlLQKdQnu7t0moaFl9d8zUXDIER2k";
=======
    string AccessKetID="";
    string AccessKeySecret="";
>>>>>>> Remove hardcoded secrets and binary files
    string Bucket="yxl-cplusplus";
};
int main(){
    OSSInfo info;
    //初始化网络资源
    InitializeSdk();
    ClientConfiguration conf;
    conf.maxConnections=30;
    conf.requestTimeoutMs=3000;
    conf.connectTimeoutMs=3000;
    //创建真正的客户端
   OssClient client(info.EndPoint,info.AccessKetID,info.AccessKeySecret,conf);
   PutObjectOutcome outcome=client.PutObject(info.Bucket,"dir1/file.txt","local.txt"); 
   if(!outcome.isSuccess()){
    cout<<"code= "<<outcome.error().Code()
    <<",message= "<<outcome.error().Message()<<"/n";
   }

    //释放网络资源
    ShutdownSdk();
}