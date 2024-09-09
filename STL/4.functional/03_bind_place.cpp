/*************************************************************************
    > File Name: 05_bind_place.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 14时15分37秒
    > Mail: JiaZiChunQiu@163.com 
    > Title: 函数占位符
    > Content:
 ************************************************************************/

#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

void func(int x1, int x2, int x3, int x4, int x5) {
    /* x4 += 100; */
    cout << "x1 = " << x1 << endl
         << "x2 = " << x2 << endl
         << "x3 = " << x3 << endl
         << "x4 = " << x4 << endl
         << "x5 = " << x5 << endl;
}

void test() {
    /* 占位符整体代表的是函数的形参位置
     * 占位符中的数字代表的是实参的位置
     *
     * 传递方式：
     *  1.默认的传递方式是值传递
     *  2.引用传递需要引用包装器
     *      std::cref = const reference, const 引用的包装器
     *      std::ref = reference, 引用的包装器
     */
    int number = 100;
    /* auto f = bind(func, 10, std::placeholders::_2, std::placeholders::_2, std::cref(number), number); */
    std::function<void(int, int)> f = bind(func, 10, std::placeholders::_2, std::placeholders::_2, std::cref(number), number);
    number = 200;
    /* f(1, 20, 300, 4000, 5000); // 多余的实参直接丢掉 */
    /* f(1, 20, 300); */
    f(20, 300);
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}


