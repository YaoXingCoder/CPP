/*************************************************************************
    > File Name: 03_copy_list_to_deque.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 20时15分32秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 从一个 list 拷贝元素到两个 deque 中。值为偶数的所有元素都拷贝到一个 deque 中，而奇数值元素都拷贝到另一个 deque 中。
    > Content:
    >   1.熟悉list容器与deque容器的基本操作，包括初始化、遍历、插入等等
 ************************************************************************/

#include <iostream>
#include <deque>
#include <list>

template <typename Container>
void display (Container & con) {
    for ( int & i : con ) { std::cout << i << " "; }
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    std::list<int> ls{1,2,3,4,5,6,7,8,9,10};
    
    std::deque<int> dq_odd;
    std::deque<int> dq_even;

    /* 遍历 */
    std::list<int>::iterator it_ls = ls.begin();
    while( it_ls != ls.end() ) {
        if ( *it_ls % 2 == 1 ) { dq_odd.emplace_back(*it_ls);  } 
        else if ( *it_ls % 2 == 0 ) { dq_even.emplace_back(*it_ls); }
        ++it_ls;
    }

    /* 打印 */
    display(ls);
    display(dq_odd);
    display(dq_even);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
