#include<iostream>
using namespace std;
template<class ...Args>
void display(Args ...args){
    cout<<"sizeof...(Args):"<<sizeof...(Args)<<endl;
    cout<<"sizeof...(args):"<<sizeof...(args)<<endl;
}
void print(){
    cout<<endl;
}
template<class T,class ...Args>
void print(T x,Args ...args){
    cout<<x<<" ";
    print(args...);
}
int main(){
    display(1,2,3,4,5);
    print(1.2,4,"hello",true);
    return 0;
}