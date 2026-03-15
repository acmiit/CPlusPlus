#include<iostream>
using namespace std;
class Point{
public:
    Point(double x,double y)
    :_x(x)
    ,_y(y)
    {}
    template <class T=int>
    T convert(){
        return _x;
    }
    template<class T>
    T add(T t1){
        return _x+_y+t1;
    }
private:
    double _x;
    double _y;
};
int main(){
    Point p(1.2,3.2);
    cout<<p.convert()<<endl;
    cout<<p.add(1.1)<<endl;
    return 0;
} 