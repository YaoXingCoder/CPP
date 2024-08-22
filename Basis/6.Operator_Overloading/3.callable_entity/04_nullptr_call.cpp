/*************************************************************************
    > File Name: 04_nullptr_call.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 20时11分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 空指针调用
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Bar{
public:
    void test0(){ cout << "Bar::test0()" << endl; }
    void test1(int x){ cout << "Bar::test1(): " << x << endl; }
    void test2(){ cout << "Bar::test2(): " << _data << endl; }

    int _data = 10;
};


/* 空指针可以调用成员函数
 * 但是如果函数中有访问成员变量则报错
 */
void test01(){
    Bar * fp = nullptr;
    fp->test0(); // ok
    fp->test1(3); // ok
    fp->test2();  // error
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
