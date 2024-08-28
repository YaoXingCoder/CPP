/*************************************************************************
    > File Name: 01_virtual_test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 09时24分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 虚函数测试
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class A{
public:
    virtual void a(){ cout << "A::a()" << endl; } 
    virtual void b(){ cout << "A::b()" << endl; } 
    virtual void c(){ cout << "A::c()" << endl; } 
};

class B{
public:
    virtual void a(){ cout << "B::a()" << endl; } 
    virtual void b(){ cout << "B::b()" << endl; } 
    void c(){ cout << "B::c()" << endl; } 
    void d(){ cout << "B::d()" << endl; } 
};

class C
: public A
, public B
{
public:
    virtual void a(){ cout << "C::a()" << endl; } 
    void c(){ cout << "C::c()" << endl; } 
    void d(){ cout << "C::d()" << endl; } 
};


//先不看D类
class D
: public C
{
public:
    void c(){ cout << "D::c()" << endl; }
};

/* =============== test =============== */
void test0() {
    C c;
    c.a(); 
    /* c.b(); */ 
    c.c(); 
    c.d(); 

    cout << endl;
    A* pa = &c;
    pa->a(); 
    pa->b(); 
    pa->c(); 
    /* pa->d(); */ 

    cout << endl;
    B* pb = &c;
    pb->a(); 
    pb->b(); /* 向上转型 B::b() */
    pb->c(); /* 向上转型 B::d() */
    pb->d(); /* 向上转型 B::d() */


    cout << endl;
    C * pc = &c;
    pc->a(); 
    /* pc->b(); */ 
    pc->c(); 
    pc->d(); 
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
