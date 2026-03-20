#include<iostream>
#include<set>
#include<math.h>
using namespace std;
class Point{
public:
    Point(int x,int y)
    :_ix(x)
    ,_iy(y)
    {
        // cout<<"Point(T,T)"<<endl;
    }
    double getdistance() const{
        return hypot(_ix,_iy);
    }
    friend ostream& operator<<(ostream & os,const Point &rhs){
        os<<"("<<rhs._ix<<","<<rhs._iy<<")";
        return os;
    }
    // friend bool operator<(const Point<T> &lhs,const Point<T> &rhs){
    //     cout<<"bool operator<(const Point,const Point)"<<endl;
    //     if(lhs.getdistance()<rhs.getdistance()){
    //         return true;
    //     }else if(lhs.getdistance()==rhs.getdistance()){
    //         if(lhs._ix<rhs._ix){
    //             return true;
    //         }else if(lhs._ix==rhs._ix){
    //             if(lhs._iy<rhs._iy){
    //                 return true;
    //             }else{
    //                 return false;
    //             }
    //         }else{
    //             return false;
    //         }
    //     }else{
    //         return false;
    //     }
    // }
    friend struct comparePoint;
    int getX() const{
        return _ix;
    }
    int getY() const{
        return _iy;
    }
private:
    int _ix;
    int _iy;
};
template <class Container>
void display(const Container &con){
    for(auto & elem:con){
        cout<<elem<<" ";
    }
    cout<<endl;
}
struct comparePoint
{

    bool operator()(const Point &lhs,const Point &rhs)const{
        cout<<"struct comparePoint"<<endl;
        if(lhs.getdistance()<rhs.getdistance()){
            return true;
        }else if(lhs.getdistance() == rhs.getdistance()){
            if(lhs._ix<rhs._ix){
                return true;
            }else if(lhs._ix==rhs._ix){
                if(lhs._iy<rhs._iy){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};
//命名空间的扩展
namespace std{
    //模板的特化,全特化
template<>
struct less<Point>{
    bool operator()(const Point &lhs,const Point &rhs)const{
        cout<<"struct less<Point>"<<endl;
        if(lhs.getdistance()<rhs.getdistance()){
            return true;
        }else if(lhs.getdistance() == rhs.getdistance()){
            if(lhs.getX()<rhs.getX()){
                return true;
            }else if(lhs.getX()==rhs.getX()){
                if(lhs.getY()<rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};
}
int main(){
    //三种：比较运算符重载，自定义比较函数对象，特化模板
    set<Point> number={
        Point(1,2),
        Point(-1,2),
        Point(1,2),
        Point(3,2),
        Point(3,3),
        Point(-3,2)
    };
    display(number);
    return 0;
}