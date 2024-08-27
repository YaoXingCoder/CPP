/*************************************************************************
    > File Name: 03_base_transfer_derived.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 16时41分20秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 基类 -> 派生类 or 派生类 -> 基类
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;


class Base{
public:
    Base(long base) : _base(base)
    { cout << "Test()" << endl; }

    ~Base(){ cout << "~Test()" << endl; }

    void print() const {
        cout << _base << endl;
    }

    virtual void display() {
        cout << "Base::display" << endl;
    }
private:
    long _base;
};

class Derived : public Base {
public:
    Derived(long base, long derived)
    : Base(base) // 创建基类子对象
    , _derived(derived)
    { cout << "Derived()" << endl; }

    ~Derived(){ cout << "~Derived()" << endl; }

    void print() const {
        cout << _derived << endl;
    }
private:
    long _derived;
};

/* =============== test =============== */
/* 向上转型 */
void test0() {
    cout << endl << "====== test0 ======" << endl;
    Base b1(1);
    Derived d1 (2, 3);

    /* derived -> b1 ok 向上转换 */ 
    b1 = d1; 
    Base* pb1 = &d1;
    Base& b_ref1 = d1;

    cout << endl << "====== start ======" << endl;
    b1.print();
    pb1->print();
    b_ref1.print();

    cout << endl << "====== end ======" << endl;
}

/* 向下转型 */
void test1() {
    cout << endl << "====== test0 ======" << endl;
    Base b1(1);
    Derived d1 (2, 3);

    /* d1 = b1; /1* error *1/ */
    /* 合理的向下转换 */
    /* Base* pb1 = &d1; /1* 基类初始化时, 指向派生类, 但该指针只能访问基类的大小 *1/ */
    /* Derived* pd1 = (Derived*)pb1; */

    /* 不合理转化 C语言的强制转换*/
    /* Base* pb2 = &b1; */
    /* Derived* pd2 = (Derived*) pb2; */

    /* 不合理转换 C++语言 */
    /* Base* pb3 = &b1; */
    Base* pb3 = &d1;
    Derived* pd3 = dynamic_cast<Derived*>(pb3);

    cout << endl << "====== START ======" << endl;
    /* pd1->print(); */
    /* pd2->print(); */
    /* pd3->print(); */
    if ( pd3 ) {
        cout << "sucess" << endl;
        pd3->display();
    } else {
        cout << "failed" << endl;
    }
    cout << endl << "====== END ======" << endl;
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
