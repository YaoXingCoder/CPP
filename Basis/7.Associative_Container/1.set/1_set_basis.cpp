/*************************************************************************
    > File Name: 1_set_basis.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月24日 星期六 10时23分20秒
    > Mail: JiaZiChunQiu@163.com
    > Title: set 容器
    > Content:
    >   1.自带排序
    >   2.元素可重复
 ************************************************************************/

#include <iostream>
#include <set>
#include <utility>
#include <string>
using std::cout;
using std::endl;
using std::set;
using std::pair;
using std::string;


/* =============== test =============== */
void test0() {
    set<int> set_i1;
    set<int> set_i2{1, 2, 3};
    set<int> set_i3 = {1, 2, 3};

    set<int> set_i4 = set_i3;
    set<int> set_i5(set_i3.begin(), set_i3.end());

    set<int> set_i6{1, 3, 2, 100, 22, 32, -1, 21, -1};
    set_i6.insert(1000);
    
    cout << endl << "====== start ======" << endl;
    for(int i : set_i6){
        cout << i << " ";
    }
    cout << endl << "====== end ======" << endl;;
}

void test1(){
    cout << endl << "====== start ======" << endl;
    set<int> set_i1{1, 3, 2, 100, 22, 32, -1, 21, -1};
    cout << "set.size : " << set_i1.size() << endl;
    cout << "set.max_size : " << set_i1.max_size() << endl;

    /* set_i1.clear(); */
    cout << "set.size : " << set_i1.size() << endl;
    cout << "set.max_size : " << set_i1.max_size() << endl;

    cout << "set.cout : " << set_i1.count(1) << endl;
    cout << "set.cout : " << set_i1.count(-3) << endl;
    cout << "*set.find() : "  << *set_i1.find(1) << endl;
    cout << endl << "====== end ======" << endl;
}

/* pair 使用 */
void test2() {
    cout << endl << "====== test2  ======" << endl;
    /* pair<int, string> pa(1, "hello"); */
    set<int> set_i1{1, 3, 2, 100, 22, 32, -1, 21, -1};
    pair<set<int>::iterator, bool> set_pair;

    cout << endl << "====== start ======" << endl;
    /* cout << "pa.key : " <<  pa.first << ", pa.value : " << pa.second << endl; */

    set_pair = set_i1.insert(50);
    cout << *set_pair.first << ", " << set_pair.second << endl;
    set_pair = set_i1.insert(50);
    cout << *set_pair.first << ", " << set_pair.second << endl;
    /* set_pair = set_i1.insert(230584300921369396); */
    /* cout << *set_pair.first << ", " << set_pair.second << endl; */
    cout << endl << "====== end ======" << endl;
}
/* 插入多个元素 */
void test3() {
    cout << endl << "====== test3  ======" << endl;
    pair<set<int>::iterator, bool> set_pair;
    set<int> set_i1{1, 3, 2, 100, 22, 32, -1, 21};

    int arr[5] = { 18, 41, 35, 2, 9 };
    set_i1.insert(arr, arr + 5);
    cout << endl << "====== start ======" << endl;
    cout << set_i1.size() << endl;
    set<int>::iterator set_it = set_i1.begin();
    while(set_it != set_i1.end()) {
        cout << *set_it << " ";
        ++set_it;
    }
    cout << endl << "====== end ======" << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    /* test1(); */
    test2();
    /* test3(); */
    return 0;
}
