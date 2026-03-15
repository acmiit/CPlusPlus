#include<iostream>
using namespace std;
template<class T>
T add(T t1,T t2){
    cout<<"class T"<<endl;
    return t1+t2;
}

template<class T1,class T2>
T1 add(T1 t1,T2 t2){
    cout<<"clas T1 class T2"<<endl;
    return t1+t2;
}
int main(){
    short s1=1,s2=2;
    int i1=3,i2=4;
    long l1=5,l2=6;
    double d1=1.4,d2=2.8;
    cout<<add(d1,i2)<<endl;
    cout<<add(i1,d2)<<endl;

    cout<<"------"<<endl;
    int x=10;
    double y=9.2;
    //有两个参数的显示实例化就是模板二
    cout<<add<int,int>(x,y)<<endl;
    cout<<add<int,double>(x,y)<<endl;
    //指定了T1类型为int，没有指定T2类型
    cout<<add<int>(x,y)<<endl;
    //指定了返回类型是int，对照模板二，发现第一个参数也得是int，实际传入的是double
    //再对照一，模板一只有一个类型参数
    //就直接使用了（对y进行类型转换）
    //注意：不推荐如下  写法
    cout<<add<int>(y,x)<<endl;
    return 0;
}