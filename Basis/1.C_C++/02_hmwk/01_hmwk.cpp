/*************************************************************************
    > File Name: 01_hmwk.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月13日 星期二 21时55分24秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

namespace MySpace {
    extern void add(int x = 10 , int y = 20);
} 

int main (int argc, char* argv[]) {
    int x = 10, y = 10;
    MySpace::add(x, y);
    MySpace::add();
    return 0;
}
