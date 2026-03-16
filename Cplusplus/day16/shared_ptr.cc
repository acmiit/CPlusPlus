#include<iostream>
#include<memory>
#include<vector>
using namespace std;
void test0(){
    shared_ptr<int> sp(new int(10));
    cout<<"*sp:"<<*sp<<endl;
    cout<<sp.get()<<endl;

    shared_ptr<int> sp2=sp;
    //地址一样，公用一片空间
    cout<<"*sp:"<<*sp<<endl;
    cout<<sp.get()<<endl;
    cout<<"*sp:"<<*sp2<<endl;
    cout<<sp2.get()<<endl;

    cout<<sp.use_count()<<endl;
    cout<<sp2.use_count()<<endl;
    cout<<endl;
    shared_ptr<int> sp3(new int(20));
    sp2=sp3;
    cout<<sp.use_count()<<endl;
    cout<<sp2.use_count()<<endl;
    cout<<sp3.use_count()<<endl;

    vector<shared_ptr<int>> vec;
    vec.push_back(sp);
    vec.push_back(sp2);
    vec.push_back(sp3);
    cout<<sp.use_count()<<endl;
    cout<<sp2.use_count()<<endl;
    cout<<sp3.use_count()<<endl;
}
int main(){
    test0();
    return 0;
}