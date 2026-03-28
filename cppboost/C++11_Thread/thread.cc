#include<iostream>
#include<thread>
using namespace std;
void ThreadFunc(int x){
    cout<<"void ThreadFunc(int)"<<endl;
    cout<<"x= "<<x<<endl;
}
int main(){
    // thread th(ThreadFunc,10);
    // void (&pFunc)(int)=ThreadFunc; //函数指针和函数引用都可以
    void (*pFunc)(int)=ThreadFunc;
    thread th(pFunc,20); 
    cout<<"child id= "<<th.get_id()<<endl;
    cout<<"main id= "<<std::this_thread::get_id()<<endl;
    th.join();
    return 0;
}