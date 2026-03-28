#include"Producer.h"
#include"Consumer.h"
#include"TaskQueue.h"
#include<memory>
#include<iostream>
#include<thread>
using namespace std;
void test(){
    TaskQueue taskque(10);
    Producer producer;
    Consumer consumer;
    thread pro(&Producer::run,&producer,std::ref(taskque));
    thread con(&Consumer::run,&consumer,std::ref(taskque));
    
    pro.join();
    con.join();
}
int main(){
    test();
    return 0;
}