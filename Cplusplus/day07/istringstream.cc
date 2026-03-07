#include<iostream>
#include<sstream>
#include<string>
using namespace std;
int main(){
    string s("123 456");
    int num=0;
    int num1=0;
    istringstream iss(s);
    iss>>num>>num1;
    cout<<"num: "<<num<<endl;
    cout<<"num1: "<<num1<<endl;
    return 0;
}