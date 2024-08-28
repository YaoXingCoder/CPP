/*************************************************************************
    > File Name: 03_test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 14时23分37秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 转换中的多态
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    virtual void func() {
        std::cout << "Base::func" << std::endl;
    }
    void display() {
        cout << "Base::display" << endl;
    }

    ~Base() {
        cout << "~Base() 析构" << endl;
    }
};

class Derived : public Base {
public:
    void func() override {
        /* Base::func(); /1* 有作用域限定符, 不经过虚函数表, 直接调用 *1/ */
        std::cout << "Derived::func" << std::endl;
    }
};

/* =============== test =============== */
void test0() {
    Base b1;
    Derived d1;
    Base* pb1;
    Derived* pd1;

    b1 = d1;
    b1.func();
    d1.func();
    b1.display();

    pb1 = &d1;
    pb1->func();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
