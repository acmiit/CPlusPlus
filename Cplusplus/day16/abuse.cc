 #include<iostream>
#include<string>
#include<memory>
using namespace std;
class Point{
    public:
        Point(int x=0,int y=0)
        :_ix(x)
        ,_iy(y)
        {cout<<"Point(int=0,int=0)"<<endl;}
        void print() const{
            cout<<"("<<_ix<<","<<_iy<<")"<<endl;
        }
        ~Point(){
            cout<<"~Point()"<<endl;
        }
    private:
        int _ix;
        int _iy;
    
};
void test0(){
    //将一个原生裸指针交给多个不同的智能指针，double free问题
    Point *pt=new Point(1,2);
    unique_ptr<Point> up1(pt);
    unique_ptr<Point> up2(pt);
}
int main(){
    test0();
    return 0;
}