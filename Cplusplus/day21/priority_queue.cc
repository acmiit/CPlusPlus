#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
class Point
{
public:
    Point(int x, int y)
        : _ix(x), _iy(y)
    {
    }
    double getdistance() const
    {
        return hypot(_ix, _iy);
    }
    friend ostream &operator<<(ostream &os, const Point &rhs)
    {
        os << "(" << rhs._ix << "," << rhs._iy << ")";
        return os;
    }
    friend bool operator<(const Point &lhs, const Point &rhs)
    {
        cout << "bool operator<(const Point,const Point)" << endl;
        if (lhs.getdistance() < rhs.getdistance())
        {
            return true;
        }
        else if (lhs.getdistance() == rhs.getdistance())
        {
            if (lhs._ix < rhs._ix)
            {
                return true;
            }
            else if (lhs._ix == rhs._ix)
            {
                if (lhs._iy < rhs._iy)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    friend struct comparePoint;
    int getX() const
    {
        return _ix;
    }
    int getY() const
    {
        return _iy;
    }

private:
    int _ix;
    int _iy;
};
void test0()
{
    // 底层使用得到是堆排序，默认是less,大根堆
    // 底层默认使用的是vector
    vector<Point> vec = {
        Point(1,2),
        Point(-1,2),
        Point(1,-2),
        Point(-1,-2),
        Point(1,1),
        Point(2,2),
    };
    priority_queue<Point> pque(vec.begin(), vec.end());
    while (!pque.empty())
    {
        cout << pque.top() << endl;
        pque.pop();
    }
}
int main()
{
    test0();
    return 0;
}