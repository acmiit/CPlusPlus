#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <memory>
using std::cout;
using std::endl;
using std::find;
using std::list;
using std::string;
using namespace std;
class Observer;
class Subject
{
public:
    virtual void attach(Observer *pObserver) = 0; //添加
    virtual void detach(Observer *pObserver) = 0;//删除
    virtual void notify() = 0;  //发送 
    virtual ~Subject() {}
};
class ConcreteSubject
    : public Subject
{
public:
    void attach(Observer *pObserver) override;
    void detach(Observer *pObserver) override;
    void notify() override;
    void setStatus(int status)
    {
        _status = status;
    }
    int getStatus() const
    {
        return _status;
    }

private:
    list<Observer *> _obList;
    int _status;
};
class Observer
{
public:
    virtual void update(int) = 0;
    virtual ~Observer() {}
};
class ConcreteObserver
    : public Observer
{
public:
    ConcreteObserver(const string &name)
        : _name(name)
    {
    }
    void update(int value)
    {
        cout << "ConcreteObserver " << _name << ", value = " << value << endl;
    }

private:
    string _name;
};
class ConcreteObserver2
    : public Observer
{
public:
    ConcreteObserver2(const string &name)
        : _name(name)
    {
    }
    void update(int value)
    {
        cout << "ConcreteObserver2 " << _name << ", value = " << value << endl;
    }

private:
    string _name;
};
void ConcreteSubject::attach(Observer *pObserver)
{
    _obList.push_back(pObserver);
}

void ConcreteSubject::detach(Observer *pObserver)
{
    for (auto it = _obList.begin(); it != _obList.end(); ++it)
    {
        if (*it == pObserver)
        {
            _obList.remove(pObserver);
            break;
        }
    }
}
void ConcreteSubject::notify()
{
    for (auto &ob : _obList)
    {
        ob->update(_status);
    }
}
void test()
{
    unique_ptr<ConcreteSubject> pSubject(new ConcreteSubject());
    unique_ptr<Observer> pObserver(new ConcreteObserver("lili"));
    unique_ptr<Observer> pObserver2(new ConcreteObserver2("lucy"));
    pSubject->setStatus(2);
    pSubject->attach(pObserver.get());
    pSubject->attach(pObserver2.get());
    pSubject->notify();
    pSubject->detach(pObserver2.get());
    pSubject->setStatus(3);
    pSubject->notify();
}
int main(){
    test();
    return 0;
}