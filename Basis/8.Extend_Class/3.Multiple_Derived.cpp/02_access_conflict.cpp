/*************************************************************************
    > File Name: 02_access_conflict.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 16时16分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 菱形继承, 访问冲突
    > Content:
    >   1.虚拟继承
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class A {
public:
    void print() const{
        cout << "A::print()" << _a << endl;
    }
    double _a;
};

class B: virtual  public A {
public:
    double _b;
};

class C : virtual public A {
public:
    double _c;
};

class D
: public B
, public C
{
public:
    /* void print() const { */
    /*     cout << "D" << endl; */
    /* } */
public:
    double _d;
};

/* =============== test =============== */
void test0() {
    cout << endl << "====== test0 ======" << endl;
    D d1;
    cout << endl << "====== start ======" << endl;
    cout << sizeof(A) << endl; /* 8 */
    cout << sizeof(B) << endl; /* 16 */
    cout << sizeof(C) << endl; /* 16 */
    cout << sizeof(D) << endl; /* 40 */
    /* d1.print(); /1* 二义性, 两条路径， D -> B -> A , D -> C -> A *1/ */
    /* d1.B::print(); /1* 指明路径 *1/ */
    /* d1.C::print(); */
    /* d1.print(); */

    /* 解决
     * 1.D 中声明, 隐藏基类
     * 2.虚拟继承基类 */
    
    cout << endl << "====== end ======" << endl;
}

/* 虚拟继承测试 */
void test1() {
    cout << endl << "====== test0 ======" << endl;
    D d1;
    cout << endl << "====== start ======" << endl;
    cout << sizeof(A) << endl; /* 8 */
    cout << sizeof(B) << endl; /* 24 */
    cout << sizeof(C) << endl; /* 24 */
    cout << sizeof(D) << endl; /* 48 */
    /* 解决
     * 1.D 中声明, 隐藏基类
     * 2.虚拟继承基类 */

    d1.print();
    
    cout << endl << "====== end ======" << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
