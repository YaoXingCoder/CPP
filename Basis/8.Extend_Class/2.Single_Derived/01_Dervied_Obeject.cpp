/*************************************************************************
    > File Name: 01_Dervied_Obeject.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月25日 星期日 22时02分33秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单继承派生类对象的创建与销毁
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Test{
public:
    Test(long test) : _test(test)
    { cout << "Test() 无参" << endl; }
    
    ~Test(){ cout << "~Test() 析构" << endl; }
private:
    long _test;
};

class Base {
public:
	Base(){ cout << "Base() 无参" << endl; }
    Base(long base) : _base(base) { cout << "Base(long) 有参" << endl; }

    ~Base() { cout << "~Base() 析构" << endl; }
private:
	long _base;
};

class Derived : public Base  {
public:
    /* 如果基类没有无参构造, 也没有显示调用基类有参, 则报错 */
	Derived(long derived) : _derived(derived), _t1(derived), _b1(derived)
	{ cout << "Derived(long) 有参" << endl; }

    ~Derived() { cout << "~Derived() 析构" << endl; }
private:
	long _derived;
    Test _t1;
    Base _b1;
};


/* =============== test =============== */
void test0() {
    Derived(1);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
