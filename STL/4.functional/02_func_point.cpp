/*************************************************************************
    > File Name: 04_func_point.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 14时09分41秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 回顾函数指针
    > Content:
 ************************************************************************/

#include <iostream>

int func() {
    std::cout << "int func()" << std::endl;
    return 10;
}

int func2() {
    std::cout << "int func2()" << std::endl;
    return 20;
}

int add(int x, int y) {
    std::cout << "int add(int, int)" << std::endl;
    return x + y;
}

/* =============== test =============== */
void test0() {
    func();

    typedef int(*pFunc)(); // C 函数指针
    using pFuncpp = int(*)(); // Cpp 函数指针
    
    /* 延迟调用函数 */
    pFunc f = &func; // 回调函数进行注册(注册回调函数)
    f(); // 回调函数的执行

    std::cout << std::endl;
    f = func2;
    f();
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
