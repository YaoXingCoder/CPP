/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月06日 星期五 20时09分21秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "LURCache.hh"
#include <iostream>

template< typename Container>
void display(Container & con) {
    for ( std::pair<int, int> lp : con ) {
        std::cout << lp.first << " : " << lp.second << std::endl;
    }
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    LURCache lRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    std::cout << lRUCache.get(1) << std::endl; // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    std::cout << lRUCache.get(2) << std::endl; // 返回 1
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    std::cout << lRUCache.get(1) << std::endl; // 返回 -1 (未找到) */
    std::cout << lRUCache.get(3) << std::endl; // 返回 3
    std::cout << lRUCache.get(4) << std::endl; // 返回 4
    std::cout << std::endl << "-----------------" << std::endl;
    display(lRUCache.get_lp());
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
