#include<iostream>
#include<memory>
#include<vector>
using namespace std;
void test0(){
    shared_ptr<int> sp(new int(10));
    weak_ptr<int> wp;
    wp=sp;
    cout<<wp.use_count()<<endl;
    cout<<sp.use_count()<<endl;
    // cout<<*wp.lock().get()<<endl;
    *wp.lock()=20;
    cout<<*sp.get()<<endl;
    cout<<*sp<<endl;
    cout<<wp.use_count()<<endl;
    cout<<sp.use_count()<<endl;
    cout<<wp.lock().use_count()<<endl;
    wp.expired(); //等价于 wp.use_count()==0
}
int main(){
    test0();
    return 0;
}