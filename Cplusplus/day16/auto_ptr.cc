#include<iostream>
#include<memory>
using namespace std;
void test0(){
    auto_ptr<int> ap(new int(5));
    cout<<"*ap:"<<*ap<<endl;
}
int main(){
    test0();
    return 0;
}