/*************************************************************************
    > File Name: A.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月13日 星期二 22时11分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

namespace MySpace {
    void add(int x, int y) { cout << x + y << endl; }
    void add(double x, int y) { cout << x + y << endl; }
    void add(int x, double y) { cout << x + y << endl; }
    void add(int x, int y, int z) { cout << x + y + z << endl; }
} 
