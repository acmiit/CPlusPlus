#include"Line.hpp"
#include<iostream>
using namespace std;
class Line::LineImpl{
public:
    class Point{
    public:
        Point(int x,int y)
        :_ix(x)
        ,_iy(y){}
        void print () const{
            cout<<"("<<_ix<<","<<_iy<<")";
        }
    private:
        int _ix;
        int _iy;
    };
public:
    LineImpl(int x1,int y1 ,int x2,int y2)
    :_pt1(x1,y1)
    ,_pt2(x2,y2)
    {}
    ~LineImpl(){}
    void printLine(){
        _pt1.print();
        cout<<"-------->";
        _pt2.print();
        cout<<endl;
    }
private:
    Point _pt1;
    Point _pt2;
    double length=10;
};
Line::Line(int x1,int y1,int x2,int y2)
:_pimpl(new LineImpl(x1,y1,x2,y2))
{}
Line::~Line(){
    if(_pimpl){
        delete _pimpl;
        _pimpl=NULL;
    }
}

void Line::printLine() const{
    _pimpl->printLine();
}
