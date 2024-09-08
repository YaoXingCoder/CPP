/*************************************************************************
    > File Name: 01_ostream_iterator.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月06日 星期五 22时18分23秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 流迭代器
    > Content:
 ************************************************************************/
#include <iostream>
#include <iterator>
#include <vector>
/* #include <algorithm> */

using std::cout;
using std::endl;
using std::ostream_iterator;
using std::vector;
/* using std::copy; */


template<class InputIt, class OutputIt>
OutputIt copy1(InputIt first, InputIt last, OutputIt d_first){
	while (first != last) {
		d_first++ = *first++;
	}
	return d_first;
}

/* =============== test =============== */
void test0() {
    vector<int> vec = {1, 4, 8, 6, 2};
    ostream_iterator<int> osi(cout, " ");
    copy1(vec.begin(), vec.end(), osi);
    cout << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
