#include<iostream>
using namespace std;
class Base{
public:
    Base(long base)
    :_base(base)
    {
        cout<<"Base(long)"<<endl;
    }
    ~Base(){
        cout<<"~Base()"<<endl;
    }
    virtual void display()const{
        cout<<"Base::display()"<<endl;
    }
    virtual void show()const{
        cout<<"Base::show()"<<endl;
    }
    virtual void print()const{
        cout<<"Base::print()"<<endl;
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
    {
        cout<<"Derived(long,long)"<<endl;
    }
    ~Derived(){
        cout<<"~Derived()"<<endl;
    }
    virtual void display()const override{
        cout<<"Derived::display()"<<endl;
    }
    virtual void show()const override{
        cout<<"Derived::show()"<<endl;
    }
    virtual void print()const override{
        cout<<"Derived::print()"<<endl;
    }
private:
    long _derived;
};
typedef void (*func)();
int main(){
    Derived d(1,2);
    Base *base=&d;
    long *p=reinterpret_cast<long *>(base);
    cout<<p[0]<<endl;
    cout<<p[1]<<endl;
    cout<<p[2]<<endl;
    long *pVtable=reinterpret_cast<long*>(p[0]);
    cout<<pVtable[0]<<endl;
    cout<<pVtable[1]<<endl;
    cout<<pVtable[2]<<endl;
    func pfunc=reinterpret_cast<func>(pVtable[0]);
    pfunc();
    pfunc=reinterpret_cast<func>(pVtable[1]);
    pfunc();
    pfunc=reinterpret_cast<func>(pVtable[2]);
    pfunc();
    return 0;
}