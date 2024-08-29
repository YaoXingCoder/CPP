/*************************************************************************
    > File Name: 04_specialized_template.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 21时44分26秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 特化模板
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
using std::cout;
using std::endl;
using std::string;
using std::strlen;

template<class T>
T add(T t1, T t2) {
    /* cout << "template" << endl; */
    return t1 + t2;
}

/* int add (int x, int y) { */
/*     return x + y; */
/* } */

/* 必须有通用模板函数, 且函数名相同 */
template <>
const char * add<const char *>(const char * p1, const char * p2){
    // 先开空间
    char * ptmp = new char[strlen(p1) + strlen(p2) + 1]();
    strcpy(ptmp, p1);
    strcat(ptmp, p2);
    return ptmp;
}

/* =============== test =============== */
void test0() {
    string s1("hello");
    string s2("world");

    cout << add(s1, s2) << endl;
    cout << add(1, 2) << endl;
    
    const char* pstr1 = "hello";
    const char* pstr2 = "world";
    /* cout << add(pstr1, pstr2) << endl; */
    cout << add<string>(pstr1, pstr2) << endl; // 转换

    /* 定义特化后, 可显示 可隐式 */
    /* const char * p = add<const char *>("hello", ",world"); // 显示  */
    const char * p = add("hello", ",world"); // 隐式
    /* cout << add("hello", "world") << endl; // 内存泄漏 */
    cout << p << endl;
    delete [] p;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
