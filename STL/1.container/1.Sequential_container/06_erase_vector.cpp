/*************************************************************************
    > File Name: 06_erase_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 23时48分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 删除元素
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::vector;

/* 多个元素相同时, 迭代器删除导致漏删 */
void test1() {
    std::vector<int> vec{1,2,2,2,2,3,4,5,6,7};
    for ( std::vector<int>::iterator it = vec.begin(); it != vec.end();) {
        if ( 2 == *it )  { it = vec.erase(it); }
        else { ++it; }
    }

    for ( int i : vec ) { std::cout << i << " "; }
    std::cout << std::endl;
}

void test2() {
    std::list<int> vec{1,2,2,2,2,3,4,5,6,7};
    for ( std::list<int>::iterator it = vec.begin(); it != vec.end();) {
        if ( 2 == *it )  { it = vec.erase(it); }
        else { ++it; }
    }

    for ( int i : vec ) { std::cout << i << " "; }
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test1();
    /* test2(); */
    return 0;
}
