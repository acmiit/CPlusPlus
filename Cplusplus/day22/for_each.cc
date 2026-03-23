#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>
using namespace std;

void fun(int x){
    cout<<x<<" ";

}
void test(){
    vector<int> vec={1,3,5,3,5,6};
    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    // for_each(vec.begin(),vec.end(),fun);
    //lambda表达式-------->匿名函数
    for_each(vec.begin(),vec.end(),[](int &value){
        ++value;
        cout<<value<<" ";
    });
    cout<<endl;
    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
}
int main(){
    test();
    return 0;
}