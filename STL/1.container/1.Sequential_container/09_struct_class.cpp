/*************************************************************************
    > File Name: 09_struct_class.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 14时42分25秒
    > Mail: JiaZiChunQiu@163.com
    > Title: struct 结构体默认继承为 public
    > Content:
 ************************************************************************/

#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base()" << std::endl;
    }
public:
    void print() {
        std::cout << "void Base::print()" << std::endl;
    }
};

struct Derived : Base {

};

/* =============== test =============== */
void test0() {
    Base();
    Derived d;
    d.print();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
