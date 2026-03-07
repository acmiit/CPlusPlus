#include<iostream>
using namespace std;
class Base{
public:
    Base(int x)
    :_ix(x)
    {}
    Base operator+(const Base & lhs){
        return Base(this->_ix+lhs._ix);
    }
    Base operator-(const Base & lhs){
        return Base(this->_ix-lhs._ix);
    }
    bool operator==(const Base & lhs){
        return this->_ix==lhs._ix;
    }
private:
    int _ix;
};
int main(){
    int i=2,j=7;
    Base x(i),y(j);
    cout<<(x+y==x-y)<<endl;
    return 0;
}