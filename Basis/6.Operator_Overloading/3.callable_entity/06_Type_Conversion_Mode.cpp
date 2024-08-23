/*************************************************************************
    > File Name: 05_Type_conversion_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 20时32分53秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 能够转换类型的几种方式, 以及他们的优先级
    > Content:
    >   1.类型转换函数 (优先级次之)
    >   2.特殊赋值函数 (三个存在时 特殊赋值优先级最高)
    >   3.隐式转换(特殊构造函数 + 赋值) (少用)
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Point;

class Complex {
public:
    Complex(int real, int image) : _real(real) , _image(image) {
        cout << "Complex(int real, int image)" << endl;
    }

    Complex& operator=(const Complex& rhs) {
        cout << "Complex& operator=( const Complex& rhs ) 赋值" << endl;
        _real = rhs._real;
        _image = rhs._image;
        return *this;
    }

    /* 特殊构造 */
    Complex(const Point& rhs);

    void print() const{ cout << _real << " + " << _image << "i" << endl; }

    /* 赋值运算 */
    Complex& operator=(const Point& rhs);
private:
    int _real;
    int _image;
};

class Point{
public:
    Point(int x = 1, int y = 2) : _ix(x) , _iy(y) {
        cout << "Point( int x, int y )" << endl;
    }
    void print() { cout << "( " << _ix << ", " << _iy << " )" << endl; }

    /* Point -> int */
    operator int(){
        cout << "operator int()" << endl;
        return _ix + _iy;
    }

    /* Point -> Complex */
    operator Complex() {
        cout << "operator Complex() 类型转换函数 " << endl;
        return Complex(_ix, _iy);
    }

    /* 友元函数 */
    friend Complex& Complex::operator=(const Point& rhs);
    friend Complex::Complex(const Point& rhs);
private:
    int _ix;
    int _iy;
};

/* 特殊的构造函数 
 * 实际时使用 Point 创建一个匿名的 Complex 对象, 再将匿名的 Complex对象 赋值*/
Complex::Complex(const Point& rhs) : _real(rhs._ix) , _image(rhs._iy)
{ cout << "Complex(const Point& rhs) 特殊构造" << endl; }

/* 因为需要访问 Point 中的私有成员, 所以需要在 Point类 中声明友元函数 
 * 特殊的赋值运算符函数 */
Complex& Complex::operator=(const Point& rhs) {
    cout << "Complex::operator=(const Point& rhs) 特殊的赋值运算符函数" << endl;
    _real = rhs._ix;
    _image = rhs._iy;
    return *this;
}

/* ================= 测试 ====================== */
void test0() {
    Point pt1(1, 2);
    Complex cp1(3, 4);
    cp1 = pt1; /* 类型转换 */
    
    Complex cp2 = cp1; /* 定义特殊的赋值运算符函数后, 默认的仍存在 */

    cout << endl << "========== start ==========" << endl;
    pt1.print();
    cp1.print();
    cp2.print();
    cout << endl << "========== end ==========" << endl;
}

/* ================= main ====================== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
