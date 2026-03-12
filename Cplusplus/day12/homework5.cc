#include<iostream>
#include<string>
using namespace std;
class Person{
public:
    Person(string name,int age)
    :_name(name)
    ,_age(age)
    {
        cout<<"Person(string,int)"<<endl;
    }
    ~Person(){
        cout<<"~Person()"<<endl;
    }
    void display(){
        cout<<"姓名: "<<_name<<"年龄: "<<_age<<endl;
    }
private:
    string _name;
    int _age;
};
class Employee
:public Person
{
public:
    Employee(string name,int age,string department,double salary)
    :Person(name,age)
    ,_department(department)
    ,_salary(salary)
    {
        cout<<"Emplyee(string,int,string,double)"<<endl;
    }
    ~Employee(){
        cout<<"~Emplyee()"<<endl;
    }
    void display(){
        Person::display();
        cout<<"部门："<<_department<<"工资："<<_salary<<endl;
    }
private:
    string _department;
    double _salary;
};
int main(){
    Employee ey1("ryc",22,"C++",6.66);
    Employee ey2("syf",23,"java",2.50);
    Employee ey3("gyh",21,"boss",666);
 
    ey1.Employee::display();
    ey2.Employee::display();
    ey3.Employee::display();
    return 0;
}