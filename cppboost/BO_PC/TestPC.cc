#include"Producer.h"
#include"Consumer.h"
#include"TaskQueue.h"
#include<memory>
#include<iostream>
#include"Thread.h"

void test(){
    TaskQueue taskque(10);
    // std::unique_ptr<Thread> pro(new Producer(taskque));
    // std::unique_ptr<Thread> con(new Consumer(taskque));
    Producer p(taskque);
    Consumer c(taskque);
    Thread pro(std::bind(&Producer::run,&p));
    Thread con(std::bind(&Consumer::run,&c));
    pro.start();
    con.start();
    pro.stop();
    con.stop();
}
int main(){
    test();
    return 0;
}