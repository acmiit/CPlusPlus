#include<iostream>
#include<cstring>
using namespace std;
class String 
{
public:
    String()
    :_pstr(new char[1]())
    {_pstr[0]='\0';};
    String(const char * pstr)
    {
        if(pstr==NULL){
            _pstr=new char[1]();
            _pstr[0]='\0';
        }else{
            _pstr=new char[strlen(pstr)+1]();
            strcpy(_pstr,pstr);
        }
    }
    //拷贝构造函数
    String(const String & other){
        _pstr=new char[strlen(other._pstr)+1]();
        strcpy(_pstr,other._pstr);
    }
    ~String(){
        delete [] _pstr;
    }
    //拷贝赋值运算符
    String &operator=(const String &other){
        if(this!=&other){
            delete [] _pstr;
            _pstr = new char[strlen(other._pstr) + 1];
            strcpy(_pstr, other._pstr);
        }
        return *this;
    }
    String &operator=(const char * pstr){
        if(pstr==NULL){
            delete [] _pstr;
            _pstr=new char[1]();
            _pstr[0]='\0';
        }else{
            delete [] _pstr;
            _pstr=new char[strlen(pstr)+1]();
            strcpy(_pstr,pstr);
        }
        return *this;
    }
 
    String &operator+=(const String &other){
        char * temp=new char[strlen(other._pstr)+strlen(_pstr)+1]();
        strcpy(temp,_pstr);
        strcat(temp,other._pstr);
        delete [] _pstr;
        _pstr=temp;
        return *this;

    }
    String &operator+=(const char * pstr){
        if(pstr){
            char *temp = new char[strlen(_pstr) + strlen(pstr) + 1];
            strcpy(temp, _pstr);
            strcat(temp, pstr);
            delete[] _pstr;
            _pstr = temp;
        }
        return *this;
    }
     
    char &operator[](std::size_t index){
        return _pstr[index];
    }
    const char &operator[](std::size_t index) const{
        return _pstr[index];
    }
     
    std::size_t size() const{
        return strlen(_pstr);
    }
    const char* c_str() const{
        return _pstr;
    }
     
    friend bool operator==(const String &lhs, const String &rhs){
        return strcmp(lhs._pstr,rhs._pstr)==0;
    }
    friend bool operator!=(const String &lhs, const String &rhs){
        return !(rhs==lhs);
    }
     
    friend bool operator<(const String &lhs, const String &rhs){
        return strcmp(lhs._pstr,rhs._pstr)<0;
    }
    friend bool operator>(const String &lhs, const String &rhs){
        return strcmp(lhs._pstr,rhs._pstr)>0;
    }
    friend bool operator<=(const String &lhs, const String &rhs){
        return strcmp(lhs._pstr,rhs._pstr)<=0;
    }
    friend bool operator>=(const String &lhs, const String &rhs){
        return strcmp(lhs._pstr,rhs._pstr)>=0;
    }
     
    friend std::ostream &operator<<(std::ostream &os, const String &s){
        os << s._pstr;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, String &s){
        char buffer[1024];
        is >> buffer;
        s = buffer;  // 使用赋值运算符
        return is;
    }
 
private:
    char * _pstr;
};
 
String operator+(const String &lhs, const String &rhs){
    String result(lhs);
    result+=rhs;
    return result;
}
String operator+(const String &lhs, const char *rhs){
    String result(lhs);
    result+=rhs;
    return result;
}
String operator+(const char *lhs, const String &rhs){
    String result(lhs);
    result+=rhs;
    return result;
}

int main(){
        // 测试各种构造函数
        String s1;                // 默认构造
        String s2("Hello");       // 从C字符串构造
        String s3 = s2;           // 拷贝构造
        String s4 = "World";      // 隐式转换
        
        cout << "s1: " << s1 << endl;
        cout << "s2: " << s2 << endl;
        cout << "s3: " << s3 << endl;
        cout << "s4: " << s4 << endl;
        
        // 测试赋值运算符
        s1 = s2;                  // 从String赋值
        cout << "s1 = s2: " << s1 << endl;
        
        s1 = "New String";        // 从C字符串赋值
        cout << "s1 = \"New String\": " << s1 << endl;
        
        // 测试复合赋值
        s1 += " ";
        s1 += s4;
        cout << "s1 += \" \" += s4: " << s1 << endl;
        
        // 测试加法运算符
        String s5 = s2 + " " + s4;
        cout << "s5 = s2 + \" \" + s4: " << s5 << endl;
        
        String s6 = "Start: " + s5;
        cout << "s6 = \"Start: \" + s5: " << s6 << endl;
        
        // 测试下标运算符
        cout << "s2[0]: " << s2[0] << endl;
        s2[0] = 'h';  // 修改
        cout << "After s2[0] = 'h': " << s2 << endl;
        
        // 测试比较运算符
        cout << "s2 == s3: " << (s2 == s3) << endl;
        cout << "s2 != s4: " << (s2 != s4) << endl;
        cout << "s2 < s4: " << (s2 < s4) << endl;
        cout << "s2 > s4: " << (s2 > s4) << endl;
        
        // 测试size和c_str
        cout << "s5.size(): " << s5.size() << endl;
        cout << "s5.c_str(): " << s5.c_str() << endl;
    return 0;
}