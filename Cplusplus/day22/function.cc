#include <iostream>
#include <functional>
using namespace std;
int add(int x, int y)
{
    return x + y;
}
class Example
{
public:
    int add(int x, int y) // 成员函数形式
    {
        cout << "int Example::add(int,int)" << endl;
        return x + y;
    }
    int data = 1;
};
void test()
{
    //以装函数类型的容器 绑定普通对象
    std::function<int()> f = bind(add, 1, 2);
    cout << "f()=" << f() << endl; //f()=3
    Example example;
    //this指针所以需要传&example参数 绑定类函数
    f = bind(&Example::add, &example, 10, 20);
    cout << "f()=" << f() << endl; //int Example::add(int,int)  \n f()=30
    //绑定类对象
    f = bind(&Example::data, &example); // 可以绑定到数据成员上面来
    cout << "f()=" << f() << endl;
    //占位符，需要按顺序 _1……
    using namespace std::placeholders;
    std::function<int(int)> f3 = bind(add, 1, _1);
    cout << "f3(10)=" << f3(10) << endl;
}
typedef int (*pFunc)(); // 函数指针
int func1()
{
    return 5;
}
int func2()
{
    return 15;
}
void test2()
{
    //函数指针
    pFunc f = func1;
    cout << "f()=" << f() << endl;
    f = func2;
    cout << "f()=" << f() << endl;
}
void func3(int x1, int x2, int x3, const int &x4, int x5)
{
    cout << "(" << x1
         << "," << x2
         << "," << x3
         << "," << x4
         << "," << x5
         << ")" << endl;
}
void test3()
{
    using namespace std::placeholders;
    int number = 100;
    auto f = bind(func3, 2, _1, _2, std::cref(number), number);
    number = 300;
    f(20, 30, 400, 50000, 5678); // 对于没有作用的实参是无效的参数
}

int main()
{
    test3();
    return 0;
}