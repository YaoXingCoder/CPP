/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 21时34分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "SSOString.hh"

/* =============== test =============== */
void test0() {
    SSOString s1; 
    SSOString s2("hello");
    std::cout << s2 << ", " << s2.size() << std::endl; 
    SSOString s3("hello,world, it's time to happy.");
    std::cout << s3 << ", " << s3.size() << std::endl; 
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
