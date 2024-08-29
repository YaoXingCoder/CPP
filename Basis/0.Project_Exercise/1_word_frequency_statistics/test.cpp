/*************************************************************************
    > File Name: test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 11时39分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

/* =============== test =============== */
void test0(std::string &word) {
    if (word.empty()) { return; }
    std::string::iterator it = word.begin();
    while (it != word.end()) {
        if ( isalpha(*it)) { it++; }
        /* else { *it = 'h'; } */
        else { it = word.erase(it); }
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    std::string str1 = "123hello";
    std::string str2;
    test0(str1);
    test0(str2);
    cout << str1 << endl;
    cout << str2 << endl;
    return 0;
}
