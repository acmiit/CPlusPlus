#include<54func.h>
#include<iostream>
#include<string>
#include<SimpleAmqpClient/SimpleAmqpClient.h>
using std::string;
using std::cout;
using namespace AmqpClient;
struct MQInfo{
    string Exchange="exchange_test";
    string RountingKey="key1";
    string Queue="queue3";
};
int main(){
    MQInfo mqinfo;
    //crate为channel申请内存
    Channel::ptr_t channel=Channel::Create();
    //调用basicconsume创建一个消费过程
    channel->BasicConsume(mqinfo.Queue);
    Envelope::ptr_t envelope;
    bool flag=channel->BasicConsumeMessage(envelope,-1);
    if(flag){
        cout<<"message= "<<envelope->Message()->Body()<<"\n";
    }else{
        cout<<"timeout\n";
    }

    return 0;
}