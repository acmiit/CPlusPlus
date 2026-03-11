#include<iostream>
using namespace std;
class Base{
public:
    Base(long base)
    :_base(base)
    {
        cout<<"Base()"<<endl;
    }
    virtual void display(){
        cout<<"Base::display"<<endl;
    }
    ~Base(){
        cout<<"~Base()"<<endl;
    }
private:
    long _base;
};
class Derived
:public Base
{
public:
    Derived(long base,long derived)
    :Base(base)
    ,_derived(derived){
        cout<<"Derived(long)"<<endl;
    }
    ~Derived(){
        cout<<"~Derived()"<<endl;
    }
private:
    long _derived;
};
int main(){

    Base base(1);
    Derived d1(1,2);
    base=d1;//ok 向上转型 基类的内存空间小于派生类的对象，
    // d1=base;//error
    Base *pbase=&d1;//ok 转换成功，原本指向的是Derived
    // Derived*pderived=&base//error
    Base &rbase=d1;//ok
    // Derived &rderived=base;//error

    pbase=&base; //转换失败，本来指向就是Base
    //在使用dynamic_cast时还需要有多态的内容
    Derived *pd=dynamic_cast<Derived*>(pbase);
    if(pd){
        cout<<"转换成功"<<endl;
        pd->display();
    }else{
        cout<<"转换失败"<<endl;
    }
    return 0;
}