/*************************************************************************
    > File Name: 01_the_union_of_sets.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月04日 星期三 21时20分12秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 计算集合的并集
    > Content:
    >   1.给你两个集合，计算其并集，即 {A} + {B}。
    >   2.不允许出现重复元素，但是 {A} 与 {B}之间可能存在相同元素。
    >   输入格式
    >   输入数据分为三行，第一行有两个数字n,m(0 < n,m<=10000) ，分别表示集合A和集合B的元素个数。
    >   后两行分别表示集合 A 和集合 B。
    >   每个元素为不超出int范围的整数，每个元素之间用一个空格隔开。
    >   输出格式
    >   输出一行数据，表示合并后的集合，要求从小到大输出，每个元素之间用一个空格隔开。
    >   样例输入1
    >   1 2
    >   1
    >   2 3
    >   样例输出1
    >   1 2 3
 ************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <list>

template<typename Container>
void display(Container & con) {
    for ( int i : con ) { std::cout << i << " "; }
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    /* 三个容器 */
    std::list<int> ls_A;
    std::list<int> ls_B;
    std::list<int> ls_union;

    /* 读取输入的一行信息 */
    int a = 0;
    int b = 0;
    int num = -1;
    scanf("%d %d", &a, &b);

    /* 读 ls_A 的数据 */
    while(scanf("%d", &num)) {
        ls_A.push_back(num);
        if ( --a == 0 ) { break; }
    }

    while(scanf("%d", &num)) {
        ls_B.push_back(num);
        if ( --b == 0 ) { break; }
    }

    /* 合并 A B */
    ls_A.merge(ls_B);
    /* 排序, 去重 */
    ls_A.sort(std::less<int>());
    ls_A.unique();
    display(ls_A);
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
