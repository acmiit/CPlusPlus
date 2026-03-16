#include<iostream>
#include<memory>
using namespace std;
class Child;
class Parent{
public:
    Parent(){
        cout<<"Parent()"<<endl;
    }
    ~Parent(){
        cout<<"~Parent()"<<endl;
    }
    weak_ptr<Child> _spChild;
};
class Child{
public:
    Child(){
        cout<<"Child()"<<endl;
    }
    ~Child(){
        cout<<"~Child()"<<endl;
    }
    shared_ptr<Parent> _spParent;
};
void test0(){
    shared_ptr<Parent> spParent(new Parent());
    shared_ptr<Child> spChild(new Child());
    cout<<spParent.use_count()<<endl;
    cout<<spChild.use_count()<<endl;
    //相互指向之后，无法释放内存 ，share_ptr强引用计数，其中一个用weak_ptr（不增加引用计数）可解决这个问题
    spParent->_spChild=spChild;
    spChild->_spParent=spParent;
    cout<<spParent.use_count()<<endl;
    cout<<spChild.use_count()<<endl;
}
int main(){
    test0();
    return 0;
}