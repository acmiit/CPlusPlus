#include<iostream>
#include <unordered_set>
using namespace std;
//容器输出
// class Point;
template <class Container>
void display(const Container &con){
    for(auto & elem:con){
        cout<<elem;
    }
    // cout<<endl;
}

//自定义类型
class Point{
public:
    Point(int x,int y)
    :_ix(x)
    ,_iy(y)
    {}
    friend bool operator==(const Point & lhs,const Point &rhs){
        return lhs._ix==rhs._ix&&rhs._iy==lhs._iy;
    }
    int getX()const{
        return _ix;
    }
    int getY() const{
        return _iy;
    }
    friend ostream &operator<<(ostream &os,const Point & rhs){
         os<<"("<<rhs._ix<<","<<rhs._iy<<")"<<endl;
    }
private:
 int _ix;
 int _iy;
};

namespace std {
    template <>
    class hash<Point> {
     public:
      size_t operator()(const Point &rhs) const
      {
        return hash<int>()(rhs.getX()) ^ (hash<int>()(rhs.getY()) << 1);
      }
    }; 
}

int main(){
    //自定义类型后，需要特化hash和keyEqual(operator==)
    unordered_multiset<Point> number={
        Point(1,2),
        Point(-1,2),
        Point(1,-2),
        Point(-1,-2),
        Point(1,2),
        Point(1,3),
        Point(3,2)
    };
    display(number);
    return 0;
}