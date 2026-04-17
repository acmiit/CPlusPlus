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
};
int main(){
    //crate为channel申请内存
    MQInfo mqinfo;
    Channel::ptr_t channel=Channel::Create();
    //创建一个消息
    BasicMessage::ptr_t message=BasicMessage::Create("howareyou");
    //发送消息
    channel->BasicPublish(mqinfo.Exchange,mqinfo.RountingKey,message);
    return 0;
}