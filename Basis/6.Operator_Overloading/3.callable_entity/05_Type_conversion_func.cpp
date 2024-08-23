/*************************************************************************
    > File Name: 05_Type_conversion_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 20时32分53秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 类型转换函数
    > Content:
    >   1.类型转换函数 (优先级次之)
    >   2.特殊赋值函数 (三个存在时 特殊赋值优先级最高)
    >   3.隐式转换(特殊构造函数 + 赋值函数) (少用)
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Complex {
public:
    Complex(int real, int image) : _real(real) , _image(image) {
        cout << "Complex(int real, int image)" << endl;
    }
    void print() const{ cout << _real << " + " << _image << "i" << endl; }

    /* 类型转换 */
private:
    int _real;
    int _image;
};

class Point{
public:
    Point(int x = 1, int y = 2) : _ix(x) , _iy(y) {}
    void print() { cout << "( " << _ix << ", " << _iy << " )" << endl; }

    /* Point -> int */
    operator int(){
        cout << "operator int()" << endl;
        return _ix + _iy;
    }

    /* Point -> Complex */
    operator Complex() {
        cout << "operator Complex()" << endl;
        return Complex(_ix, _iy);
    }

private:
    int _ix;
    int _iy;
};

/* =================  测试 ====================== */
/* 自定义 --> 基本类型 */
void test01() {
    /* 隐式转换 */
    Point pt1 = 1;
    pt1.print();

    cout << endl << "========== 类型转换函数 ==========" << endl;
    /* Point对象 转换为 int类型 的变量
     * 本质上是 Point对象 产生一个临时的 int型 变量
     * 赋值给 a */
    int a = pt1;
    /* int a = pt1.operator int(); /1* 本质 *1/ */
    cout << a << endl;
    /* pt1.print(); */
    cout << endl << "========== end ==========" << endl;
}

/* 自定义 --> 自定义 */
void test02() {
    Point pt1(1, 2);
    Complex cp1 = pt1;

    cout << endl << "========== start ==========" << endl;
    pt1.print();
    cp1.print();
    cout << endl << "========== end ==========" << endl;
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
