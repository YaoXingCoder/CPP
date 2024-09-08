/*************************************************************************
    > File Name: 02_map_basic.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 21时09分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title: map 键值对 初始化 插入
    > Content:
 ************************************************************************/

#include <iostream>
#include <map>
#include <utility>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::make_pair;
using std::string;

template <typename Container>
void display(const Container &con){
    for(auto &elem : con) { cout << elem.first << "  " << elem.second << endl; }
}

/* =============== test =============== */
void test0() {
    map<int, string> number = {
        {1, "hello"},//1、直接使用大括号构建pair
        {4, "hello"},
        {8, ""},
        make_pair(3, "beijing"),//2、使用make_pair的返回结果构建pair类型
        make_pair(7, "nanjing"),
        pair<int, string>(4, "wangdao"),//3、使用pair的构建函数构建pair
        pair<int, string>(5, "dongjing"),
    };
    display(number);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
