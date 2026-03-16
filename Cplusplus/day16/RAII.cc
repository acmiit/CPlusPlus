#include<iostream>
using namespace std;
class Point{
public:
    Point(int x=0,int y=0)
    :_ix(x)
    ,_iy(y)
    {cout<<"Point(int=0,int=0)"<<endl;}
    void print() const{
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
    ~Point(){
        cout<<"~Point()"<<endl;
    }
private:
    int _ix;
    int _iy;

};
template <class T>
class RAII{
public:
        //1、在构造函数中托管资源
        RAII(T * pdata)
        :_pdata(pdata){
            cout<<"RAII(T *)"<<endl;
        }
        //2、在析构函数中释放资源
        ~RAII(){
            if(_pdata){
                delete _pdata;
                _pdata=nullptr;
            }
            cout<<"~RAII()"<<endl;
        }
        //3、不允许复制或者赋值
        RAII(const RAII & )=delete;
        RAII &operator=(const RAII &)=delete;

        //4、提供访问资源的方法
        T * operator->(){
            return _pdata;
        }
        T&  operator*(){
            return *_pdata;
        }
        T * get() const{
            return _pdata;
        }
        void set(T * pdata){
            if(_pdata){
                delete _pdata;
                _pdata=nullptr;
            }
            _pdata=pdata;
        }

private:
    T * _pdata;
};


void test0(){
    RAII<int> raii(new int(10));
    RAII<Point> raii2(new Point(3,8));
    raii2->print();

}
int main(){
    test0();
    return 0;
}