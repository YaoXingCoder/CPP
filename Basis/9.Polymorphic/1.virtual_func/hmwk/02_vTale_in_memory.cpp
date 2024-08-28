/*************************************************************************
    > File Name: 02_vTale_in_memory.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 09时45分25秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 验证虚表在内存中的区域
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class A {
public:
    virtual void print() {
        cout << "A::a()" << endl;
    }
};

class B : public A {
public:
    void print() override {
        cout << "B()" << endl;
    }
}; /* sizeof(B) = 16 */

int x = 10;
const char* pstr2 = "world";

/* =============== test =============== */
void test0() {
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    int y = 10;
    int* z = new int();
    const char* pstr = "hello";
    B b;

    printf("%p\n", &y); /* 栈区 */
    printf("%p\n", z); /* 堆区 */
    printf("%p\n", &x); /* 静态区 */

    long* pB = (long*)(&b);
    long* pBV = (long*)(*pB);

    cout << endl << endl;
    printf("%p\n", pBV); /* 文字常量区 */
    printf("%p\n", pstr2);
    printf("%p\n", pstr);

    cout << endl << endl;
    printf("%p\n", test0); /* 代码区 */
    printf("%p\n", main); /* 代码区 */
    delete z;
    return 0;
}
