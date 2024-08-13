/*************************************************************************
    > File Name: ref_04.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月13日 星期二 09时03分00秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

void test0 () {
    int num = 100;
    int &ref = num;

    std::cout << num << std::endl;
    std::cout << ref << std::endl;
    std::cout << &num << std::endl;
    std::cout << &ref << std::endl;

    int num2 = 200;
    ref = num2;
    cout << ref << endl;
    cout << num << endl;
    cout << num2 << endl;
    cout << &ref << endl;
    cout << &num << endl;
    cout << &num2 << endl;

}

int main (int argc, char* argv[]) {
    
    test0();
    return 0;
}
