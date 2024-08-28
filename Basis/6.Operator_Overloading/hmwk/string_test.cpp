/*************************************************************************
    > File Name: string_test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 16时02分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 库函数 string 测试
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

/* =============== test =============== */
void test0() {
    string str1 = "Hello";
    string str2 = "World";

    cout << str1 + str2 << endl;
    string str3 = str1 + str2;
    str3 += " ";
    cout << str3 << endl;
    cout << str1 << endl;

    cin >> str1;
    cout << str1 << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
