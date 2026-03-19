#include<deque>
#include<iostream>
using namespace std;
//初始化list、deque、vector是一样的
//遍历只有list没有下标访问
//尾部插入和删除，vector、deque、list三个容器是一样的
template <class Container>
void display(const Container &con){
    for(auto & elem:con){
        cout<<elem<<" ";
    }
    cout<<endl;
}
void test0(){
    //1、初始化
    //1.1 创建一个空对象
    // deque<int> number;
    //1.2创建一个count个value
    // deque<int> number(10); //（count）
    // deque<int> number(10,0);//(count,value)
    //1.3迭代器范围 左闭右开 [,)
    // int arr[10]={1,1,3,4,5,6,7,8,9,10};
    // deque<int> number(arr,arr+10);
    //1.4大括号
    deque<int> number{1,2,3,4,5,6,7,8,9,10};
    //2.遍历
    //2.1下标
    // for(size_t idx=0;idx<number.size();++idx){
    //     cout<<number[idx]<<" ";
    // }
    // cout<<endl;
    // //2.2迭代器
    // deque<int>::iterator it=number.begin();
    // for(;it!=number.end();++it){
    //     cout<<*it<<" ";
    // }
    // cout<<endl;
    // //增强for循环
    // for(int &it:number){
    //     cout<<it<<" ";
    // }
    // cout<<endl;

    display(number);
    //3.尾插入
    number.push_back(110);
    number.push_back(1110);
    display(number);
    //4.尾删除
    number.pop_back();
    display(number);
    //3.头插入
    number.push_front(110);
    number.push_front(1110);
    display(number);
    //4.头删除
    number.pop_front();
    display(number);

}
int main(){
    test0();
    return 0;
}