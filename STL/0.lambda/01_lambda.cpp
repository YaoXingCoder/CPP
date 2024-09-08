/*************************************************************************
    > File Name: 01_lambda.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月07日 星期六 11时39分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: _lambda 表达式
    > Content:
 ************************************************************************/

#include <iostream>

void func1() {
    int number = 100;
    /* lambda 表达式 -> 匿名函数 
     * [] 捕获列表
     * 捕获方式:
     * 1. 值捕获: 拷贝一份到表达式中, 为值传递
     * 2. 引用捕获[&]: 将引用传递进来, 为引用传递
     * () 参数列表
     * {} 函数体
     * -> 返回值类型
     */
    std::cout << "number = " << number << std::endl; // error: number 没有被捕获
    /* [number](int value)->void{ */
    [number](int value)mutable{ // mutable 关键字: 将变量变为可修改的, 此时修改number, 仍是值传递
        ++value;
        ++number; // [number]捕获的number, 为 read_only, 需要更改为[&number]捕获
        std::cout << value << " " << std::endl;
        std::cout << "number = " << number << std::endl; // error: number 没有被捕获
    }(100); // (100): 调用匿名函数, 没有则不能调用
    std::cout << "number = " << number << std::endl; // error: number 没有被捕获
}

/* =============== test =============== */
void test0() {
    func1();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
