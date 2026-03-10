#include<iostream>
using namespace std;

class Line{
public:
    class Point{
    public:
        Point(int x,int y)
        :_ix(x)
        ,_iy(y)
        {}
    private:
        int _ix;
        int _iy;
    };
public:
    Line(int x1,int y1,int x2,int y2)
    :_pt1(x1,y1)
    ,_pt2(x2,y2)
    {}
private:
    Point _pt1;
    Point _pt2;
};  
int main(){
    return 0;
}