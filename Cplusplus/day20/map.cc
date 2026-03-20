#include<iostream>
#include<map>
#include<utility>
#include<string>
using namespace std;
template <class Container>
void display(const Container &con){
    for(auto & elem:con){
        cout<<elem.first<<" "<<elem.second<<endl;
    }
}
void test0(){
    map<int,string> number={
        {1,"beijing"},
        {10,"nanjing"},
        pair<int ,string>(3,"wuhan"),
        pair<int ,string>(5,"wuhan"),
        make_pair(10,"guangzhou"),
        make_pair(4,"guangzhou")
    };
    display(number);
}
int main(){
    test0();
    return 0;
}