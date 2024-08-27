/*************************************************************************
    > File Name: 01_multiDerived.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 15时52分48秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 多继承
    > Content:
    >   1.
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class A {
public:
    A(){ cout << "A()" << endl; }
    ~A(){ cout << "~A()" << endl; }
    void print() const{
        cout << "A::print()" << endl;
    }
};

class B {
public:
    B(){ cout << "B()" << endl; }
    ~B(){ cout << "~B()" << endl; }
    void show() const{
        cout << "B::show()" << endl;
    }
};

class C {
public:
    C(){cout << "C()" << endl; }
    ~C(){ cout << "~C()" << endl; }
    void display() const{
        cout << "C::display()" << endl;
    }
};

/* 多继承时
 * 1.每个基类都需要指明继承方式, 否则默认为私有 */
class D : public A, public B, public C {
public:
    D(){ cout << "D()" << endl; }
    ~D(){ cout << "~D()" << endl; }
    /* void print() const{ */
    /*     cout << "D::print()" << endl; */
    /* } */
};

/* =============== test =============== */
void test0() {
    cout << endl << "====== test0 ======" << endl;
    D d1;

    cout << endl << "====== start ======" << endl;
    d1.print();
    d1.show();
    d1.display();
    cout << endl << "====== end ======" << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
