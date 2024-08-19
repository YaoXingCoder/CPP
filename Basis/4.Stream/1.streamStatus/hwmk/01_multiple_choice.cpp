/*************************************************************************
    > File Name: 01_multiple_choice.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 22时01分51秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
    char *str;：这行代码声明了一个指向字符的指针 str，但它没有初始化，所以 str 目前指向一个未定义的地址。

    cin >> str;：在这行代码中，cin 会尝试将输入的字符串存储到 str 指针所指向的内存地址中。
    然而，由于 str 没有指向有效的内存区域，这会导致程序试图向未定义的内存地址写入数据，导致未定义行为，可能会导致程序崩溃。

    cout << str;：如果前面没有崩溃，cout 会尝试从 str 指针所指向的内存地址读取数据并输出。
    由于 str 没有指向有效的数据，输出内容是不可预测的。
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;

void test01() {
    char *str;
    cin >> str;
    cout << str;
}

void test02() {
    char a[200] = {0};
    cin.getline(a, 200, ' ');
    cout << a;
}

int main (int argc, char* argv[]) {
    test02();
    return 0;
}
