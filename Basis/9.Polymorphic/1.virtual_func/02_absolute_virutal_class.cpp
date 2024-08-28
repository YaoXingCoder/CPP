/*************************************************************************
    > File Name: 02_absolute_virutal_class.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月27日 星期二 23时23分20秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 纯虚函数 , 抽象类
    > Content:
    >   1.
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
    virtual void print() = 0;
    virtual void display() = 0;
    void show() {
        cout << "A::show()" << endl;
    }
};

class B
: public A
{
public:
    B(int b = 10)
        :_b(b)
    {
        /* cout << "B" << endl; */
    }
public:
     virtual void print() override{
        cout << "B::print()" << endl;
    }

     void display() override{
         cout << "B::display()" << endl;
     }
private:
    int _b;
};

class C
: public B
{
public:
    virtual void display() override{
        cout << "C::display()" << endl;
    }
};

/* =============== test =============== */
void test0() {
    /* B b; */
    C c;
    B& b = c;
    A& a = c;
    B b1;
    b.print();
    b.display();
    a.display();
    b1.display();
    C c2;
    c2.display();
    c2.print();
    a.show();
    c.show();
    b.show();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
