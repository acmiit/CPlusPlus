#include<iostream>
#include<string.h>
using namespace std;
class Person{
public:
    Person(const char * name,int age)
    :_name(new char[strlen(name)+1]())
    ,_age(age)
    {   
        strcpy(_name,name);
        cout<<"Person(const char *,int)"<<endl;
    }
    Person(const Person &rhs)
    :_name(new char[strlen(rhs._name)+1]())
    ,_age(rhs._age)
    {
        strcpy(_name,rhs._name);
        cout<<"Person(const Person &)"<<endl;
    }
    Person & operator=(const Person &rhs){
        if(this!=&rhs){
            delete [] _name;
            _name=new char[strlen(rhs._name)+1]();
            strcpy(_name,rhs._name);
            _age=rhs._age;
        }
        cout<<"Person & operator=(const Person &)"<<endl;
        return *this;
    }
    virtual ~Person(){
        if(_name){
            delete [] _name;
            _name=NULL;
        }
        cout<<"Person"<<endl;
    }
    virtual void display() const{
        cout<<"姓名："<<_name<<"年龄："<<_age<<endl;
    }
private:
    char * _name;
    int _age;
};
class Employee
:public Person
{
public:
    Employee(const char * name,int age,const char * department,double salary)
    :Person(name,age)
    ,_department(new char[strlen(department)+1]())
    ,_salary(salary)
    {   
        if(department){
            strcpy(_department,department);
        }
        cout<<"Employee(string,int,string,double)"<<endl;
    }
    Employee(const Employee & rhs)
    :Person(rhs)
    ,_department(new char [strlen(rhs._department)+1]())
    ,_salary(rhs._salary)
    {
        strcpy(_department,rhs._department);
        cout<<"Employee(const Employee &)"<<endl;
    }
    Employee & operator=(const Employee & rhs){
        if(this!=&rhs){
            Person::operator=(rhs);
            delete [] _department;
            _department=new char [strlen(rhs._department)+1]();
            strcpy(_department,rhs._department);
            _salary=rhs._salary;
        }
        cout<<"Employee& operator=(const Empolyee &)"<<endl;
        return *this;
    }
    ~Employee(){
        if(_department){
            delete [] _department;
        }
        cout<<"~Employee()"<<endl;
    }
    void display() const override{
        Person::display();
        cout<<"部门："<<_department<<"薪资："<<_salary<<endl;
    }
private:
    char * _department;
    double _salary;
};
int main()
{
    Employee ey1("ryc",22,"C++",6.66);
    Employee ey2("syf",23,"java",2.50);
    Employee ey3("gyh",21,"boss",666);
 
    ey1 = ey3;
    Employee ey4(ey2);
    // /* ey1.Employee::display(); */
    // /* ey2.Employee::display(); */
    // /* ey3.Employee::display(); */
    // /* ey4.Employee::display(); */
    ey1.display();
    ey2.display();
    ey3.display();
    ey4.display();
    return 0;
} 
