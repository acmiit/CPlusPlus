#include<iostream>
#include<cstdlib>
#include<pthread.h>
using namespace std;
class Singleton{
public:
    static Singleton * getInstance(){
        pthread_once(&_once,init_r);
        return _pInstance;
    }
    static void init_r(){
        _pInstance = new Singleton(1,1);
        atexit(destory);
    }
    void Init(int x,int y){
        _ix=x;
        _iy=y;
    }
    void print(){
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
private:
    static void destory(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=NULL;
        }
    }
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
    static pthread_once_t _once;
};
Singleton *Singleton::_pInstance=NULL;
pthread_once_t Singleton::_once=PTHREAD_ONCE_INIT;
int main(){
    Singleton::getInstance()->print();
    
    return 0;
}