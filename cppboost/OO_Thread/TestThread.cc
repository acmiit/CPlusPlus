#include<iostream>
#include<memory>
#include"Thread.h"
#include <unistd.h>
using namespace std;
class MyThread
:public Thread{
    void run() override{
        while(1){
            cout<<"MyThread is running!!"<<endl;
            sleep(1);
        }

    }
};
void test(){
    MyThread mth;
    mth.start();
    mth.stop();
}
void test2(){
    unique_ptr<Thread> up(new MyThread());
    up->start();
    up->stop();
}
int main(){
    test2();
    return 0;
}