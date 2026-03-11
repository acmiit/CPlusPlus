#include<iostream>
using namespace std;
class Point{
public:
    Point(int x,int y)
    :_ix(x)
    ,_iy(y)
    { cout<<"Point(int,int)"<<endl;}
    void print() const{
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
private:
int _ix;
int _iy;
};
class Point3D
:public Point
{
public:
    Point3D(int x,int y,int z)
    :Point(x,y)
    ,_iz(z)
    {
        cout<<"Point3D(int,int,int)"<<endl;
    }
    void display() const{
        print();
        cout<<_iz<<endl;
    }
private:
    int _iz;
};
void test0(){
    Point pt(1,2);
    Point3D pt3d(1,2,3);
    pt.print();
    pt3d.display();
    pt3d.print();
}
int main(){
    test0();
    return 0;
}