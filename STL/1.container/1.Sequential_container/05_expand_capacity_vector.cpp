/*************************************************************************
    > File Name: 05_expand_capacity_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 23时27分30秒
    > Mail: JiaZiChunQiu@163.com
    > Title: vector 的扩容机制探究
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

template<typename Contianer>
void display(Contianer & con) {
    for (int i : con) { std::cout << i << " ";}
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    vector<int> number = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    number.reserve(15);
    cout << "number.size() = " << number.size() << endl; // m = 9
    cout << "number.capacity() = " << number.capacity() << endl; // n = 15

    /* 1. t < n - m = 6; */
    cout << endl << "------------ 2 ----------" << endl;
    vector<int>::iterator it_vc = number.begin();
    it_vc+=5;
    number.insert(it_vc, {11,12,13,14,15});
    cout << "number.size() = " << number.size() << endl; // 14
    cout << "number.capacity() = " << number.capacity() << endl; // 15

    /* 2. n - m = 6 < t < 9;  2 * m = 18 */
    /* cout << endl << "------------ 2 ----------" << endl; */
    /* vector<int>::iterator it_vc = number.begin(); */
    /* it_vc+=5; */
    /* number.insert(it_vc, {11,12,13,14,15,16,17}); */
    /* cout << "number.size() = " << number.size() << endl; // 16 */
    /* cout << "number.capacity() = " << number.capacity() << endl; // 18 */

    /* 3. n - m = 6 < t < 15, t > 9;  n * m = 24 */
    /* cout << endl << "------------ 3 ----------" << endl; */
    /* vector<int>::iterator it_vc = number.begin(); */
    /* it_vc+=5; */
    /* number.insert(it_vc, {11,12,13,14,15,16,17,18,19,20}); */
    /* cout << "number.size() = " << number.size() << endl; // 19 */
    /* cout << "number.capacity() = " << number.capacity() << endl; // 19 */
                                                                 //
    /* 4. t > 15;  n * m = 24 */
    /* cout << endl << "------------ 4 ----------" << endl; */
    /* vector<int>::iterator it_vc = number.begin(); */
    /* it_vc+=5; */
    /* number.insert(it_vc, {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26}); */
    /* cout << "number.size() = " << number.size() << endl; // 25 */
    /* cout << "number.capacity() = " << number.capacity() << endl; // 25 */
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
