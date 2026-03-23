#include<iostream>
#include<algorithm>
using namespace std;
void test(){
    //[]捕获列表
    //()函数的参数列表
    //{}函数的函数体
    []()->void{
        cout<<"hello"<<endl;
    }();
    int a=100;
    //lambda表达式默认是const的，如果想修改可使用mutable
    //值捕获
    [a]()mutable->void{
        ++a;
        cout<<"a="<<a<<endl;
        cout<<"hello"<<endl;
    }();
    cout<<"------------a="<<a<<endl;
    //引用捕获
    [&a]()->void{
        ++a;
        cout<<"a="<<a<<endl;
        cout<<"hello"<<endl;
    }();
    cout<<"------------a="<<a<<endl;
}
void test1(){
    [](const string &name){
        cout<<"test2"<<endl;
        cout<<"name:"<<name<<endl;
    }("wangdao");

    auto f=[](const string &name){
        cout<<"test2"<<endl;
        cout<<"name:"<<name<<endl;
    };
    f("test2");
}
int main(){
    test1();
    return 0;
}