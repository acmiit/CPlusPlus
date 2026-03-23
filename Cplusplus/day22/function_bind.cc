#include <iostream>
#include <functional>
#include<math.h>
using namespace std;
class Figure
{
public:
    using DisplayCallback = function<void()>;
    using AreaCallback = function<double()>;
    DisplayCallback _displayCallback;
    AreaCallback _areaCallback;
    // 注册回调函数
    void setDisplayCallback(DisplayCallback &&cb)
    {
        _displayCallback = std::move(cb);
    }
    void setAreaCallback(AreaCallback &&cb)
    {
        _areaCallback = std::move(cb);
    }
    // 执行回调函数
    void handleDispalyCallback() const
    {
        if (_displayCallback)
        {
            _displayCallback();
        }
    }
    double handleAreaCallback() const
    {
        if (_areaCallback)
        {
            return _areaCallback();
        }
        else
        {
            return 0;
        }
    }
};
// 执行回调函数
void test(const Figure &fig) // 这里使用const对象，所以处理函数必须定义为const版本
{
    fig.handleDispalyCallback();
    cout << "'sareais:" << fig.handleAreaCallback() << endl;
}
class Rectangle
{
public:
    Rectangle(double length, double width)
        : _length(length), _width(width)
    {
    }
    void display(int ix) const // 相比之前，这里display函数可以传参
    {
        cout << "Rectangle";
    }
    double area() const
    {
        return _length * _width;
    }

private:
    double _length;
    double _width;
};
class Circle
{
public:
    Circle(double radis)
        : _radis(radis)
    {
    }
    void show() const
    {
        cout << "Circle";
    }
    double getArea() const
    {
        return _radis * _radis * 3.1415;
    }

private:
    double _radis;
};
class Traingle
{
public:
    Traingle(double a, double b, double c)
        : _a(a), _b(b), _c(c)
    {
    }
    void print() const
    {
        cout << "Traingle";
    }
    double calcArea() const
    {
        double tmp = (_a + _b + _c) / 2;
        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

private:
    double _a;
    double _b;
    double _c;
};
void test01()
{
    Rectangle rectangle(10, 20);
    Circle circle(10);
    Traingle traingle(3, 4, 5);
    Figure figure;
    figure.setDisplayCallback(bind(&Rectangle::display, &rectangle, 10));
    figure.setAreaCallback(bind(&Rectangle::area, &rectangle));
    test(figure);
    figure.setDisplayCallback(bind(&Circle::show, &circle));
    figure.setAreaCallback(bind(&Circle::getArea, &circle));
    test(figure);
    figure.setDisplayCallback(bind(&Traingle::print, &traingle));
    figure.setAreaCallback(bind(&Traingle::calcArea, &traingle));
    test(figure);
}
// 海伦公式
int main()
{
    // Figure f;
    test01();
    return 0;
}