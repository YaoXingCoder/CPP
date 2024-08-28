/*************************************************************************
    > File Name: 05_verify_virtual_table.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 00时05分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 验证虚拟表的存在, 以及内存构造
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
	virtual void print() {
  		cout << "Base::print()" << endl;
		}
	virtual void display() {
  		cout << "Base::display()" << endl;
	}
	virtual void show() {
  		cout << "Base::show()" << endl;
	}
private:
	long _base = 10;
};

class Derived
: public Base
{
public:
    	virtual void print() {
  		cout << "Derived::print()" << endl;
	}
	virtual void display() {
  		cout << "Derived::display()" << endl;
	}
	virtual void show() {
  		cout << "Derived::show()" << endl;
	}
private:
	long _derived = 100;
};

/* =============== test =============== */

void test0(){
	Derived d;
	long * pDerived = reinterpret_cast<long*>(&d);
	cout << pDerived[0] << endl;
	cout << pDerived[1] << endl;
	cout << pDerived[2] << endl;

    /* cout << endl << endl; */
    /* cout << (*(long*)(pDerived[0])) << endl; */
    /* cout << (*((long*)(pDerived[0])+1)) << endl; */

	cout << endl;
	long * pVtable = reinterpret_cast<long*>(pDerived[0]);
	cout << pVtable[0] << endl;
	cout << pVtable[1] << endl;
	cout << pVtable[2] << endl;

	cout << endl;
	typedef void (*Function)();

    /* Function (*(long*)pDerived[0])(); */

	Function f = (Function)(pVtable[0]);
	f();
	f = (Function)(pVtable[1]);
	f();
	f = (Function)(pVtable[2]);
    f();
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
