/*************************************************************************
    > File Name: 07_function_container.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 15时38分18秒
    > Mail: JiaZiChunQiu@163.com
    > Title: function 容器
    > Content:
    >   1.lambda 的 类型
 ************************************************************************/

#include <iostream>
#include <functional>
#include <vector>
#include <string>

std::vector<std::function<void(const std::string &)>> vec_str;

/* =============== test =============== */
void test0() {
    int num = 100;
    std::string name("wangdao");

    /* function 接收 lambda 函数 */
    /* std::function<void(const std::string &)> f = [&](const std::string & str){ */
    /*                     std::cout << "num = " << num << std::endl; */
    /*                     std::cout << "name = " << name << std::endl; */
    /*                     std::cout << "str = " << str << std::endl; */
    /* }; */

    /* vec_str.push_back(f); // 发生拷贝 */

    /* 在 vec 容器中注册了回调函数 */
    vec_str.push_back([=](const std::string & str){
                        std::cout << "num = " << num << std::endl;
                        std::cout << "name = " << name << std::endl;
                        std::cout << "str = " << str << std::endl;
                      });

    /* for ( std::function<void(const std::string &)> & f : vec_str ) { */
    /*     f("wuhan"); // 遍历容器, 并调用 */
    /* } */
}

void test1() {
   test0();
    for ( std::function<void(const std::string &)> & f : vec_str ) {
        f("wuhan"); // 遍历容器, 并调用
    }
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test1();
    return 0;
}
