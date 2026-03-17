#include<iostream>
#include<memory>
#include<vector>
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
    unique_ptr<int> up(new int(10));
    cout<<"*up:"<<*up<<endl;
    cout<<"up.get()"<<up.get()<<endl;
    cout<<endl;

    //不允许赋值和复制
    // unique_ptr<int> up2=up;     
}

void test1(){
     unique_ptr<Point> up(new Point(4,9));
     vector<unique_ptr<Point>> vec;
     //往vec当中存左值的时候，会发生复制，需要用移动语义才行
     vec.push_back(move(up));
     vec.push_back(unique_ptr<Point>(new Point(2,8)));
}
int main(){
    test1();
    return 0;
}