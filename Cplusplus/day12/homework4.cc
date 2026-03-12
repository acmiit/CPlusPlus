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
        cout<<"圆的半径:"<<_r<<" 圆的周长:"<<getPerimeter()<<" 圆的面积:"<<getArea()<<endl;
    }
private:
    double _r;
};
class Cylinder
:public Circle
{
public:
    Cylinder(double r,double h)
    :Circle(r)
    ,_h(h)
    {
        cout<<"Cylinder(double,double)"<<endl;
    }
    ~Cylinder(){
        cout<<"Cylinder()"<<endl;
    }
    double getVolume(){
        return getArea()*_h;
    }
    double showVolume(){
        show();
        cout<<"圆柱体的体积"<<getVolume()<<endl;
    }
private:
    double _h;
};
int main(){
    // Circle c1;
    // Circle c2(1);
    // c1.show();
    // c2.show();

    
    Cylinder cl1(1,1);
    Cylinder cl2(3,3);
 
    cl1.showVolume();
    cl2.showVolume();
    return 0;
}