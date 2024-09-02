/*************************************************************************
    > File Name: 04_intialize_string_by_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 21时53分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 从一个 vector<char> 初始化一个 string。
    > Content:
    >   可以定义vector如下：vector<char> vc = { 'H', 'E', 'L', 'L', 'O' };
    >   然后查看如何给string进行初始化或者赋值，考查对vector与string的基本使用
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>

/* =============== test =============== */
void test0() {
    std::vector<char> vc = { 'H', 'E', 'L', 'L', 'O' };
    std::string str_vc;
    str_vc.resize(vc.size() + 1);

    std::vector<char>::iterator it_vc = vc.begin();
    std::string::iterator it_str = str_vc.begin();
    int idx = 0;
    while(it_vc != vc.end()) {
        *it_str = *it_vc;
        ++it_vc;
        ++it_str;
    }
    *it_str = '\0';

    std::cout << str_vc << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
