#include<iostream>
using namespace std;
class Base{
public:
    Base(long base)
    :_base(base)
    {cout<<"Base(long)"<<endl;}
    ~Base(){
        cout<<"~Base()"<<endl;
    }
    virtual void display() const{
        cout<<"Base::display()"<<endl;
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
    ,_derived(derived)
    {   cout<<"Derived(long,long)"<<endl;}
    ~Derived(){
        cout<<"~Derived()"<<endl;
    }
    void display() const override{
        cout<<"Derived::display()"<<endl;
    }
private:
    long _derived;
};
int main(){
    Base base(1);
    Derived d1(10,20);
    Base *p1=&base;
    p1->display();

    Derived *p2=&d1;
    p2->display();

    Base *p3=&d1;
    p3->display();
    return 0;
}