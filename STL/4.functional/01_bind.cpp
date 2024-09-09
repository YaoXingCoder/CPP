/*************************************************************************
    > File Name: 03_bind.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 10时01分29秒
    > Mail: JiaZiChunQiu@163.com
    > Title: bind
    > Content:
 ************************************************************************/

#include <iostream>
#include <functional>

int add(int x, int y){
    std::cout << "int add(int, int)" << std::endl;
    return x + y;
}

int multiply(int x, int y, int z) {
    std::cout << "int multiply(int, int, int)" << std::endl;
    return x * y * z;
}

class Example {
public:
    int add(int x, int y) {
        std::cout << "int Example::add(int, int)" << std::endl;
        return x + y;
    }
};

/* =============== test =============== */
/* _1, _2 ... _N  占位符 */
void test1() {
    /* auto f = std::bind(add, 1, std::placeholders::_1); */
    std::function<int(int)> f = std::bind(add, 1, std::placeholders::_1);
    f(1);
}

/* bind 绑定函数 */
void test0() {
    /* 普通函数 */
    /* std::function<int()> f_add = std::bind(add, 1, 2); */
    std::function<int()> f_add = std::bind(&add, 1, 2); // 规范形式
    std::cout << f_add() << std::endl;

    /* 成员函数 */
    /* 成员函数, 参数列表中隐藏有 *this 指针, 所以需要传入对象地址
     * 成员函数的函数地址需要 &className::memFunc 获取 
     * */
    Example example;
    std::function<int()> f_mem = std::bind(&Example::add, &example, 10, 20);
    std::cout << f_mem() << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
