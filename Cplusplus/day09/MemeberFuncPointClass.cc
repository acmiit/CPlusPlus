#include<iostream>
using namespace std;
void print(int x){
    cout<<"print:"<<x<<endl;
}
void display(int x){
    cout<<"display:"<<x<<endl;
}
class FFF{
public:
    void print(int x){
        cout<<"print:"<<x<<endl;
    }
    void display(int x){
        cout<<"display:"<<x<<endl;
    }
};
//将此类的函数指针的类型定名为Func
typedef void (FFF::* Func)(int);

int main(){
    //FFF::print 这个写法显示出print是FFF类的成员函数
    // 前面加上&是完整的写法
    // 成员函数指针的定义和使用不能用省略的写法
    // 定义成员函数指针的时候也需要加上类作用域
    void (FFF::*p)(int)=&FFF::display;
     FFF fff;
     (fff.*p)(6);

     Func p2=&FFF::display;
     (fff.*p2)(6);
    return 0;
} 