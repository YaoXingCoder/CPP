/* #include "add.h" */
#include <iostream>

template <class T>
T add(T t1, T t2) {
    return t1 + t2;
}

/* 调用后才能生成相应函数, 还必须与main函数中调用的一致 */
/* void test1() { */
/*     std::cout << add(1, 2) << std::endl; */
/* } */
