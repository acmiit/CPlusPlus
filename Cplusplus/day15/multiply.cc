#include<iostream>
using namespace std;
template<class T,int kBase=1>
T multiply(T t1,T t2){
    return t1*t2*kBase;
}
int main(){
    //当kBase没有赋默认值时，只能显式实例化
    cout<<multiply<int,10>(1,2)<<endl;
    //赋默认值之后，可以隐式实例化
    cout<<multiply(1.2,1.2)<<endl;
    return 0;
}