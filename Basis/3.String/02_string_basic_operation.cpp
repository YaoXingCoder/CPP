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

/* string 常规操作 */
void test02() {
    string str1("hello");
    const char* pstr = "world";
    /* printf("%s\n", str1); /1* 不可使用str1替换C中的char* *1/ */
    cout << str1 << endl; /* << 重载后输出到 cout 可以使用 */
    printf("%s\n", str1.data()); /* data() 是 cstring 中的封装 */
    printf("%s\n", str1.c_str()); /* 需使用string中的函数方法 更推荐c_str()*/
    printf("%s\n", pstr);

    cout << "is str1 empty? " << str1.empty() << endl; /* empty() 判空 */
    cout << "str1's size: " << str1.size() << endl; /* size() 字符数 */
    cout << "str1's size: " << str1.length() << endl; /* lenght() 字符数 */
    str1.push_back('!'); /* 追加字符 */
    cout << str1 << endl;

    string str2("world");
    str1.append(str2); /* 追加字符串 */
    cout << str1 << endl;
    str1.append("hi!");
    cout << str1 << endl;

    string str3("hello,wold,hi,wor123!");
    int ret_find = str3.find("wor", 0, 1);
    cout << ret_find << endl;
}

int main (int argc, char* argv[]) {
    test02();
    return 0;
}
