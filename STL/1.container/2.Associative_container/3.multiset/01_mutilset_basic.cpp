/*************************************************************************
    > File Name: 01_mutilset_basic.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 19时45分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title: multiset
    > Content:
 ************************************************************************/

#include <iostream>
#include <set>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::multiset;
using std::vector;
using std::pair;

template <typename Container>
void display(const Container &con) {
    for(auto &elem : con) {
        cout << elem << "  ";
    }
    cout << endl;
}

void test() {
    //multiset的基本特征
    //1、存放的是key类型，key值是不唯一的，可以重复
    //2、默认会按照key进行升序排列
    //3、底层使用的是红黑树
    multiset<int> number = {1, 3, 9, 8, 7, 4, 3, 2, 3, 3};
    /* multiset<int, std::greater<int>> number = {1, 3, 9, 8, 7, 4, 3, 2, 3, 3}; */
    display(number);

    /* 1. count 查询元素 */
    /* cout << endl << "multiset的查找操作" << endl; */
    /* size_t cnt = number.count(3); */
    /* cout << "cnt = " << cnt << endl; */
    /* cout << endl; */

    /* 2. find 查找元素 */
    auto it = number.find(7);
    if(it == number.end()) { cout << "元素是不存在multiset中" << endl; } 
    else { cout <<"元素是存在的 " << *it << endl; }

    cout << endl << "multiset 的 bound 系列函数" << endl;
    auto it2 = number.lower_bound(3);
    auto it3 = number.upper_bound(3);
    cout << "*it2 = " << *it2 << endl << "*it3 = " << *it3<< endl;

    while(it2 != it3) {
        cout << *it2 << "  ";
        ++it2;
    }
    cout << endl;
    
    pair<multiset<int>::iterator, multiset<int>::iterator> ret = number.equal_range(3);
    cout << "first = " << *ret.first << endl << "second = " << *ret.second << endl;
    while(ret.first != ret.second) {
        cout << *ret.first << "  ";
        ++ret.first;
    }
    cout << endl;

    cout << endl << "multiset的插入操作" << endl;
    multiset<int>::iterator it_insert =  number.insert(6);
    cout << *it_insert << endl;
    display(number);

    cout << endl;
    vector<int> vec = {1, 4, 8, 6, 4, 5};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl;
    number.insert({11, 99, 22, 1, 5, 3});
    display(number);

    cout << endl << "multiset的删除操作" << endl;
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.erase(it);
    display(number);

    size_t erase_num = number.erase(3);
    cout << erase_num << endl;
    display(number);
#if 0
    cout << endl << "multiset的下标操作" << endl;
    /* cout << "number[1] = " << number[1] << endl; */

    cout << endl << "multiset使用迭代器进行修改" << endl;
    it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    /* *it = 20;//error */
#endif
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}


