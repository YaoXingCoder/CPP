/*************************************************************************
    > File Name: 01_string_t1.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月17日 星期六 10时15分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: string 函数
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void test01() {
    string str1;
    cout << str1 <<endl;

    string str2("hello");
    cout << str2 << endl;
    
    string str3("hello", 2);
    cout << str3 << endl;

    string str4(str2);
    cout << str4 << endl;

    string str5(str2, 1, 3);
    cout << str5 << endl;

    string str6 = str2 + str3;
    cout << str6 << endl;
}

/* 迭代器 
 * 广义上的指针
 * begin() 返回收迭代器
 * */
void test02() {
    string str1("hello");
    string::iterator it = str1.begin();
    /* string::iterator ip = str1.begin(); */
    /* char* it = str1.begin(); /1* 不是指针 *1/ */
    cout << *it << endl;
    it++;
    cout << *it << endl;
    /* cout << *ip << endl; */
}

/* 根据迭代器 和 string 的区间 创建一个string对象 */
void test03() {
    cout << "test03()" << endl;
    string str1("hello");
    string::iterator it_begin = str1.begin();
    string::iterator it_end = str1.end();
    string str2(it_begin, it_end);
    cout << str2 << endl;
}

int main (int argc, char* argv[]) {
    test01();
    /* test02(); */
    /* test03(); */
    return 0;
}
