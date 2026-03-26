#include"Producer.h"
#include"Consumer.h"
#include"TaskQueue.h"
#include<memory>
#include<iostream>
#include"Thread.h"

void test(){
    TaskQueue taskque(10);
    std::unique_ptr<Thread> pro(new Producer(taskque));
    std::unique_ptr<Thread> con(new Consumer(taskque));
    pro->start();
    con->start();
    
    pro->stop();
    con->stop();
}
int main(){
    test();
    return 0;
}