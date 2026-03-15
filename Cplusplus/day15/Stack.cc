#include<iostream>
#include<string.h>
using namespace std;
template<class T,int KCapacity=10>
class Stack{
public:
    Stack()
    :_top(-1)
    ,_data(new T[KCapacity]())
    {
        cout<<"Stack()"<<endl;
    }
    ~Stack(){
        if(_data){
            delete [] _data;
            _top=-1;
        }
        cout<<"~Stack()"<<endl;
    }
    bool empty()const{
        return _top==-1;
    }
    bool full()const{
        return _top==KCapacity-1;
    }
    void push(const T &t){
        if(!full()){
            _data[++_top]=t;
        }else{
            cout<<"Stack is full"<<endl;
        }
 
    }
    void pop();
    T top(){
        if(!empty()){
            return _data[_top];
        }else{
            cout<<"Stack is empty"<<endl;
            return ;
        }
    }

private:
    int _top;
    T *_data;
};
template<class T,int KCapacity>
void Stack<T,KCapacity>::pop(){
    if(empty){
        cout<<"Stack is empty"<<endl;
    }else{
        _top--;
    }
}
int main(){
    Stack<int> stack;
    Stack<long> stack1;
    Stack<string> stack2;
    cout<<stack2.empty()<<endl;
    stack2.push("hello");
    cout<<stack2.empty()<<endl;
    cout<<stack2.top()<<endl;
    return 0;
}