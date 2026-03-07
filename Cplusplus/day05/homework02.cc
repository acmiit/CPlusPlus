#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
class Student{
public:
    Student(int id,const char *name)
    :_id(id)
    ,_name(new char[strlen(name)+1]())
    {
        strcpy(_name,name);
        cout<<"Student(int,const char *)"<<endl;
    }
    void * operator new(size_t sz){
        cout<<"void * operator new(size_t)"<<endl;  
        return malloc(sz);
    }
    void operator delete(void * pointer){
        cout<<"void operator delete(void *)"<<endl;
        free(pointer);
    }
    void release(){
        delete this;
    }
    void display() const{
        cout<<"id:"<<_id<<" name:"<<_name<<endl;
    }
private:
    ~Student(){
        if(_name){
            delete [] _name;
            _name=NULL;
        }
        cout<<"~Student"<<endl;
    }
    int _id;
    char *_name;
};
int main(){
    Student *stu=new Student(1,"lisi");
    stu->display();
    stu->release();
    return 0;
}