#include<iostream>
#include<math.h>
class Point{
public:
    Point(int x,int y)
    :_ix(x)
    ,_iy(y)
    {}
    friend float distance(const Point & lhs,const Point & rhs);
private:
    int _ix;
    int _iy;
};
//友元的普通函数 形式
float distance(const Point & lhs,const Point & rhs){
    return sqrt(pow(lhs._ix-rhs._ix,2)+pow(lhs._ix-lhs._iy,2));
}
using namespace std;
int main(){
    Point pt1(1,2),pt2(2,3);
    cout<<distance(pt1,pt2)<<endl;
    return 0;
}