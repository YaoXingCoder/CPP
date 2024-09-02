/*************************************************************************
    > File Name: 02_variable_parameter_add.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 00时06分33秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 利用可变模板参数实现一个函数模板，用来计算多个整型、浮点型数据的加法
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

template<class T>
T add(T t) {
    return 0;
}

template<class T, class ...Args>
T add(T t, Args ... args) {
   return t + add(args...);
}

/* =============== test =============== */
void test0() {
    cout << add( 1, 2, 2, 3, 4, 5, 5, 6, 6, 123.0, 123.0 ) << endl;
    cout << add( 1, 2 ) << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
