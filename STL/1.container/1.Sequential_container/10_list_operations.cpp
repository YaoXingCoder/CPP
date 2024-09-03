/*************************************************************************
    > File Name: 10_list_operations.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 15时29分00秒
    > Mail: JiaZiChunQiu@163.com
    > Title: list 特殊操作
    > Content:
 ************************************************************************/

#include <iostream>
#include <list>
#include <algorithm>
using std::cout;
using std::endl;
using std::list;

template<typename Contianer>
void display(Contianer & con) {
    for (int i : con) { std::cout << i << " ";}
    std::cout << std::endl;
}

/* =============== test =============== */
template <typename T1, typename T2>
struct Compare{
    bool operator()(const T1 & t1, const T2 & t2) {
        return t1 < t2;
    }
};

/* sort 排序 */
void test0() {
    list<int> ls{-1,2,-6,8,3,553,-122,0};
    /* ls.sort(std::less<int>()); */
    /* ls.sort(std::greater<int>()); */
    ls.sort(Compare<int, int>());
    display(ls);
}

/* 逆序, 去重, 合并 */
void test1() {
    list<int> number = {1, 3, 3, 3, 5, 7, 3, 9, 8,3,8,9};

    /* 1.逆置 */
    cout << endl << "list的逆置" << endl;
    /* number.reverse(); */
    display(number);

    /* 2.去重不完全，想要完全去重, 应该需要有序的列表 */
    cout << endl << "list的去重unique" << endl;
    /* number.unique(); */
    /* number.sort(Compare<int, int>()); */
    /* number.unique(); */
    display(number);

    /* 3.merge 合并操作 */
    cout <<endl << "list的merge操作" << endl;
    /* number.sort(std::greater<int>()); // 降序 */
    number.sort();
    display(number);

    list<int> other = {11, 2, 6, 4, 9};
    /* other.sort(std::greater<int>()); // 降序 */
    other.sort(); // 默认升序
    display(other);

    number.merge(other); // 默认升序
    /* number.merge(other, std::greater<int>()); */
    display(number);
    display(other); // 为空
}

/* 从一个链表转移元素到另一个链表 splice */
void test2() {
    list<int> number = {1, 3, 5, 7, 9, 11, 8};
    list<int> other = {333, 444, 999, 555, 222};
    display(number);
    display(other);

#if 0
    cout << endl;
    auto it_num = number.begin();
    ++it_num;
    cout << "*it = " << *it_num << endl;
    number.splice(it_num, other);
    display(number);
    display(other); /* 为空 */
    /* cout << other.size() << endl; // 0 */
#endif

#if 0
    cout << endl;
    auto it_num = number.begin();
    ++it_num;
    cout << "*it = " << *it_num << endl;
    auto it_ot = other.end();
    --it_ot;
    cout << "*oit = " << *it_ot << endl;
    number.splice(it_num, other, it_ot);
    display(number);
    display(other);
#endif

#if 0
    cout << endl << endl;
    auto it_num = number.begin();
    ++it_num;
    cout << "*it = " << *it_num << endl;
    auto oit2 = other.begin();
    auto oit3 = other.end();
    --oit3;
    cout << "*oit2 = " << *oit2 << endl;
    cout << "*oit3 = " << *oit3 << endl;
    number.splice(it_num, other, oit2, oit3);
    display(number);
    display(other);
#endif

#if 1
    // splice 能不能在同一个链表中进行操作呢？
    cout <<endl << endl;
    auto it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    auto it2 = number.end();
    --it2;
    --it2;
    cout << "*it2 = " << *it2 << endl;
    number.splice(it, number, it2);
    display(number);
#endif
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    /* test1(); */
    test2();
    return 0;
}
