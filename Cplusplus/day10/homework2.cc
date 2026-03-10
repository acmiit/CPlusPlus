#include<iostream>
#include<string.h>
using namespace std;
class CowString{
    class CharProxy{
    public:
        CharProxy(CowString & self,size_t idx)
        :_self(self)
        ,_idx(idx)
        {}
        char & operator=(char ch);
        friend ostream & operator<<(ostream & os,const CharProxy & rhs);
    private:
        CowString & _self;
        size_t _idx;
    };
public:
    CowString();
    ~CowString();
    CowString(const char *pstr);
    CowString(const CowString & other);
    CowString & operator=(const CowString & other);
    CharProxy operator[](size_t idx);

    
    const char * c_str(){return _pstr;}
    size_t size(){return strlen(_pstr);}
    int use_count() {return *(int*)(_pstr-kRefcountLength);}
    friend ostream & operator<<(ostream & os,const CowString & other);
    friend ostream & operator<<(ostream & os,const CharProxy & rhs);
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
CowString::CharProxy CowString::operator[](size_t idx){
    return CharProxy(*this,idx);
}

char & CowString::CharProxy::operator=(char ch){
    if(_idx<_self.size()){
        if(_self.use_count()!=1){
            //引用计数减一
             _self.decreaseRefcount();
            //深拷贝
            char * ptemp=_self.malloc(_self._pstr);
            strcpy(ptemp,_self._pstr);
            //修改指向
            _self._pstr=ptemp;
            _self.initRefcount();
        }
        //执行写操作
        _self._pstr[_idx]=ch;
        return _self._pstr[_idx];
    }else{
        cout<<"out of range"<<endl;
        static char nullchar='\0';
        return nullchar;
    }
}
ostream & operator<<(ostream & os,const CowString::CharProxy & rhs){
    if(rhs._idx<rhs._self.size()){
        os<<rhs._self._pstr[rhs._idx];
    }else{
        os<<"out of range";
    }
    return os;
}


int main(){
    CowString str1("hello");
    CowString str2(str1);
    CowString str3(str1);
    cout<<str1[0]<<endl;

    cout<<str1.use_count()<<endl;
    cout<<str2.use_count()<<endl;
    cout<<str3.use_count()<<endl;
    str1[0]='H';
    cout<<str1[0]<<endl;
    cout<<str2[0]<<endl;
    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str3<<endl;
    
    cout<<str1.use_count()<<endl;
    cout<<str2.use_count()<<endl;
    cout<<str3.use_count()<<endl;

    str1[0]='X';
    cout<<str1<<endl;
    cout<<str1[0]<<endl;

    return 0;
} 