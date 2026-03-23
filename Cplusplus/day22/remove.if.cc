#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool func(int value){
    return value>4;
}
void test(){
    vector<int> vec={1,3,4,6,8,6,3,2};
    //遍历容器
    for_each(vec.begin(),vec.end(),[](int &value){
        cout<<value<<" ";
    });
    cout<<endl;
    //删除大于4的元素，move_if需要和erase配合使用 
    // auto it=remove_if(vec.begin(),vec.end(),bind1st(less<int>(),4));
    auto it=remove_if(vec.begin(),vec.end(),bind2nd(greater<int>(),4));
    // auto it=remove_if(vec.begin(),vec.end(),[](int value){
    //     return value>4;
    // });
    vec.erase(it,vec.end());

    for_each(vec.begin(),vec.end(),[](int &value){
        cout<<value<<" ";
    });
    cout<<endl;
}
int main(){
    test();
    return 0;
}