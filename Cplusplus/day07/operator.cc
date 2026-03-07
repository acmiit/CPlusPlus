#include<iostream>
using namespace std;
class Complex{
public:
    Complex(int real,int image)
    :_real(real)
    ,_image(image)
    {
        cout<<"Complex(int,int)"<<endl;
    }
    Complex operator+(const Complex & lhs){
        cout<<"Complex operator+(const Complex &)"<<endl;
        return Complex(_real+lhs._real,_image+lhs._image);
    }
    Complex operator-(const Complex & lhs){
        cout<<"Complex operator-(const Complex &)"<<endl;
        return Complex(_real-lhs._real,_image-lhs._image);
    }
    Complex & operator+=(const Complex & lhs){
        this->_real+=lhs._real;
        this->_image+=lhs._image;
        cout<<"Complex operator+=(const Complex &)"<<endl;
        return *this;
    }
    Complex & operator-=(const Complex & lhs){
        this->_real-=lhs._real;
        this->_image-=lhs._image;
        cout<<"Complex operator-=(const Complex &)"<<endl;
        return *this;
    }
    Complex & operator++(){
        this->_real++;
        this->_image++;
        cout<<"Complex operator++()"<<endl;
        return *this;
    }
    Complex & operator++(int){
        Complex temp(*this);
        this->_real++;
        this->_image++;
        cout<<"Complex operator++(int)"<<endl;
        return temp;
    }
    Complex & operator--(){
        this->_real--;
        this->_image--;
        cout<<"Complex operator++()"<<endl;
        return *this;
    }
    Complex operator--(int){
        Complex temp(*this);
        this->_real--;
        this->_image--;
        cout<<"Complex operator++(int)"<<endl;
        return temp;
    }
    void display(){
        cout<<_real<<"+"<<_image<<"i"<<endl;
    }
private:
    int _real;
    int _image;
};

int main(){
    Complex c1(1,1),c2(2,2);
    Complex c3=c1+c2;
    c3.display();
    c3+=c1;
    c3.display();
    c3-=c1;
    c3.display();
    c3++;
    c3.display();
    ++c3;
    c3.display();
    return 0;
}