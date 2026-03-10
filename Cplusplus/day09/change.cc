#include<iostream>
using namespace std;
class Complex{
    public:
        Complex(int real,int image)
        :_real(real)
        ,_image(image)
        {
            cout<<"Complex(int,int)"<<endl;
        }
        void display() const{
            cout<<_real<<"+"<<_image<<"i"<<endl;
        }
    private:
        int _real; 
        int _image;
    };
class Point{
public:
    //限制构造函数，不能隐式转换
    explicit Point(int x=0,int y=0)
    :_ix(x)
    ,_iy(y)
    {
        cout<<"Point(int,int)"<<endl;
    }
    void print() const{
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
    operator int (){
        cout<<"operator int ()"<<endl;
        return _ix+_iy;
    }
    operator Complex (){
        cout<<"operator Complex ()"<<endl;
        return Complex(_ix,_iy);
    }
private:
    int _ix;
    int _iy;
};
int main(){
    //利用类型转换函数，将自定义类型转换成了内置类型
    Point pt2(1,2);
    int a=pt2;
    //本质
    int b=pt2.operator int();
    cout<<a<<endl;
    cout<<b<<endl;

    Complex cx(3,4);
    cx=pt2;
    cx.display();
    return 0;
}