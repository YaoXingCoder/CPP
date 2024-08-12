/*************************************************************************
    > File Name: hmwk_01.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 20时22分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

int foo(int x, int y) {
    if ( x <= 0 || y <= 0 ) { return 1; }
    return 3 * foo(x - 1, y / 2);
}

int main (int argc, char* argv[]) {
    cout << foo(3, 5) << endl;
    return 0;
}
