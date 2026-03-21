#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <cmath>
using namespace std;
template <class Container>
void display(const Container &con)
{
    for (auto &elem : con)
    {
        cout << elem.first << " " << elem.second << endl;
    }
}
class Point
{
public:
    Point(int x, int y)
        : _ix(x), _iy(y)
    {
        // cout<<"Point(T,T)"<<endl;
    }
    double getdistance() const
    {
        return hypot(_ix, _iy);
    }
    friend ostream &operator<<(ostream &os, const Point &rhs)
    {
        os << "(" << rhs._ix << "," << rhs._iy << ")";
        return os;
    }
    // friend bool operator<(const Point &lhs,const Point &rhs){
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
    int getX() const
    {
        return _ix;
    }
    int getY() const
    {
        return _iy;
    }

private:
    int _ix;
    int _iy;
};

// template <class Container>
// void display(const Container &con){
//     for(auto & elem:con){
//         cout<<elem<<" ";
//     }
//     cout<<endl;
// }
// struct comparePoint
// {

//     bool operator()(const Point &lhs,const Point &rhs)const{
//         cout<<"struct comparePoint"<<endl;
//         if(lhs.getdistance()<rhs.getdistance()){
//             return true;
//         }else if(lhs.getdistance() == rhs.getdistance()){
//             if(lhs._ix<rhs._ix){
//                 return true;
//             }else if(lhs._ix==rhs._ix){
//                 if(lhs._iy<rhs._iy){
//                     return true;
//                 }else{
//                     return false;
//                 }
//             }else{
//                 return false;
//             }
//         }else{
//             return false;
//         }
//     }
// };
void test0()
{
    multimap<int, string> number = {
        {1, "beijing"},
        {10, "nanjing"},
        pair<int, string>(3, "wuhan"),
        pair<int, string>(5, "wuhan"),
        make_pair(10, "guangzhou"),
        make_pair(4, "guangzhou")};
    display(number);
}
void test1()
{
    multimap<string, Point> number{
        {"beijing", Point(1, 2)},
        {"nanjing", Point(1, -2)},
        pair<string, Point>("hubei", Point(-1, 2)),
        pair<string, Point>("huibei", Point(-1, 2)),
        make_pair("hainan", Point(1, 3)),
        make_pair("henan", Point(3, 3))};
    display(number);
}
int main()
{
    test1();
    return 0;
}