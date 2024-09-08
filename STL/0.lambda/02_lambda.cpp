/*************************************************************************
    > File Name: 02_lambda.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月07日 星期六 18时09分06秒
    > Mail: JiaZiChunQiu@163.com
    > Title: lambda 表达式
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>

int date = 2024;

/* =============== test =============== */
void test0() {
    int num = 200;
    std::string name("hello");
    int age = 10;

    /* 可以将外部的局部变量分别进行捕获, 值捕获和引用捕获可以同时使用 */
    [num, &age, name](int value) {
        ++value;
        std::cout << "value = " << value << std::endl;
        std::cout << "num = " << num << std::endl;
        ++age;
        std::cout << "age = " << age << std::endl;
        std::cout << "name = " << name << std::endl;
    }(100);

    std::cout << std::endl << "-------------------------" << std::endl;
    /* =: 将外部的局部变量同时进行 引用捕获 */
    [=](int value)mutable {
        ++value;
        std::cout << "value = " << value << std::endl;
        std::cout << "num = " << num << std::endl;
        ++age;
        std::cout << "age = " << age << std::endl;
        std::cout << "name = " << name << std::endl;
        std::cout << "date = " << date << std::endl;
    }(100);

    std::cout << std::endl << "-------------------------" << std::endl;
    /* &: 将外部的局部变量同时进行 值捕获 */
    [&](int value) {
        ++value;
        std::cout << "value = " << value << std::endl;
        std::cout << "num = " << num << std::endl;
        ++age;
        std::cout << "age = " << age << std::endl;
        std::cout << "name = " << name << std::endl;
    }(100);

    std::cout << std::endl << "-------------------------" << std::endl;
    /* =: 将外部的局部变量同时进行 值捕获 
     * age: &age 单独 引用捕获*/
    [=, &age](int value) {
        ++value;
        std::cout << "value = " << value << std::endl;
        std::cout << "num = " << num << std::endl;
        ++age;
        std::cout << "age = " << age << std::endl;
        std::cout << "name = " << name << std::endl;
    }(100);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
