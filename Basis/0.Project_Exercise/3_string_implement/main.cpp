/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 21时34分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

/* #include "SSOString.hh" */
#include "String.hh"

/* =============== test =============== */
/* void test0() { */
/*     /1* SSOString s1; *1/ */ 
/*     SSOString s2("hello"); */
/*     std::cout << s2 << ", " << s2.size() << std::endl; */ 
/*     SSOString s3("hello,world, it's time to happy."); */
/*     std::cout << s3 << ", " << s3.size() << std::endl; */ 
/*     SSOString s4(SSOString("world")); */
/*     std::cout << s4 << ", " << s4.size() << std::endl; */
/*     SSOString s5(s2); */
/*     std::cout << s5 << ", " << s5.size() << std::endl; */
/*     /1* s5 = s3; *1/ */
/*     /1* std::cout << s5 << ", " << s5.size() << std::endl; *1/ */
/*     s5 = std::move(s3); */
/*     std::cout << s5 << ", " << s5.size() << std::endl; */
/*     std::cout << s3 << ", " << s3.size() << std::endl; */ 
/* } */

CowString func1() {
    return CowString("test");
}

void test1() {
    /* CowString cStr1; */
    /* CowString cStr2("hello"); */
    /* CowString cStr3(CowString("world")); */
    /* CowString cStr4 = cStr2; */
    /* cStr4 = std::move(cStr3); */
    CowString cStr5 = CowString("hi");
    cStr5 = func1();
    /* std::cout << "cStr2 count : "  << cStr2.use_count() << std::endl; */
    /* std::cout << "cStr3 count : "  << cStr3.use_count() << std::endl; */
    std::cout << "cStr5 count : "  << cStr5.use_count() << std::endl;
    /* std::cout << cStr2 << std::endl; */
    /* std::cout << cStr3 << std::endl; */
}

/* 成员访问 */
void test2() {
    CowString str1("hello");
    str1[3] = str1[1] = 'E';
    char ch = str1[1];
    std::cout << ch << std::endl;
    std::cout << str1 << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    /* test1(); */
    test2();
    return 0;
}
