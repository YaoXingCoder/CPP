/*************************************************************************
    > File Name: 01_list_char_vector_string.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 19时56分19秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 编写代码：将一个list中的char *指针元素赋值给一个vector中的string。
    > Content:
    >   1.加入list的定义如下，list<char*> lst= { "hello", "world", "!"  };
    >   2.如何将list中的内容赋值给vector<string>]
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <list>

template<typename Container>
void display(Container & con) {
    for (std::string str : con) { std::cout << str << " ";}
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    std::list<const char*> lst = {"hello", "world", "!"};
    std::vector<std::string> vec_str;
    /* std::vector<std::string> vec_str(lst.size()); */
    display(lst);
    
    /* 赋值 */
    std::list<const char*>::iterator it_ls = lst.begin();
    /* std::vector<std::string>::iterator it_vec = vec_str.begin(); */

    while(it_ls != lst.end()) {
        vec_str.emplace_back(*it_ls);
        ++it_ls;
    }

    display(vec_str);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
