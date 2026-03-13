#include<iostream>
#include<string.h>
using namespace std;
class Base{
public: 
    Base()
    :_pbase(new char[1]())
    {
        cout<<"Base()"<<endl;
    }
    Base(const char * pbase){
        _pbase=new char [strlen(pbase)+1]();
        strcpy(_pbase,pbase);
        cout<<"Base(const char * pbase)"<<endl;
    }
    Base(const Base &rhs){
        _pbase = new char[strlen(rhs._pbase) + 1](); 
        cout<<"Base(const Base &pbase)"<<endl;
        strcpy(_pbase,rhs._pbase);
    }
    Base& operator=(const Base & rhs){
        if(this!=&rhs){
            delete [] _pbase;
            _pbase=nullptr;
            _pbase= new char [strlen(rhs._pbase)+1]();
            strcpy(_pbase,rhs._pbase);

        }
        cout<<"Base operator=(const Base &)"<<endl;
        return *this;
    }
    ~Base(){
        if(_pbase){
            delete [] _pbase;
            _pbase=nullptr;
        }
        cout<<"~Base()"<<endl;
    }
    friend ostream &operator<<(ostream &os ,const Base & rhs){
        if(rhs._pbase){
            os<<rhs._pbase;
        }
        return os;
    }
private:
    char * _pbase;
};
class Derived
:public Base
{
public:
    Derived(const char * pbase,const char *pderived)
    :Base(pbase)
    ,_pderived(new char[strlen(pderived)+1]())
    {
        cout<<"Derived(const char *)"<<endl;
        strcpy(_pderived,pderived);
    }
    Derived(const Derived &rhs)
    :Base(rhs) //显示调用基类的拷贝构造函数 
    ,_pderived(new char[strlen(rhs._pderived)+1]())
    {
        cout<<"Derived(const Base &)"<<endl;
        strcpy(_pderived,rhs._pderived);
    }
    Derived & operator=(const Derived &rhs){
        if(this!=&rhs){
            Base::operator=(rhs); //显示调用基类的赋值运算符函数
            delete [] _pderived;
            _pderived=nullptr;
            _pderived= new char [strlen(rhs._pderived)+1]();
            strcpy(_pderived,rhs._pderived);
        }
        return *this;
    }
    ~Derived(){
        cout<<"~Derived()"<<endl;
        if(_pderived){
            delete [] _pderived;
            _pderived=nullptr;
        }
    }

    friend ostream& operator<<(ostream &os ,const Derived &rhs){
        const Base &ref=rhs;
        os<<ref<<","<<rhs._pderived;
        return os;
    }
private:
    char * _pderived;
};
int main(){
    Derived d1("hello","world");
    cout<<"d1="<<d1<<endl;
    cout<<endl<<endl;

    Derived d2(d1);
    cout<<"d1="<<d1<<endl;
    cout<<"d2="<<d2<<endl;
    cout<<endl<<endl;

    Derived d3("world","wangdao");
    cout<<"d3="<<d3<<endl;
    d3=d1;
    cout<<"d1="<<d1<<endl;
    cout<<"d3="<<d3<<endl;
    return 0;
}