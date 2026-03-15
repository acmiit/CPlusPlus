#include<iostream>
#include<string.h>
using namespace std;
template<class T>
T add(T t1,T t2){
    return t1+t2;
}

//特化模板,必须要有通用模板
template<>
const char * add<const char *>(const char * p1,const char * p2){
    char *ptemp=new char[strlen(p1)+strlen(p2)+1]();
    strcpy(ptemp,p1);
    strcat(ptemp,p2);
    return ptemp;
}
int main(){
    int x=2,y=3;
    double a=7.9,b=8.2;
    cout<<add(x,y)<<endl;
    cout<<add(a,b)<<endl;
    cout<<add<int>(a,y)<<endl;
    cout<<add<double>(a,y)<<endl;
    const char *p1="hello";
    const char *p2=",world";
    cout<<add(p1,p2)<<endl;
    return 0;
}