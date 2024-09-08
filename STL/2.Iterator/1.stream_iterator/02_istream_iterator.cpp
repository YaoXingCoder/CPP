/*************************************************************************
    > File Name: 02_istream_iterator.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月06日 星期五 23时16分24秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 输入流迭代器
    > Content:
 ************************************************************************/

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::istream_iterator;
using std::ostream_iterator;
using std::vector;
using std::copy;

/* =============== test =============== */
void test0() {
    vector<int> vec;
    /* vec.reserve(10); */
    istream_iterator<int> isi(cin);
    /* copy(isi, istream_iterator<int>(), vec.begin()); */
    copy(isi, istream_iterator<int>(), std::back_inserter(vec));
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
