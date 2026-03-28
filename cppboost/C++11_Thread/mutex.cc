#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
int gCnt=0;
mutex mtx;
void threadFunc(){

    for(int i=0;i<100000;i++){
        // mtx.lock();
        // lock_guard<mutex> lg(mtx); //无法手动解锁
        unique_lock<mutex> ul(mtx);
        ++gCnt;
        // mtx.unlock();
        mtx.unlock(); 
    }

}
void test(){
    thread th(threadFunc);
    thread th2(threadFunc);
    th.join();
    th2.join();
    cout<<"gCnt= "<<gCnt<<endl;
}
int main(){
    test();

    return 0;
}