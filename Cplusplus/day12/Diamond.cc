#include<iostream>
using namespace std;
class A
{
public:
    void print()const{
        cout<< "A::print()" <<endl;
    }
    double _a;
};
class B
:public A
{
public:
    double _b;
};
class C
:public A
{
public:
    double _c;
}; 
class D
:public B
,public C
{
public:
    double _d;
};
int main(){
    cout<<sizeof(A)<<endl;
    cout<<sizeof(B)<<endl;
    cout<<sizeof(C)<<endl;
    cout<<sizeof(D)<<endl;

    D d;
    // d.A::print(); //error
    // d.B::print();    //不推荐
    // d.C::print();    //不推荐
    return 0;
}