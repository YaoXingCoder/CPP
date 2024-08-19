/*************************************************************************
    > File Name: 05_vector_traversal.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 09时52分34秒
    > Mail: JiaZiChunQiu@163.com
    > Title: vector 遍历
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Point {
public:
    Point(int x = 1, int y = 1); /* 有参构造 + 默认参数 */
    Point(const Point& rhs); /* 拷贝构造 */
    Point& operator=(const Point& rhs); /* 赋值运算符函数 */

    ~Point();

    void print();
private:
    int _ix;
    int _iy;
};

inline Point::Point(int x, int y) :_ix(x), _iy(y) {
    cout << "Point(int x, int y) 有参构造" << endl;
}

inline Point::Point(const Point& rhs) :_ix(rhs._ix), _iy(rhs._iy) {
    cout << "Point(const Point& rhs) 拷贝构造" << endl;
}

inline Point & Point::operator=(const Point& rhs) {
    cout << "operator=(const Point& rhs) 赋值运算符函数" << endl;
    if ( this != &rhs ) {
        _ix = rhs._ix;
        _iy = rhs._iy;
    }
    return *this;
}

inline Point::~Point() {
    cout << "~Point() 析构函数" << endl;
}

inline void Point::print() {
    cout << "( " << _ix << ", " << _iy << " )" << endl;
}

void func(Point pt) {
    pt.print();
}

/* 测试函数 */
void test01() {

    /* 有参构造 */
    Point pt1(1, 2);
    pt1.print();

    /* 缺省参数 */
    Point pt2(3);
    pt2.print();
    Point pt3;
    pt3.print();
    
    /* 隐式转换 
     * 编译器会先尝试使用一个 int型 参数初始化一个匿名的 Point 对象
     * 再通过拷贝初始pt4
     * Point pt4 = Point(3);
     */
    Point pt4 = 3;
    pt4.print();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
