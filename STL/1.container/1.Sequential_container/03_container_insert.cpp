/*************************************************************************
    > File Name: 03_container_insert.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 22时44分48秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 插入元素, 随即插
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <list>
using std::vector;
using std::deque;
using std::list;
using std::cout;
using std::endl;

template<typename Contianer>
void display(Contianer & con) {
    for (int i : con) { std::cout << i << " ";}
    std::cout << std::endl;
}

/* =============== test =============== */
/* list */
void test0() {
    std::list<int> l1 {1, 4, 6, 8, 9};
    std::list<int>::iterator it_l1 = l1.begin();
    ++it_l1;

    /* 1.插入一个元素 */
    l1.insert(it_l1, 22);
    display(l1);
    std::cout << *it_l1 << std::endl;

    /* 2.插入数个相同元素 */
    l1.insert(it_l1, 3, 100);
    display(l1);
    std::cout << *it_l1 << std::endl;

    /* 3.插入迭代器范围元素 */
    std::vector<int> vec_int{ 51,52,53,54,55,56,57,58,59 };
    l1.insert(it_l1, vec_int.begin(), vec_int.end());
    display(l1);
    std::cout << *it_l1 << std::endl;

    /* 4.插入大括号范围元素 */
    l1.insert(it_l1, {1, 2, 3});
    display(l1);
    std::cout << *it_l1 << std::endl;
}

/* deque */
void test1() {
    deque<int> number = {1, 4, 6, 8, 9, 10, 5, 7};
    display(number);

    cout << endl << "在deque的尾部进行插入与删除" << endl;
    number.push_back(22);
    number.push_back(33);
    display(number);
    number.pop_back();
    display(number);

    cout << endl << "在deque的头部进行插入与删除" << endl;
    number.push_front(100);
    number.push_front(200);
    display(number);
    number.pop_front();
    display(number);

    cout << endl << "在deque的任意位置进行插入" << endl;
    auto it = number.begin();
    it += 2;
    cout << "*it = " << *it <<endl;
    number.insert(it, 111);
    display(number);
    cout << "*it = " << *it <<endl;

    cout << endl << endl;
    number.insert(it, 3, 200);
    display(number);
    cout << "*it = " << *it <<endl;

    cout << endl << endl;
    vector<int> vec = {333, 555, 444};
    number.insert(it, vec.begin(), vec.end());
    display(number);
    cout << "*it = " << *it <<endl;

    cout << endl << endl;
    number.insert(it, {123, 789, 456});
    display(number);
    cout << "*it = " << *it <<endl;
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
