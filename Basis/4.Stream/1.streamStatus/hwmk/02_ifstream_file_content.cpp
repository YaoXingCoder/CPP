/*************************************************************************
    > File Name: 02_read_file_content.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 22时28分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 分别使用按单词读取的方式和按行读取的方式读取指定文件的内容
    > Content:
 ************************************************************************/
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

/* 按单词读取 */
void readFileByWord(const char* filename) {
    /* 打开文件 */
    ifstream ifs(filename);

    /* string 对象 */
    string word;

    /* 循环打印 */
    while(ifs >> word) { cout << word << endl; }
    
    /* 关闭流 */
    ifs.close();
}

void test01() {
    cout << " start " << endl;
    readFileByWord("01_multiple_choice.cpp");
    cout << " end " << endl;
}

/* 按行读取 */
void readFileByLine(const char* filename) {
    ifstream ifs(filename);

    char buff[1024] = { 0 };
    while( ifs.getline(buff, sizeof(buff))) {
        cout << buff << endl;
        memset(buff, 0, sizeof(buff));
    }

    ifs.close();
    
}

void test02() {
    cout << " start " << endl;
    readFileByLine("01_multiple_choice.cpp");
    cout << " end " << endl;
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
