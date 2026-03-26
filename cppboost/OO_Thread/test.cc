#include<iostream>
using namespace std;
void *threadFunc(void *arg){
    while(1){
        cout<<"running!"<<endl;
    }
    return nullptr;
}


int main(){
    pthread_t tid;
    int ret=pthread_create(&tid,nullptr,threadFunc,nullptr);

    pthread_join(tid,nullptr);
    return 0;
}