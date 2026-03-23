#include <iostream>
#include <algorithm>
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
        cout << "intExample::add(int,int)" << endl;
        return x + y;
    }
};
void test()
{
    auto f = bind(add, 3, 4);
    cout << f() << endl;
    Example em;
    // em this 指针
    auto f2 = bind(&Example::add, &em, 4, 5);
    cout << f2() << endl;
    using namespace std::placeholders;
    auto f3 = bind(add, 1, _1); // 函数参数的绑定并不固定，并不一定要全部给出
    cout << "f3(10)=" << f3(10) << endl;
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
    using namespace std::placeholders; // 占位符
    int number = 100;
    auto f = bind(func3, 2, _1, _2, std::cref(number), number);
    number = 300;
    f(20, 30, 400, 50000, 5678); // 对于没有作用的实参是无效的参数
    //输出的结果为（2，20，30，200，100）
    //2是bind的固定绑定
    //20和30是占位符的所输入的参数
    //300 是cref(number)，引用传递，
    //100是原本number的值，bind绑定时是值传递，后续改变number无用
}
int main()
{
    test3();
    return 0;
}