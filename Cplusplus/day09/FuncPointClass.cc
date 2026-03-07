#include<iostream>
using namespace std;
void print(int x){
    cout<<"print:"<<x<<endl;
}
void display(int x){
    cout<<"display:"<<x<<endl;
}
void show(){
    cout<<"show"<<endl;
}
int down(int x){
    cout<<"down:"<<endl;
    return x;
}
//将此类的函数指针的类型定名为Func
typedef void (*Func)(int);

int main(){
    //定义函数指针时就已经确定了
    //这个函数指针只能指向特定类型的函数
    //返回类型、参数类型都确定了
    //省略形式
    void (*p)(int)=print;
    p(4);
    p=display;
    p(5);
    
    //完整形式
    void (*p2)(int)=&print;
    (*p2)(6);

    Func p3=print;
    p3(7);
    p3=display;
    p3(8);

    return 0;
}