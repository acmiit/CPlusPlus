#include<iostream>
using namespace std;
class Data{
public:
    Data(){
        cout<<"Data()"<<endl;
    }
    Data(int x)
    :_data(x)
    {
        cout<<"Data(int )"<<endl;
    }
    int getData() const{return _data;}
    ~Data(){cout<<"~Data()"<<endl;}
private:
    int _data=10;
};
class MiddleLayer{
public:
    MiddleLayer(Data *p)
    :_pdata(p)
    {
        cout<<"MiddleLayer(Data *)"<<endl;
    }
    Data * operator->(){
        return _pdata;
    }
    Data operator*(){
        return *_pdata;
    }
    ~MiddleLayer(){
        if(_pdata){
            delete _pdata;
            _pdata=NULL;
        }
        cout<<"~MiddleLayer()"<<endl;
    }
    // friend class ThirdLayer;
private:
    Data * _pdata;
};
class ThirdLayer{
public:
    ThirdLayer(MiddleLayer *ptl)
    :_tl(ptl)
    {
        cout<<"ThirdLayer(MiddleLayer *)"<<endl;
    }
    ~ThirdLayer(){
        if(_tl){
            delete _tl;
            _tl=NULL;
        }
        cout<<"~ThirdLayer"<<endl;
    } 
    MiddleLayer & operator->(){
        return *_tl;
    }
    //两步解引用方案
    // MiddleLayer & operator*(){
    //     return *_tl;
    // }
    //一步解引用方案
     Data  operator*(){
        return *(*_tl);
    }
    
private:
    MiddleLayer *_tl;
};
int main(){
    Data *p=new Data();
    cout<<p->getData()<<endl;
    delete p;
    p=NULL;

    MiddleLayer ml=MiddleLayer(new Data());
    cout<<ml->getData()<<endl;
    cout<<(*ml).getData()<<endl;

    ThirdLayer tl(new MiddleLayer(new Data));
    cout<<tl->getData()<<endl;
    cout<<(*tl).getData()<<endl;;
    return 0;
}