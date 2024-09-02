/*************************************************************************
    > File Name: 01_test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 20时17分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <list>

/* =============== test =============== */
void test0() {
    std::list<int> lst;
    std::list<int>::iterator iter1 = lst.begin(), iter2 = lst.end();
    std::cout << &iter1 << std::endl << &iter2 << std::endl;
    while(iter1 != iter2) {
        iter1++;
        std::cout << &iter1 << std::endl;
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
