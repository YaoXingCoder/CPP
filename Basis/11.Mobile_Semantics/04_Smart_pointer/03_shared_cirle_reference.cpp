/*************************************************************************
    > File Name: 03_shared_cirle_reference.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月31日 星期六 00时08分47秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 循环引用问题
    > Content:
 ************************************************************************/
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

class Child;

class Parent {
public:
	Parent() { cout << "Parent()" << endl; }
	~Parent(){ cout << "~Parent()" << endl; }
	//只需要Child类型的指针，不需要类的完整定义
	shared_ptr<Child> _spChild;
	weak_ptr<Child> _wpChild;
};

class Child {
public:
	Child() { cout << "child()" << endl; }
	~Child() { cout << "~child()" << endl; }
	shared_ptr<Parent> _spParent;
    weak_ptr<Parent> _wpParent;
};

void test0(){
    shared_ptr<Parent> parentPtr(new Parent());
    shared_ptr<Child> childPtr(new Child());
    cout << parentPtr.use_count() << endl;
    cout << childPtr.use_count() << endl;

    cout << endl;
    parentPtr->_spChild = childPtr;
    /* parentPtr->_wpChild = childPtr; */
    /* childPtr->_spParent = parentPtr; */
    childPtr->_wpParent = parentPtr;
    cout << parentPtr.use_count() << endl;
    cout << childPtr.use_count() << endl;
}

int main(void){
    test0();
    return 0;
}
