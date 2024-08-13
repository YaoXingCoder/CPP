/*************************************************************************
    > File Name: overload_05.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月13日 星期二 20时15分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 函数重载 function overloading
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

float add(float x, int y) {
    return x + y;
}

float add(int x, float y) {
    return x + y;
}

int add(int x, int y) {
    return x + y;
}


int main (int argc, char* argv[]) {

    float f1 = 10.1f;
    int n1 = 10;
    
    /* 函数重载 */
    cout << add(f1, n1) << endl;
    cout << add(10, 10) << endl;
    cout << add(n1, 123) << endl;

    return 0;
}
