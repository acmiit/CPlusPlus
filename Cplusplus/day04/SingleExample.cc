 #include<iostream>
 using namespace std;
class Point {
Point(int x,int y)
:_ix(x)
,_iy(y)
{
    cout<<"Point(int,int)"<<endl;
}
~Point(){
    cout<<"~Point()"<<endl;
}
Point(const Point & rhs) = delete;
Point & operator=(const Point & rhs)=delete;
public:
    static Point * getInstance(){
        if(_pInstance==NULL){
            _pInstance=new Point(1,2);
        }
        return _pInstance;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=NULL;
        }
    }
    void display(){
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
private:
    int _ix;
    int _iy;
    static Point * _pInstance;
};
Point * Point::_pInstance= NULL ;

int main(){
    Point *pt1=Point::getInstance();
    Point *pt2=Point::getInstance();
    cout<<pt1<<endl;
    cout<<pt2<<endl;
    pt1->destroy();
    return 0;
}