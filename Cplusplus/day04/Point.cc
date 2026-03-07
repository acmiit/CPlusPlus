#include<iostream>
using namespace std;
class Point{
public:
    //默认构造函数
    Point()
    {
        cout<<"Point()"<<endl;
    }
    //构造函数Point(int ,int )
    Point(int ix,int iy)
    :_ix(ix)
    ,_iy(iy)
    {
        cout<<"Point(int ,int )"<<endl;
    }
    ~Point(){
        cout<<"~Point()"<<endl;
    }
    //拷贝构造函数
    Point(const Point & rhs)
    :_ix(rhs._ix)
    ,_iy(rhs._iy)
    {
        cout<<"Point(const Point & )"<<endl;
    }
    //赋值运算符函数
    Point & operator=(const Point & rhs){
        //防止自赋值
        if(this!=&rhs){
            this->_ix=rhs._ix;
            this->_iy=rhs._iy;
        }
        cout<<"Point & operator=(const Point & )"<<endl;
        return *this;
    }
    //比较运算符
    bool operator==(const Point & rhs){
        cout<<"bool operator==(const Point &)"<<endl;
        return (_ix==rhs._ix)&&(_iy==rhs._iy);
    }
    bool operator!=(const Point & rhs){
        cout<<"bool operator!=(const Point &)"<<endl;
        return !(*this == rhs);
    }
    //算术运算符
    Point operator+(const Point & rhs){
        cout<<"Point operator+(const Point &)"<<endl;
        return Point(_ix+rhs._ix,_iy+rhs._iy);
    }

    Point operator-(const Point & rhs){
        cout<<"Point operator-(const Point &)"<<endl;
        return Point(_ix-rhs._ix,_iy-rhs._iy);
    }

    //复合赋值运算符
    Point operator+=(const Point & rhs){
        _ix+=rhs._ix;
        _iy+=rhs._iy;
        cout<<"Point operator+=(const Point &)"<<endl;
        return *this;
    }
    Point operator-=(const Point & rhs){
        _ix-=rhs._ix;
        _iy-=rhs._iy;
        cout<<"Point operator-=(const Point &)"<<endl;
        return *this;
    }

    // 8. 流输出运算符（友元函数）
    friend std::ostream& operator<<(std::ostream &os, const Point &p);
    //访问器函数
    int getX() const{ return _ix;}
    int getY() const{ return _iy;}

    int setX(int xVal){_ix=xVal;}
    int setY(int yVal){_iy=yVal;}

    //打印函数
    void display() const{
        cout<<"Point("<<_ix<<","<<_iy<<")"<<endl;
    }

private:
    int _ix;
    int _iy;
};
// 流输出运算符实现
std::ostream& operator<<(std::ostream &os, const Point &p) {
    os << "Point(" << p._ix << ", " << p._iy << ")";
    return os;
}
int main(){
    std::cout << "=== 创建点对象 ===" << std::endl;
    Point p1;                 // 默认构造
    Point p2(3, 4);       // 带参构造
    Point p3(p2);             // 拷贝构造
    
    std::cout << "\n=== 运算符使用 ===" << std::endl;
    p1 = p2;                  // 赋值运算符
    Point p4 = p1 + p2;       // 加法运算符
    p4 += p1;                 // 复合加法
    
    std::cout << "\n=== 比较运算 ===" << std::endl;
    if (p1 == p2) {
        std::cout << "p1 等于 p2" << std::endl;
    }
    
    std::cout << "\n=== 流输出 ===" << std::endl;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;
    std::cout << "p4: " << p4 << std::endl;
    
    std::cout << "\n=== 程序结束，析构顺序 ===" << std::endl;

    return 0;
}