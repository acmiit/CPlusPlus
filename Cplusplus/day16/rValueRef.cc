#include<iostream>
using namespace std;
int &&func(){
    return 10;
}
int func2(){
    return 10;
}
int main(){
    // &func(); //error
    // &func2(); //error 无法取址，说明返回的右值引用本身也是一共右值
    int && ref=func();
    &ref; //可以取址，此时ref是一只右值引用，其本身是左值

    return 0;
}