/*************************************************************************
    > File Name: 01_virtual_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月27日 星期二 14时28分26秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 虚函数各种访问情况
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Grandpa
{
public:
    Grandpa(){ cout << "Grandpa()" << endl; }
    ~Grandpa(){ cout << "~Grandpa()" << endl; }

    virtual void func1() {
        cout << "Grandpa::func1()" << endl;
    }

    virtual void func2(){
        cout << "Grandpa::func2()" << endl;
    }
};

class Parent
: public Grandpa
{
public:
    Parent(){
        cout << "Parent()" << endl;
        func1();//构造函数中调用虚函数
    }

    ~Parent(){
        cout << "~Parent()" << endl;
        func2();//析构函数中调用虚函数
    }

    virtual void func1() override {
        cout << "Parent::func1()" << endl;
    }

    virtual void func2() override{
        cout << "Parent::func2()" << endl;
    }
};

class Son
: public Parent
{
public:
    Son() { cout << "Son()" << endl; }
    ~Son() { cout << "~Son()" << endl; }

    virtual void func1() override {
        cout << "Son::func1()" << endl;
    }

    virtual void func2() override{
        cout << "Son::func2()" << endl;
    }
};

/* =============== test =============== */
void test0() {
    Parent p1;
    Grandpa* gp1 = &p1;
    /* gp1->func1(); */
    /* gp1->func2(); */
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
