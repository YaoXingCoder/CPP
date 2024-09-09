/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月10日 星期二 00时18分17秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 测试
    > Content:
 ************************************************************************/

#include "my_vector.hh"
#include <iostream>

/* =============== test =============== */
void test0() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    /* std::cout << vec[0] << std::endl; */
    /* std::cout << vec[1] << std::endl; */

    std::cout << "size:" << vec.size() << std::endl;
    std::cout << "capacity:" << vec.capacity() << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
