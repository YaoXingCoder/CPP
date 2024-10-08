/*************************************************************************
    > File Name: test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月08日 星期二 14时02分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>

int * const func1() {
    int * const pi = new int(1);
    return pi;
}

/* =============== test =============== */
void test0() {
    int * x = func1();
    const int i = 1;
    int y = i;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
