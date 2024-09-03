/*************************************************************************
    > File Name: 02_input_string_deque.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 20时07分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 从标准输入读取 string 序列，存入一个 deque 中。编写一个循环，用迭代器打印 deque 中的元素。
    > Content:
    >   1.熟悉deque的基本函数的使用方式。
 ************************************************************************/

#include <iostream>
#include <deque>

template<typename Container>
void display(Container & con) {
    for (std::string str : con ) { std::cout << str << " "; }
}

/* =============== test =============== */
void test0() {
    std::string word;
    std::deque<std::string> dq_str; // 用于存放单词
    while(getline(std::cin, word)) { 
        if ( word.empty() ) { break; }
        dq_str.emplace_back(word);
    }

    /* 输出 */
    display(dq_str);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
