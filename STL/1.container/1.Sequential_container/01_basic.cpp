/*************************************************************************
    > File Name: 01_basic.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 15时34分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 序列式基础使用
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <list>
using namespace std;

/* 遍历 */
template <typename Container>
void display(Container & con) {
    for (auto i : con) { cout << i << " "; }
    cout << endl;
}

/* =============== test =============== */
void test0() {
    /* 1.初始化为空 */
    vector<int> v1;
    deque<int> d1;
    list<int> l1;

    /* 2.初始化指定大小 */
    vector<int> v2_0(10);
    deque<int> d2_0(10);
    list<int> l2_0(10);
    display(v2_0);
    display(d2_0);
    display(l2_0);
    vector<int> v2_1(10, 1);
    deque<int> d2_1(10, 1);
    list<int> l2_1(10, 1);
    display(v2_1);
    display(d2_1);
    display(l2_1);

    /* 3.迭代器 */
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v3(arr, arr + sizeof(arr)/sizeof(arr[0]));
    deque<int> d3(arr, arr + sizeof(arr)/sizeof(arr[0]));
    list<int> l3(arr, arr + sizeof(arr)/sizeof(arr[0]));
    display(v3);
    display(d3);
    display(l3);

    /* 4.大括号, 调用 std::initializer_list 构造 */
    /* 4.0, 4_1等效 */
    vector<int> v4_0{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v4_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    deque<int> d4_0{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list<int> l4_0{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    display(v4_0);
    display(d4_0);
    display(l4_0);

    /* 5.拷贝 | 移动构造 */
    vector<int> v5_0 = { 1, 2, 3, 4 };
    vector<int> v5_1(v5_0); /* 拷贝 */
    vector<int> v5_2(std::move(v5_0)); /* 移动 */
    display(v5_1);
    display(v5_2);
    deque<int> d5_0 = { 1, 2, 3, 4 };
    deque<int> d5_1(d5_0); /* 拷贝 */
    deque<int> d5_2(std::move(d5_0));
    display(d5_1);
    display(d5_2);
    list<int> l5_0 = { 1, 2, 3, 4 };
    list<int> l5_1(l5_0); /* 拷贝 */
    list<int> l5_2(std::move(l5_0)); /* 移动 */
    display(l5_1);
    display(l5_2);
}

/* 1.下标访问 */ 
template<typename Container>
void traverse1(Container & con) {
    for(size_t idx = 0; idx != con.size(); ++idx) { cout << con[idx] << " ";}
    cout << endl;
}

/* 2.迭代器 */
template<>
void traverse1(vector<int> & con) {
    cout << "vector<int>" << endl;
    vector<int>::iterator it = con.begin();
    while(it != con.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}
template<>
void traverse1(deque<int> & con) {
    cout << "deque<int>" << endl;
    deque<int>::iterator it = con.begin();
    while(it != con.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}
template<>
void traverse1(list<int> & con) {
    cout << "list<int>" << endl;
    list<int>::iterator it = con.begin();
    while(it != con.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

/* 3.增强for循环 */
template<typename Type, typename Container>
void traverse_for(Container & con) {
    for( Type i : con  ) { cout << i << " "; }
    cout << endl;
}

/* 遍历 */
void test2() {
    vector<int> v1{1, 12, 3, 23, 5, 6, 33, 8, 9, 11};
    deque<int> d1{1, 2, -3, 4, 5, -6, 7, 8, 9, 10};
    list<int> l1{1, 22, 3, -4, -5, 6, 17, 8, 9, -10};    

    traverse1(v1);
    traverse1(d1);
    traverse1(l1);

    traverse_for<int>(v1);
    traverse_for<int>(d1);
    traverse_for<int>(l1);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test2();
    return 0;
}
