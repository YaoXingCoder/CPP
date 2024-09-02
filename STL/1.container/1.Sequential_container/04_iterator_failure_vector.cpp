/*************************************************************************
    > File Name: 04_iterator_failure_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 23时01分21秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 迭代器失效
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

template<typename Contianer>
void display(Contianer & con) {
    for (int i : con) { std::cout << i << " ";}
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    vector<int> number = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    display(number);
    cout << "number.size() = " << number.size() << endl; // 9
    cout << "number.capacity() = " << number.capacity() << endl; // 9

    cout << endl << "在容器尾部进行插入: " << endl;
    number.push_back(10);
    number.push_back(11);
    display(number);
    cout << "number.size() = " << number.size() << endl; // 11
    cout << "number.capacity() = " << number.capacity() << endl; // 18

    cout << endl << "在容器vector中间进行插入: " << endl;
    auto it = number.begin();
    it+=2;
    cout << "*it = " << *it << endl;
    number.insert(it, 22);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "numbers.size() = " << number.size() << endl;
    cout << "numbers.capacity() = " << number.capacity() << endl;

    /* 会发生扩容 */
    number.insert(it, 7, 100); // 因为插入个数不确定，有可能底层已经发生了扩容
    display(number);
    cout << "*it = " << *it << endl; // 扩容，迭代器仍指向就地址，失效
    cout << "numbers.size() = " << number.size() << endl;
    cout << "numbers.capacity() = " << number.capacity() << endl;

    // 正确办法是重置迭代器的位置
    /* vector<int> vec{51, 52, 53, 56, 57, 59}; */
    /* number.insert(it, vec.begin(), vec.end()); // 继续使用该迭代器就会出现问题（内存错误） */
    /* display(number); */
    /* cout << "*it = " << *it << endl; */

    // 解决方案：每次在插入元素的时候，可以将迭代器的位置进行重置更新，
    // 避免因为底层扩容，迭代器还指向老的空间而出现问题
    vector<int> vec{51, 52, 53, 56, 57, 59};
    it = number.begin(); // 重新置位
    it+=2;
    number.insert(it, vec.begin(), vec.end()); // 继续使用该迭代器就会出现问题（内存错误）
    display(number);
    cout << "*it = " << *it << endl;
    cout << "numbers.size() = " << number.size() << endl;
    cout << "numbers.capacity() = " << number.capacity() << endl;
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
