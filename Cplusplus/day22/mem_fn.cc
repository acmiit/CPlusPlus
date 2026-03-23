#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
class Number
{
public:
    Number(size_t data = 0)
        : _data(data)
    {
    }
    void print() const
    {
        cout << _data << " ";
    }
    bool isEven() const
    {
        return (0 == _data % 2);
    }
    bool isPrime() const
    {
        if (1 == _data)
        {
            return false;
        }
        // 质数/素数
        for (size_t idx = 2; idx <= _data / 2; ++idx)
        {
            if (0 == _data % idx)
            {
                return false;
            }
        }
        return true;
    }

private:
    size_t _data;
};
void test()
{
    vector<Number> numbers;
    for (size_t idx = 1; idx != 10; ++idx)
    {
        numbers.push_back(Number(idx));
    }
    // 遍历
    std::for_each(numbers.begin(), numbers.end(), mem_fn(&Number::print));
    // erase函数参数之前说过，两个参数，
    cout << endl;
    // 删除偶数
    numbers.erase(remove_if(numbers.begin(), numbers.end(),
                            mem_fn(&Number::isEven)),
                  numbers.end());

    // 遍历
    std::for_each(numbers.begin(), numbers.end(), mem_fn(&Number::print));
    cout << endl;
    // 删除素数
    numbers.erase(remove_if(numbers.begin(), numbers.end(),
                            mem_fn(&Number::isPrime)),
                  numbers.end());
    // 遍历
    std::for_each(numbers.begin(), numbers.end(), mem_fn(&Number::print));
    cout << endl;
}
int main()
{
    test();
    return 0;
}