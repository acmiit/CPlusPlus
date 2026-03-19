#include<iostream>
#include<vector>
using namespace std;
void test0(){
    vector<int> number={1,3,4,4,4,5,4,4,7};
    for(auto &it:number){
        cout<<it<<" ";
    }
    cout<<endl;
    auto it=number.begin();
    while(it!=number.end()){
        if(4==*it){
            number.erase(it);
        }else{
            ++it;
        }
    }
    for(auto &it:number){
        cout<<it<<" ";
    }
    cout<<endl;
    number.clear();
    number.shrink_to_fit();
    cout<<"size: "<<number.size()<<endl;
    cout<<"capcity: "<<number.capacity()<<endl;
}
class Point{
public:
    Point(int x=0,int y=0)
    :_ix(x)
    ,_iy(y)
    {
        cout<<"Point(int =0,int =0)"<<endl;
    }
    Point(const Point & rhs)
    :_ix(rhs._ix)
    ,_iy(rhs._iy)
    {
        cout<<"Point(const Point &)"<<endl;
    }
    Point(Point && rhs)
    :_ix(rhs._ix)
    ,_iy(rhs._iy)
    {
        cout<<"Point(const Point &&)"<<endl;
    }
private:
    int _ix;
    int _iy;
};
void test1(){
    vector<Point> vec;
    vec.push_back(Point(1,2));
    cout<<"--------------"<<endl;
    vec.emplace_back(Point(3,4));
    cout<<"--------------"<<endl;
    //因为重新分配了
    vec.emplace_back(5,6);
    cout<<"--------------"<<endl;
    vec.emplace_back(5,6);
}
int main(){
    test1();
    return 0;
}