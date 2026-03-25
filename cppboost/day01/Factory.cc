#include <iostream>
#include<memory>
using namespace std;
class Product
{
public:
    Product()
    {
        cout << "Product()" << endl;
    }
    virtual void show() = 0;
    virtual ~Product()
    {
        cout << "~Product()" << endl;
    }
};
class ProductA
    : public Product
{
public:
    ProductA()
    {
        cout << "ProductA()" << endl;
    }
    void show() override
    {
        cout << "ProductA::show()" << endl;
    }
    ~ProductA()
    {
        cout << "~ProductA()" << endl;
    }
};
class ProductB
    : public Product
{
public:
    ProductB()
    {
        cout << "ProductB()" << endl;
    }
    void show() override
    {
        cout << "ProductB::show()" << endl;
    }
    ~ProductB()
    {
        cout << "~ProductB()" << endl;
    }
};
class Factory
{
public:
    Factory()
    {
        cout << "Factory()" << endl;
    }
    virtual Product *createProduct() = 0;
    virtual ~Factory()
    {
        cout << "~Factory()" << endl;
    }
};
class FactoryA
    : public Factory
{
public:
    FactoryA()
    {
        cout << "FactoryA()" << endl;
    }
    Product *createProduct() override
    {
        return new ProductA();
    }
    ~FactoryA()
    {
        cout << "~FactoryA()" << endl;
    }
};
class FactoryB
    : public Factory
{
public:
    FactoryB()
    {
        cout << "FactoryB()" << endl;
    }
    Product *createProduct() override
    {
        return new ProductB();
    }
    ~FactoryB()
    {
        cout << "~FactoryB()" << endl;
    }
};
int main()
{

    unique_ptr<Factory> factoryA(new FactoryA());
    unique_ptr<Product> productA(factoryA->createProduct());
    cout<<endl;
    productA->show();
    cout<<endl;
    unique_ptr<Factory> factoryB(new FactoryB());
    unique_ptr<Product> productB(factoryB->createProduct());
    cout<<endl;
    productB->show();
    cout<<endl;
    return 0;
}