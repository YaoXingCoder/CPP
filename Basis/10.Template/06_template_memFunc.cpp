/*************************************************************************
    > File Name: 05_template_memFunc.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 15时49分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 成员函数
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Point {
public:
    Point(double x,double y) : _x(x) , _y(y) {}

    // 定义一个成员函数模板
    // 将_x转换成目标类型
    template <class T = int>
        T convert() {
            return (T)_x;
        }

    /* 添加 static 是可以, 但是函数内不能访问非static的成员 */
    /* virtual 不能添加, virtual机制 是运行时多态, template 是编译时确定, 时机不同 */
    template<class T, int kBase = 10>
        T add(T t1) {
            return (_x + _y + t1) * kBase;
        }
private:
    double _x;
    double _y;
};

/* =============== test =============== */
void test0() {
    Point pt1(1.1, 1.2);
    std::cout << pt1.convert() << std::endl; /* 模板参数默认值后可以调用 */ 
    std::cout << pt1.convert<int>() << std::endl; /* 显式实例化, 可以调用 */

    cout << pt1.add<double, 20>(1.2) << endl;
    cout << pt1.add(1.2) << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
