#include<iostream>
#include<math.h>
#define PI 3.14
using namespace std;
class Circle{
public:
    Circle()
    :_r(0)
    {
        cout<<"Circle()"<<endl;
    }
    Circle(double r)
    :_r(r)
    {
        cout<<"Circle(double)"<<endl;
    }
    ~Circle(){
        cout<<"~Circle()"<<endl;
    }
    double getArea(){
        return PI*pow(_r,2);
    }
    double getPerimeter(){
        return 2*PI*_r;
    }
    void show(){
        cout<<"r:"<<_r<<" perimeter:"<<getPerimeter()<<" area:"<<getArea()<<endl;
    }
private:
    double _r;
};
int main(){
    Circle c1;
    Circle c2(1);
    c1.show();
    c2.show();
    return 0;
}