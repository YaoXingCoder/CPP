/*************************************************************************
    > File Name: 04_delete_virtual_class.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月27日 星期二 23时56分19秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 虚拟析构函数
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    Base()
    : _base(new int(10))
    { cout << "Base()" << endl; }

    virtual void display() const{
        cout << "*_base:" << *_base << endl;
    }

    ~Base(){
        if(_base){
            delete _base;
            _base = nullptr;
        }
        cout << "~Base()" << endl;
    }

private:
    int * _base;
};

class Derived
: public Base
{
public:
    Derived()
    : Base()
    , _derived(new int(20))
    {
        cout << "Derived()" << endl;
    }

    virtual void display() const override{
        cout << "*_derived:" << *_derived << endl;
    }

    ~Derived(){
        if(_derived){
            delete _derived;
            _derived = nullptr;
        }
        cout << "~Derived()" << endl;
    }

private:
    int * _derived;
};

void test(){
    //编译器会进行类型检查，pbase指向的空间是一个Derived对象
  	//所以会调用Derived的析构函数 —— 需要让析构函数设为虚函数，Derived析构函数会在虚表中覆盖Base析构函数的地址
    //这样通过pbase才能调用到Derived析构函数
    //Derived析构函数执行完，会自动调用Base的析构函数（没有走虚表这个途径） —— 析构函数本身的机制
}

/* =============== test =============== */
void test0() {
    /* Base * pbase = new Derived(); */
    /* pbase->display(); */

    /* delete (Derived*)pbase; */
    /* Derived* pd = (Derived*) pbase; */
    Derived* pd = new Derived();
    delete pd;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
