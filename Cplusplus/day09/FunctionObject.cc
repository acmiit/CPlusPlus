#include<iostream>
using namespace std;
class FunctionObject{
public:
    int operator()(){
        cout<<"int operator()()"<<endl;
        return 1;
    };
    void operator()(int x){
        cout<<"void operator(int)"<<endl;
        cout<<x<<endl;
    }
};

int main(){
    FunctionObject fo;
    cout<<fo()<<endl;;
    fo(2);
    return 0;
}