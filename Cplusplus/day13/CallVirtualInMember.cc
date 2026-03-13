#include<iostream>
using namespace std;
class Base{
public:
    Base(long x)
    :_base(x)
    {}
    virtual void display()const{
        cout<< "Base::display()" <<endl;
    }
    void func1(){
         display();
        cout<< _base<<endl;
    }
    void func2(){
        Base::display();
    }
private:
    long _base=10;
};
class Derived
:public Base
{
public:
    Derived(long base,long derived)
    :Base(base)
    ,_derived(derived)
    {}
    void display()const override{
        cout<< "Derived::display()" <<endl;
    }
private:
    long _derived;
};
        void test0(){
        Base base(10);
        Derived derived(1,2);
        base.func1();
        base.func2();
        derived.func1();//调用了Derived::display();
        derived.func2();
        }
int main(){
    test0();
    return 0;
}