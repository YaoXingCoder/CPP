/*************************************************************************
    > File Name: 08_variable_parameter.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 23时22分30秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 可变参数
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

template <class ...Args> // Args 模板参数包
void display(Args ... args) // args 函数参数包
{
    // 输出模板参数包中类型参数个数
    cout << "sizeof...(Args) = " << sizeof...(Args) << endl;
    (cout << ... << args) << endl;
    // 输出函数参数包中参数的个数
    cout << "sizeof...(args) = " << sizeof...(args) << endl;
}

/* 递归出口 */
void print() {
    cout << endl;
}

/* void print(double x) { */
/*     cout << x << endl; */
/* } */

template<class T>
void print(T t) {
    /* cout << "template" << endl; */
    cout << t << endl;
}

/* 循环输出 */
template <class T1, class T2, class ...Args>
void print(T1 t1, T2 t2, Args ... args) {
    cout << t1 <<  " " << t2 << " ";
    print(args...);
}

/* =============== test =============== */
void test0() {
    display(1, 2, 3, 4, "hello");
    /* print(1, 2, 3, 4, "hello"); */
    print(1, 2, 3, 4, 5, 6, 7, 8, 9, "hello", "1");
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
