#include<iostream>
using namespace std;
class Singleton{
    class AutoRelease{
    public:
        AutoRelease(){
            cout<<"AutoRelease()"<<endl;
        }
        ~AutoRelease(){
            cout<<"~AutoRlease()"<<endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance=NULL;
            }
        }
    };
private:
    Singleton(int x,int y)
    :_ix(x)
    ,_iy(y)
    {cout<<"Singleton()"<<endl;}
    ~Singleton(){
        cout<<"~Singleton()"<<endl;
    }
public:
    static Singleton * getInstance(){
        if(_pInstance ==NULL){
            _pInstance=new Singleton(1,2);
        }
        return _pInstance;
    }
    static void destory(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=NULL;
        }
    }
    void print(){
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
    Singleton(const Singleton & other)=delete;
    Singleton & operator=(const Singleton & other)=delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
    static AutoRelease _ar;
};
Singleton* Singleton::_pInstance = NULL;
Singleton::AutoRelease Singleton::_ar;
int main(){
    Singleton::getInstance()->print();
    // Singleton::destory();
    return 0;
}