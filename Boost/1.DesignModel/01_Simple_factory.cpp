/*************************************************************************
    > File Name: 01_Simple_factory.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月12日 星期四 16时26分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 简单工厂模式
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

class ProductFactory {
  public:
    static unique_ptr<Product> createProduct(ProductType type) {
        switch (type) {
        case TypeA:
            return unique_ptr<Product>(new ProductA());
        case TypeB:
            return unique_ptr<Product>(new ProductB());
        case TypeC:
            return unique_ptr<Product>(new ProductC());
        default:
            return unique_ptr<Product>(nullptr);
        }
    }
};

/* =============== test =============== */
void test0() {
    unique_ptr<Product> pa = ProductFactory::createProduct(TypeA);
    unique_ptr<Product> pb = ProductFactory::createProduct(TypeB);
    unique_ptr<Product> pc = ProductFactory::createProduct(TypeC);
    pa->show();
    pb->show();
    pc->show();
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    test0();
    return 0;
}
