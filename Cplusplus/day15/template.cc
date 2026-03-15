#include<iostream>
using namespace std;
template<class T>
T add(T t1,T t2){
    return t1+t2;
}
int main(){
    cout<<add(1,2)<<endl;
    return 0;
}