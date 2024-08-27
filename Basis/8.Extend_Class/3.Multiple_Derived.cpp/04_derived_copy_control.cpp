/*************************************************************************
    > File Name: 04_derived_copy_control.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 19时35分45秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 派生类之间的复制控制
    > Content:
    >   1.复制控制函数就是 拷贝构造函数、赋值运算符函数
    >   2.（1）当派生类中没有显式定义复制控制函数时，就会自动完成基类部分的复制控制操作；
    >   3.（2）当派生类中有显式定义复制控制函数时，不会再自动完成基类部分的复制控制操作，需要显式地调用；
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base(long base = 10) : _base(base) {}

    void print() const {
        cout << "Base::_base:" << _base << endl;
    }

protected:
    long _base = 10;
};


class Derived : public Base {
public:
    Derived(long base, long derived) 
        : Base(base) 
        , _derived(derived) 
    {}

    Derived(const Derived & rhs)
    : Base(rhs) // 调用Base的拷贝构造
    , _derived(rhs._derived)
    {
        cout << "Derived(const Derived & rhs)" << endl;
    }

    Derived &operator=(const Derived & rhs){
        Base::operator=(rhs); // 调用Base的赋值运算符函数
        _derived = rhs._derived;
        cout << "Derived& operator=(const Derived &)" << endl;
        return *this;
    }

    void print() const{
        Base::print();
        cout << "Derived::_derived:" << _derived << endl;
    }

private:
    long _derived = 11;
};

/* =============== test =============== */
void test0() {
    cout << endl << "====== test0 ======" << endl;
    Derived d1(2, 5);
    Derived d2 = d1; /* 拷贝 */

    Derived d3(6, 7);
    d1 = d3; /* 赋值 */
    cout << endl << "====== start ======" << endl;
    d2.print();
    d1.print();
    cout << endl << "====== end ======" << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
