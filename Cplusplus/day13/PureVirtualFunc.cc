#include<iostream>
using namespace std;
class A
{
public:
    virtual void print()=0;
    virtual void display()=0;
};
class B
:public A
{
public:
    virtual void print()override{
        cout<< "B::print()" <<endl;
    }
};
class C
:public B
{
public:
    virtual void display()override{
        cout<< "C::display()" <<endl;
}
};
void test0(){
    //A类定义了纯虚函数，A类是抽象类
    //抽象类无法创建对象
    //Aa;//error
    //Bb;//error 
    C c;
    A *pa2=&c;
    pa2->print();
    pa2->display();
}

int main(){
    test0();
    return 0;
}