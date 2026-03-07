#include<iostream>
#include<string.h>
using namespace std;
class Computer{
public:
    static Computer * getInstance(){
        if(_pInstance==NULL){
            _pInstance=new Computer("xiaomi",6000);
        }
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=NULL;
        }
        cout<<"head delete"<<endl; 
    }
    void Init(const char * brand,double price)
    {
        if(_brand){
            delete [] _brand;
            _brand=NULL;
        }
        _brand=new char[strlen(brand)+1]();
        strcpy(_brand,brand);
        _price=price;
        cout<<"Init(const char *,double)"<<endl;
    }
    void display(){
        cout<<"("<<_brand<<","<<_price<<")"<<endl;
    }
    Computer(const Computer & rhs) = delete;
    Computer & operator=(const Computer & rhs)=delete;
private:
    Computer()=default;
    Computer(const char * brand,double price)
    :_brand(new char[strlen(brand)+1]())
    ,_price(price)
    {
        strcpy(_brand,brand);
        cout<<"Computer(const char *,double)"<<endl;
    }
    ~Computer(){
        if(_brand){
            delete[] _brand;
            _brand=NULL;
        }
        cout<<"~Computer()"<<endl;
    }
private:
    char *_brand;
    double _price;
    static Computer * _pInstance;
};
Computer * Computer::_pInstance=NULL;
int main(){
    Computer::getInstance()->Init("apple",10000);
    Computer::getInstance()->Init("apple",10000);
    return 0;
}