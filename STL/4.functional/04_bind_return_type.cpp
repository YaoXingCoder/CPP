/*************************************************************************
    > File Name: 06_bind_return_type.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 14时54分38秒
    > Mail: JiaZiChunQiu@163.com
    > Title: bind 返回类型
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
void test0() {
    std::cout << add(1, 2) << std::endl; // add 函数形态：int(int, int);
    std::cout << multiply(1, 2, 3) << std::endl; // multiply 函数形态：int(int, int, int);
    std::cout << Example().add(1, 2) << std::endl; // Example add 函数形态：int(int, int);

    // f的形态:int()
    std::cout << std::endl;
    std::function<int()> f = std::bind(&add, 1, 2);
    std::cout << "f() = " << f() << std::endl;

    // f2的形态:int()
    std::function<int()> f2 = std::bind(&multiply, 3, 4, 5);
    // 因为 f 和 f2 的形态一样, 所以可以赋值
    f = f2;
    std::cout << "f2() = " << f2() << std::endl;
    std::cout << "f() = " << f() << std::endl;

    // f3的形态:int()
    Example ex;
    std::function<int()> f3 = std::bind(&Example::add, &ex, 10, 20);
    std::cout << "f3() = " << f3() << std::endl;

    //占位符
    // f4的形态:int(int)
    std::function<int(int)> f4 = std::bind(add, 100, std::placeholders::_1);
    std::cout << "f4(300) = " << f4(300) << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
