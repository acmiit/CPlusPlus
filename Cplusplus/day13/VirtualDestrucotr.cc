#include<iostream>
using namespace std;
class Base{
public:
    Base()
    :_pbase(new int(10))
    {
        cout<<"Base()"<<endl;
    }
    virtual void display() const {
        cout<<"Base::display()"<<endl;
    }
    virtual ~Base(){
        if(_pbase){
            delete _pbase;
            _pbase=NULL;
        }
        cout<<"~Base()"<<endl;
    }
private:
    int * _pbase;
};
class Derived
:public Base
{
public:
    Derived()
    :Base()
    ,_pderived(new int(20))
    {
        cout<<"Derived()"<<endl;
    }
    void display() const override{
        cout<<"Derived::display"<<endl;
    }   
    ~Derived(){
        if(_pderived){
            delete _pderived;
            _pderived=NULL;
        }
        cout<<"~Derived()"<<endl;
    }
private:
    int * _pderived;
};
int main(){
    // Derived d1;
    // Base b=d1;
    // b.display();
    Base *base=new Derived();
    base->display();
    delete base; //泄露四个字节的内存空间 //一共有 24+8 （虚指针、_pbase、_pderived）+(10,20 内容)，最终泄露的存放20int内容的堆空间
    return 0;
}