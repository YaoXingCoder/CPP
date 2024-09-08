/*************************************************************************
    > File Name: 03_inserter_iterator.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月07日 星期六 09时11分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 三组插入迭代器
    > Content:
    >   1.back_inserter;
    >   2.front_inserter;
    >   3.inserter
 ************************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>

template <typename Container>
void display(Container & con) {
    for ( int & i : con ) { std::cout << i << " "; }
    std::cout << std::endl;
}

/* =============== test =============== */
/* back_inserter */
void test0() {
    std::vector<int> vec = {1, 3, 7, 9};
    std::list<int> ls = {2, 6, 8, 4};

    // 将list中的元素插入到vector的尾部
    std::copy(ls.begin(), ls.end(), std::back_inserter<std::vector<int>>(vec));
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // 将 vector 中的元素插入到 list 的头部
    std::copy(vec.begin(), vec.end(), std::front_inserter<std::list<int>>(ls));
    std::copy(ls.begin(), ls.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::set<int> setNum = {1, 4, 6, 10, 20, 7};
    // 将 vector 中的元素插入到 set
    std::copy(vec.begin(), vec.end(), std::inserter<std::set<int>>(setNum, setNum.begin()));
    std::copy(setNum.begin(), setNum.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
