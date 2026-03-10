#include<iostream>
using namespace std;
class Singleton{
public:
    static Singleton * getInstance(){
        if(_pInstance==NULL)
            _pInstance = new Singleton(1,1);
        return _pInstance;
    }
    static void destory(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=NULL;
        }
    }
    void Init(int x,int y){
        _ix=x;
        _iy=y;
    }
    void print(){
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
private:
    Singleton(int x,int y)
    :_ix(x)
    ,_iy(y)
    {
        cout<<"Singleton(int,int)"<<endl;
    }
    ~Singleton(){
        cout<<"~SingleTon"<<endl;
    }
    Singleton(const Singleton & other)=delete;
    Singleton & operator=(const Singleton &other)=delete;

    int _ix;
    int _iy;
    static Singleton * _pInstance;
};
Singleton *Singleton::_pInstance=NULL;
int main(){
    Singleton::getInstance()->print();
    
    return 0;
}