#include <iostream>
#include <cmath>
#include <memory>
using namespace std;
class Figure
{
public:
    virtual void display()const = 0;
    virtual double area()const = 0;
    virtual ~Figure() = default;
};
class Rectangle
: public Figure
{
public:
    Rectangle(double length, double width)
        : Figure(), _length(length), _width(width)
    {
        if(_length<=0||_width<=0){
            throw invalid_argument("矩阵的长和宽必须为正数");
        }
        cout<<"Rectangle(double,double)"<<endl;
    }
    void display() const override
    {
        cout << "Rectangle";
    }
    double area() const override
    {
        return _length * _width;
    }
    ~Rectangle(){
        cout<<"~Rectangle()"<<endl;
    }
private:
    double _length;
    double _width;
};
class Circle
    : public Figure
{
public:
    Circle(double radis)
        : _radis(radis)
    {
        cout<<"Circle(double)"<<endl;
    }
    ~Circle(){
        cout<<"~Circle()"<<endl;
    }
    void display() const override
    {
        cout << "Circle";
    }
    double area() const override
    {
        return _radis * _radis * 3.1415;
    }

private:
    double _radis;
};
class Triangle
    : public Figure
{
public:
    Triangle(double a, double b, double c)
        : _a(a), _b(b), _c(c)
    {
        cout<<"Triangle(double,double,double)"<<endl;
    }
    ~Triangle(){
        cout<<"~Triangle()"<<endl;
    }
    void display() const override
    {
        cout << "Triangle";
    }
    double area() const override
    {
        double tmp = (_a + _b + _c) / 2;
        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

private:
    double _a;
    double _b;
    double _c;
};
void func(Figure *pfig)
{
    pfig->display();
    cout << "的面积： " << pfig->area() << endl;
}
class Factory
{
public:
    static unique_ptr<Figure> create(const string &name)
    {
        if (name == "rectangle")
        {
            return unique_ptr<Figure>(new Rectangle(4,5));
        }
        else if (name == "circle")
        {
            return unique_ptr<Figure>(new Circle(4));
        }
        else if (name == "triangle")
        {
            return unique_ptr<Figure>(new Triangle(4,5,6));
        }
        else
        {
            return nullptr;
        }
    }
};
int main()
{
    unique_ptr<Figure> ptr = Factory::create("rectangle");
    unique_ptr<Figure> ptc = Factory::create("circle");
    unique_ptr<Figure> pti = Factory::create("triangle");
    cout<<endl;
    func(ptr.get());
    func(ptc.get());
    func(pti.get());
    cout<<endl;
    return 0;
}