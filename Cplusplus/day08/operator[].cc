#include<iostream>
#include<string.h>
using namespace std;
class CharArray{
public:
    CharArray(char * data)
    :_capacity(strlen(data)+1)
    ,_data(new char[_capacity]())
    {
        strcpy(_data,data);
    }
    ~CharArray(){
        if(_data){
            delete [] _data;
            _data=NULL;
        }
    }
    void display(){
        cout<<_data<<endl;
    }
    const char & operator[](size_t idx) const{
        if(idx<_capacity-1)
        {
            return _data[idx];
        }else{
            cout<<"out of range"<<endl;
            static char nullchar ='\0';
            return nullchar;
        }

    }
private:
    size_t _capacity;
    char * _data;
};
int main(){
    char arr[6]="Hello";
    CharArray c(arr);
    c.display();
    // c[0]='W';
    cout<<c[0]<<endl;
    cout<<c.operator[](10)<<endl;
    return 0;
}