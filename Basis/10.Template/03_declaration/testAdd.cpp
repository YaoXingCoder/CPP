/*************************************************************************
    > File Name: testAdd.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 21时18分30秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include "add.h"
#include <iostream>
using std::cout;
using std::endl;

/* =============== test =============== */
void test0() {
    int i1 = 1, i2 = 2;
    cout << add(i1, i2) << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
