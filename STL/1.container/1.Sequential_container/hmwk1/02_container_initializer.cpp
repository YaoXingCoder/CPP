/*************************************************************************
    > File Name: 02_container_initializer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 20时24分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 容器初始化
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <list>
using namespace std;

/* =============== test =============== */
void test0() {
    /* 1. 无参 */
    vector<int> v1;
    deque<int> d1;
    list<int> l1;

    /* 2.指定容量大小和初始化值 */
    vector<int> v2(10, 1);
    deque<int> d2(10, 2);
    list<int> l2(10, 3);

    /* 3.迭代器 */
    vector<int> v3(v2.begin(), v2.end());
    deque<int> d3(d2.begin(), d2.end());
    list<int> l3(l2.begin(), l2.end());

    /* 大括号（std::initializer_list 的 构造器） */
    vector<int> v4{ 1,2,3,4,5,6,7,8 };
    deque<int> d4{1,2,3,4,5,6,7,9};
    list<int> l4{1,2,3,4,5,56,67,7};

    /* 5.拷贝 和 移动 */
    vector<int> v5 = v4;
    deque<int> d5(d4);
    list<int> l5(std::move(l4));
    
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
