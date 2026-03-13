#include<iostream>
#include<math.h>
using namespace std;
#define PI 3.141592653
class Figure{
public:
    virtual string getName()const=0;
    virtual double getArea()const=0;
};
class Rectangle//矩形
:public Figure
{
public:
    Rectangle(double len,double wid)
    :_length(len)
    ,_width(wid)
{}
    string getName()const override
    {
        return"矩形";
    }
    double getArea()const override
    {
        return _length*_width;
    }
private:
    double _length;
    double _width;
};
class Circle
:public Figure
{
public:
    Circle(double r)
    :_radius(r)
    {}
    string getName()const override
    {
        return"圆形";
    }
    double getArea()const override
    {
        return PI*_radius*_radius;
    }
private:
    double _radius;
};
class   Triangle
:public Figure
{
public:
Triangle(double a,double b,double c)
:_a(a)
,_b(b)
,_c(c)
{}
    string getName()const override
    {
        return"三角形";
    }
    double getArea()const override
    {
        double p=(_a+ _b+ _c)/2;
        return sqrt(p*(p-_a)*(p-_b)*(p-_c));
    }
private:
    double _a,_b,_c;
};

void display(Figure *pf){
    cout<<pf->getName()<<endl;
    cout<<pf->getArea()<<endl;
}
void show(Figure &rhs){
    cout<<rhs.getName()<<endl;
    cout<<rhs.getArea()<<endl;
}
int main(){
    Rectangle rectangle(10,20);
    Circle circle(10);
    Triangle triangle(3,4,5);
    display(&rectangle);
    display(&circle);
    display(&triangle);
    cout<<endl;
    show(rectangle);
    show(circle);
    show(triangle);
    return 0;
}