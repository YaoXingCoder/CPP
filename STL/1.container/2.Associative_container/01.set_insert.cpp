/*************************************************************************
    > File Name: 01.set_insert.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 22时01分30秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 关联式容器 set 的插入
    > Content:
 ************************************************************************/

#include <iostream>
#include <set>
#include <utility>
using std::cout;
using std::endl;
using std::set;
using std::pair;

template <typename Container>
void display(const Container &con){
    for(auto &elem : con) { cout << elem << " "; }
    cout << endl;
}

/* =============== test =============== */
/* insert 返回值 */
void test0() {
    std::set<int> number {1, 3, 9, 8, 7, 4, 3, 2, 3, 3};
    cout << endl << "set的插入操作" << endl;
    pair<set<int>::iterator, bool> ret = number.insert(6);
    if(ret.second) { cout << "插入成功 " << *ret.first << endl; }
    else { cout << "插入失败, 该元素存在set中" << endl; }
    display(number);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
