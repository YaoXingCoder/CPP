/*************************************************************************
    > File Name: hmwk_02.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 20时26分04秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main (int argc, char* argv[]) {

    int x;
    cin >> x;
    if ( x++ > 5 ) { cout << x << endl; }
    else { cout << x-- << endl; }
    return 0;
}
