/*************************************************************************
    > File Name: 04_reverse_iterator.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月07日 星期六 09时53分56秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 反向（逆向）迭代器
    > Content:
 ************************************************************************/

#include <iostream>
#include <iterator>
#include <vector>

/* =============== test =============== */
void test0() {
    std::vector<int> vec = {1, 3, 5, 7, 9, 11, 13};
    std::vector<int>::reverse_iterator rit = vec.rbegin();
    for ( ; rit != vec.rend(); ++rit ) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
