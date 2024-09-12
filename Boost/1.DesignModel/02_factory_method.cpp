/*************************************************************************
    > File Name: 01_Simple_factory.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月12日 星期四 16时26分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 简单工厂模式 -> 工厂方法模式
    > Content:
 ************************************************************************/

#include <iostream>
#include <memory>
using namespace std;

enum ProductType { TypeA, TypeB, TypeC };

// 抽象产品类
class Product {
  public:
    virtual void show() = 0; // 抽象类的析构函数设置为虚函数
    virtual ~Product() {}
};

class ProductA : public Product {
  public:
    ProductA() { cout << "ProductA()" << endl; }
    void show() override { cout << "void ProductA::show()" << endl; }
    ~ProductA() { cout << "~ProductA()" << endl; }
};

class ProductB : public Product {
  public:
    ProductB() { cout << "ProductB()" << endl; }
    void show() override { cout << "void ProductB::show()" << endl; }
    ~ProductB() { cout << "~ProductB()" << endl; }
};

class ProductC : public Product {
  public:
    ProductC() { cout << "ProductC()" << endl; }
    void show() override { cout << "void ProductC::show()" << endl; }
    ~ProductC() { cout << "~ProductC()" << endl; }
};

class Factory {
  public:
    virtual Product *createProduct() = 0;
    virtual ~Factory() {};
};

class FactoryA : public Factory {
  public:
    FactoryA() { cout << "FactoryA()" << endl; }
    Product *createProduct() override { return new ProductA(); }
    ~FactoryA() { cout << "~FactoryA()" << endl; }
};

class FactoryB : public Factory {
  public:
    FactoryB() { cout << "FactoryB()" << endl; }
    Product *createProduct() override { return new ProductB(); }
    ~FactoryB() { cout << "~FactoryB()" << endl; }
};

class FactoryC : public Factory {
  public:
    FactoryC() { cout << "FactoryC()" << endl; }
    Product *createProduct() override { return new ProductC(); }
    ~FactoryC() { cout << "~FactoryC()" << endl; }
};

/* =============== test =============== */
void test0() {
    unique_ptr<Factory> factoryA(new FactoryA());
    unique_ptr<Product> pa(factoryA->createProduct());
    pa->show();

    unique_ptr<Factory> factoryB(new FactoryB());
    unique_ptr<Product> pb(factoryB->createProduct());
    pb->show();
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    test0();
    return 0;
}
