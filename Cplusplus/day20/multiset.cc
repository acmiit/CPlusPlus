#include<iostream>
#include<set>
#include<utility>
#include<vector>
using namespace std;
template <class Container>
void display(const Container &con){
    for(auto & elem:con){
        cout<<elem<<" ";
    }
    cout<<endl;
}
void test0(){
    // set<int,greater<int>> number={1,3,9,8,4,3,2,1,8};
    multiset<int,less<int>> number={1,3,9,8,4,3,2,1,8};
    cout<<"count(1): "<<number.count(1)<<endl;
    cout<<"find(1): "<<(number.find(1)==number.end()?"false":"true")<<endl;
    display(number);

    cout<<endl<<"测试bound函数"<<endl;
    //返回第一个不小于3的迭代器
    auto it=number.lower_bound(3);
    cout<<"*it= "<<*it<<endl;
        //返回第一个大3的迭代器
    auto it2=number.upper_bound(3);
    cout<<"*it2= "<<*it2<<endl;
    //输出等于3，可以计算出3的count
    auto ret0=number.equal_range(3);
    while(ret0.first!=ret0.second){
        cout<<*ret0.first<<" ";
        ++ret0.first;
    }
    cout<<endl;

    //插入
    multiset<int>::iterator ret= number.insert(7);
    display(number);
    vector<int> vec={1,24,234,543,56};
    number.insert(vec.begin(),vec.end());
    display(number);
    number.insert({-1,-2});
    display(number);

    //删除
    number.erase(number.begin()); //删除第一个元素
    number.erase(number.begin(),++number.begin()); //删除第一个元素，左闭右开
    display(number);
    //不支持写操作，防止破坏红黑树的稳定性
    //不支持下标访问
}
int main(){
    test0();
    return 0;
}