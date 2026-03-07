#include<iostream>
#include<limits>
using namespace std;

void checkInputInt(istream & is,int & number){
    cout<<"please input a int number"<<endl;
    while(is>>number,!is.eof()){
        if(is.bad()){
            cout<<"istream has broken"<<endl;
        }else if(is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"please input a int number"<<endl;
        }else{
            break;
        }
    }
}


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

    friend ostream & operator<<(ostream & os,const Complex & complex);
    friend istream & operator>>(istream & is,Complex & complex);
        
    void display(){
        cout<<_real<<"+"<<_image<<"i"<<endl;
    }
private:
    int _real; 
    int _image;
};

ostream & operator<<(ostream & os,const Complex & complex){
    cout<<complex._real<<"+"<<complex._image<<"i";
    return os;
}

istream & operator>>(istream & is,Complex & complex){
    cout<<"please input a real "<<endl;
    // is>>complex._real;
    checkInputInt(is,complex._real);
    cout<<"please input a image "<<endl;
    // is>>complex._image;
    checkInputInt(is,complex._image);
    return is;
}

int main(){
    Complex c1(1,1),c2(2,2);
    cout<<c1<<endl;
    cin>>c1;
    cout<<c1<<endl;
    return 0;
}