/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 19时56分14秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
/* #include "01_single_auto_release.hh" */
/* #include "02_single_auto_release_nested.hh" */
/* #include "03_single_auto_release_atexit.hh" */
#include "04_single_auto_release_pthread_once.hh"
#include <iostream>
using std::cout;
using std::endl;

/* =============== test =============== */
void test0() {
    /* AutoRelease auto1(Singleton::getInstance()); */
    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(3, 4);
    Singleton::getInstance()->print();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
