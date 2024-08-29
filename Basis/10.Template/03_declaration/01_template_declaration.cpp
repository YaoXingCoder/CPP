/*************************************************************************
    > File Name: 02_template_declaration.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 11时35分31秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 模板声明与定义
    > Content:
 ************************************************************************/

#include <iostream>

template<class T>
T add(T t1, T t2);

/* 模板函数定义在调用之后, 可以在前边声明 */
void test1() {
    std::cout << add(1, 2) << std::endl;
}

template<class T>
T add(T t1, T t2) {
    return t1 + t2;
}

/* =============== test =============== */
void test0() {
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test1();
    return 0;
}
