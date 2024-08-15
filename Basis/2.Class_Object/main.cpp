/*************************************************************************
    > File Name: main.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月15日 星期四 14时35分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 测试
    > Content:
 ************************************************************************/

#include "01_Computer.hh"
#include "02_Point.hh"
#include <my_header.h>
#include <iostream>

void test01() {
    /* int x = 19; */
    /* int y(x); */
    /* cout << x << "," << y << endl; */

    std::cout << "start" << std::endl;

    /* Computer cp0; */
    /* cp0.setBrand("hello"); */
    /* cp0.setPirce(1234.123); */
    /* cp0.~Computer(); */ /* 不建议手动调用析构函数 */
    /* cp0.print(); */


    Computer cp1("Xiaomi", 12000.0);
    cp1.print();

    /* Computer cp2 = cp1; */
    Computer cp2(cp1);
    cp2.print();

    std::cout << "over" << std::endl;


}

/* 拷贝构造的第二个时机 */
void copyConstruct(Computer cp) {
    cp.print();
}

/* 拷贝构造的第三个时机 */
/* 加上引用后返回的生命周期大于函数的生命周期 */
/* Computer & copyConstruct2() { */
/* Computer cp("Apple", 20000.00); */
/*     return cp; */
/* } */
/* Computer cp00("Apple", 20000.00); */
/* Computer & copyConstruct2() { */
/*     return cp00; */
/* } */

void test02() {
    /* Computer cp("huawei", 9000.00); */
    /* copyConstruct(cp); */

    /* copyConstruct2().print(); */
}

/* ========================================================= */

void test03 () {
    Point pt1(10 ,20), pt2(11, 22);
    pt1 = pt2;
    pt1.operator=(pt2); /* 本质形式 */
    pt1.print();
}

int main (int argc, char* argv[]) {
    test03();
    return 0; 
}
