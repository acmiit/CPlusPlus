#include<iostream>
#include<string.h>
using namespace std;
class CowString{
public:
    CowString();
    ~CowString();
    CowString(const char *pstr);
    CowString(const CowString & other);
    CowString & operator=(const CowString & other);
    char & operator[](size_t idx);

    
    const char * c_str(){return _pstr;}
    size_t size(){return strlen(_pstr);}
    int use_count() {return *(int*)(_pstr-kRefcountLength);}
    friend ostream & operator<<(ostream & os,const CowString & other);
private:
    char * malloc(const char * pstr=NULL){
        if(pstr){
            return new char[strlen(pstr)+1+kRefcountLength]()+kRefcountLength;
        }else{
            return new char[1+kRefcountLength]()+kRefcountLength;
        }
    }
    void release(){
        decreaseRefcount();
        if(use_count()==0){
            delete [] (_pstr-kRefcountLength);
            cout<<"delete heap"<<endl;
        }
    }

    void initRefcount(){
        *(int*)(_pstr-kRefcountLength)=1;
    }
    void increaseRefcount(){
        ++*(int*)(_pstr-kRefcountLength);
    }
    void decreaseRefcount(){
        --*(int*)(_pstr-kRefcountLength);
    }
    static const int kRefcountLength=4;
    char * _pstr;
};
ostream & operator<<(ostream & os,const CowString & other){
    os<<other._pstr;
    return os;
}
CowString::CowString()
:_pstr(malloc())
{
    cout<<"CowString()"<<endl;
    initRefcount();
}
CowString::~CowString(){
    release();
}
CowString::CowString(const CowString & other)
:_pstr(other._pstr) //浅拷贝
{
    cout<<"CowString(const CowString &)"<<endl;
    increaseRefcount();
}
CowString::CowString(const char *pstr)
:_pstr(malloc(pstr))
{
    cout<<"CowString(const char *)"<<endl;
    strcpy(_pstr,pstr);
    initRefcount();
}
CowString & CowString::operator=(const CowString & other){
    if(this!=&other){
        cout<<"CowString& operaotr=(const CowString &)"<<endl;
        release();
        _pstr=other._pstr;
        increaseRefcount();
    }
    return *this;
}
char & CowString::operator[](size_t idx){
    if(idx<size()){
        return _pstr[idx];
    }else{
        cout<<"out of range"<<endl;
        static char nullchar='\0';
        return nullchar;
    }
}
int main(){
    CowString str1;
    CowString str2=str1;
    cout<<"str1:"<<str1<<endl;
    cout<<"str2:"<<str2<<endl;
    cout<<str1.use_count()<<endl; 
    cout<<str2.use_count()<<endl; 
    cout<<"-------------------"<<endl;

    CowString str3("hello");
    CowString str4=str3;
    cout<<"str3:"<<str3<<endl;
    cout<<"str4:"<<str4<<endl;
    cout<<str3.use_count()<<endl; 
    cout<<str4.use_count()<<endl; 
    cout<<"-------------------"<<endl;

    str1=str3;
    cout<<"str1:"<<str1<<endl;
    cout<<"str2:"<<str2<<endl;
    cout<<"str3:"<<str3<<endl;
    cout<<"str4:"<<str4<<endl;
    cout<<str1.use_count()<<endl; 
    cout<<str2.use_count()<<endl; 
    cout<<str3.use_count()<<endl; 
    cout<<str4.use_count()<<endl; 
    return 0;
}