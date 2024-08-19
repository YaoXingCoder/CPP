/*************************************************************************
    > File Name: 03_str_traversal.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月17日 星期六 11时19分38秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 遍历字符串
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void test01() {
    string str1("wangdao");

    /* 方式1 for循环
     */
    for(int idx = 0; idx < str1.size(); ++idx) {
        cout << str1[idx] << " ";
    }

    cout << endl;

    /* 方式2 增强for循环
     * 增强for循环, 通常与auto连用
     * 加& 操作元素本身
     * 不加& 操作的元素的副本
     */
    for(char & ch : str1) {
        cout << ch << " ";
    }
    cout << endl;
    for(char  ch : str1) {
        cout << ch << " ";
    }
    cout << endl;

    /* iterator 通过迭代器遍历string 
     *
     * */
    string::iterator it = str1.begin();
    while(it != str1.end()) {
        cout << *it << " ";
        /* cout << &*it << " "; */ 
        printf("%p\t", &*it);
        it++;
        cout << endl;
    }
}

/* at() 检查索引是否有效 */
void test02() {
    string str01("wangdao");
    string::iterator it1 = str01.begin();
    cout << *it1 << endl;
    cout << str01.find("a") << endl;
    cout << str01.at(str01.find("a")) << endl;
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
