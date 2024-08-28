/*************************************************************************
    > File Name: 03_abstract_protected_class.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月27日 星期二 23时37分32秒
    > Mail: JiaZiChunQiu@163.com
    > Title: protected 抽象类
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Base {
protected:
	Base(int base)
    : _base(base) 
    { 
        cout << "Base()" << endl; 
    }

    void print() {
        cout << "Base _base " << _base << endl;
    }

	int _base;
};
class Derived
: public Base 
{
public:
	Derived(int base, int derived)
	: Base(base)
	, _derived(derived)
	{ cout << "Derived(int,int)" << endl; }
    
	void print() const
	{
        Base::print();
		cout << "_base:" << _base
		<< ", _derived:" << _derived << endl;
	}
private:
	int _derived;
};
/* =============== test =============== */
void test0() {
    Derived derived(1, 2);
    
    derived.print();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
