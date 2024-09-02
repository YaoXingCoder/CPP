/*************************************************************************
    > File Name: test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 16时20分26秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 测试
    > Content:
    >   1.字符串替换测试 
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <string>

void query(const std::string & word) {
    std::cout << "----------------------------------------------------" << std::endl;
    std::string word_occurs("element occurs number times.");
    std::string word_element("element");
    std::string::size_type n = word_occurs.find("element");
    word_occurs.replace(n, word_element.size(), word);
    n = word_occurs.find("number");
    word_occurs.replace(n, std::strlen("number"), std::to_string(111));
    std::cout << word_occurs << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

void identified_words(std::string & line, const std::string & word) {
    std::string::size_type n = 0;
    std::string word_color =  "\e[31m" + word + "\e[0m";
    while( (n = line.find(word, n)) != std::string::npos)  {
        line.replace(n, word.size(), word_color);
        n += word_color.size(); // 移动搜索位置到替换后的字符串之后
        std::cout << line << std::endl;
    }
}
/* =============== test =============== */
void test0() {
    /* query("hello"); */

    /* 颜色输出 */
    /* std::string word("hello"); */
    /* std::string word_color( "\e[31m" + word + "\e[0m"); */
    /* std::cout << word_color << std::endl; */

    std::string line("The Chinese mainland will likely announce the launch of the much-anticipated");
    std::string word("the");
    identified_words(line, word);
    /* std::cout << line << std::endl; */
}

void test1() {
    std::string s("1a2b3c4d5e6f7jkg8h9i1a2b3c4d5e6f7g8ha9i");
    char flag= 'a';
    int position = 0;
    int i = 1;
    while((position = s.find(flag, position)) != std::string::npos) {
        std::cout << "position  " << i << " : " << position << std::endl;
        position++;
        i++;
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    /* test1(); */
    return 0;
}
