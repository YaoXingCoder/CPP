/*************************************************************************
    > File Name: 03_abstract_factory.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月12日 星期四 20时09分05秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 抽象工厂
    > Content:
 ************************************************************************/

#include <iostream>

/*
产品A接口
 */
class AbstractProductA {
  public:
    virtual void show() = 0;
    virtual ~AbstractProductA() {}
};

class ProductA1 : public AbstractProductA {
  public:
    void show() override { std::cout << "ProductA1" << std::endl; }
    ~ProductA1() {}
};

class ProductA2 : public AbstractProductA {
  public:
    void show() override { std::cout << "ProductA2" << std::endl; }
    ~ProductA2() {};
};

/*
产品B接口
 */
class AbstraccProductB {
  public:
    virtual void show() = 0;
    virtual ~AbstraccProductB() {}
};

class ProductB1 : public AbstraccProductB {
  public:
    void show() override { std::cout << "ProductB1" << std::endl; }
    ~ProductB1() {}
};

class ProductB2 : public AbstraccProductB {
  public:
    void show() override { std::cout << "ProductB2" << std::endl; }
    ~ProductB2() {}
};

/*
抽象工厂
*/
class AbstractFactory {
  public:
    virtual AbstractProductA *createAbstractProductA() = 0;
    virtual AbstraccProductB *createAbstractProductB() = 0;
    ~AbstractFactory() {}
};

/*
1类型产品生产
*/
class ConcreteFactory1 : public AbstractFactory {
  public:
    AbstractProductA *createAbstractProductA() override {
        return new ProductA1();
    }
    AbstraccProductB *createAbstractProductB() override {
        return new ProductB1();
    }
    ~ConcreteFactory1() {}
};

/*
2类型产品生产
*/
class ConcreteFactory2 : public AbstractFactory {
  public:
    AbstractProductA *createAbstractProductA() override {
        return new ProductA2();
    }
    AbstraccProductB *createAbstractProductB() override {
        return new ProductB2();
    }
    ~ConcreteFactory2() {}
};

/* =============== test =============== */
void test0() {
    AbstractFactory *abf1 = new ConcreteFactory1();
    AbstractProductA *producta1 = abf1->createAbstractProductA();
    AbstraccProductB *productb1 = abf1->createAbstractProductB();
    producta1->show();
    productb1->show();
}

/* =============== main =============== */
int main(int argc, char *argv[]) {
    test0();
    return 0;
}
