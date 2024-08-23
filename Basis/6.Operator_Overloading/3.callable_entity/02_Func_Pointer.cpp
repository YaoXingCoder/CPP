/*************************************************************************
    > File Name: 02_Func_Pointer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 17时24分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 函数指针
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

typedef void(*FuncPtr)(int);
using FuncPtr2 = void(*)(int);

void print(int x) { 
    cout << "print: " << x << endl;
}

void display( int x ) {
    cout << "display: " << x << endl;
}

void show() {
    cout << "show" << endl;
}

void test01() {
    /* 定义函数指针 要确定其 指向的函数的
     * 返回类型 和 参数信息 
     * */
    void (*p1)(int) = print;
    p1(3);
    p1 = display;
    p1(4);
    
    /* 规范完整的形式 */
    void(*p)(int) = &print;
    (*p)(3);
    p = &display;
    (*p)(4);

    FuncPtr p2 = print;
    p2(5);

    FuncPtr2 p3 = display;
    p3(6);

    /* p1 = show; /1* 报错 因为:show的类型与p1声明不同 */
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
