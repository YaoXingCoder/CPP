/*************************************************************************
    > File Name: 04_test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月25日 星期日 15时50分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include "04_Line.hh"
#include <iostream>
using std::cout;
using std::endl;

/* =============== test =============== */
void test0() {
    Line(1, 2, 3, 4).printLine();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
