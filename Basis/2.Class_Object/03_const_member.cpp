/*************************************************************************
    > File Name: 03_const_member.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月16日 星期五 19时38分57秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 特殊的数据成员 对象的组织
    > Content:
    >   1.常量成员
    >   2.引用成员
    >   3.
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;


/* ====================类的定义==================== */

class Point{
public:    
    Point(); /* 无参构造函数 */ 
    Point(int, int y); /* 有参构造函数 */

    ~Point(); /* 析构函数 */

    Point(const Point& rhs); /* 拷贝构造函数 */

    Point & operator=(const Point& rhs); /* 赋值运算符函数 */

    void print(); /* 普通函数 */

private:
    /* const int _ix; */
    int _ix;
    /* const int _iy; */
    int _iy;
    /* int & _iz; /1* 一定要有值 *1/ */
};

class Line{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine();
private:
    Point _pt1;
    Point _pt2;
};

/* =====================Point类函数实现===================== */

/* inline Point::Point () : _ix(0) , _iy(0) { */
inline Point::Point () : _ix(0), _iy(0) {
    /* _ix = 0; */
    /* _iy = 0; */
    cout << "Point() 无参构造器" << endl; /* 构造器的初始化列表能够对const进行初始化 */
}

inline Point::Point(int x, int y) : _ix(x), _iy(y) {
    cout << "Point(int x, int y) 有参构造函数 " << endl;
}

inline Point::~Point() {
    cout << "~Point() 析构函数" << endl;
}

/* inline Point::Point(const Point& rhs) : _ix(rhs._ix), _iy(rhs._iy) { */
/*     cout << "Point(const Point& rhs) 拷贝构造函数" << endl; */
/* } */

inline Point& Point::operator=(const Point& rhs) {
    cout << "Point& operator=(const Point& rhs) 赋值运算符函数" << endl;
    _ix = rhs._ix;
    _iy = rhs._iy;
    /* _iz = rhs._iz; */
    return *this;
}

inline void Point::print() {
    cout << "(" << _ix << ", "  << _iy << ")" << endl;
    /* cout << _iz << endl; */
}

/* =====================Line类函数实现===================== */

inline Line::Line(int x1, int y1, int x2, int y2) : _pt1(x1, y1) , _pt2(x2, y2) {
    cout << "Line 有参构造器" << endl;
}

void Line::printLine() {
    _pt1.print();
    cout << "----->";
    _pt2.print();
    cout << endl;
}

inline Line::~Line() {
    cout << "~Line() 析构函数"  << endl;
}

/* ======================测试函数==================== */

void test01() {
    int a = 1, b = 2, c = 3;
    Point pt01(1, 2);
    pt01.print();

    Point pt02;
    pt02.print();

    pt02 = pt01;
    pt02.print();
}

void test02() {
    Line ll(1, 2, 3, 4);
    ll.printLine();
}

/* ======================主函数==================== */

int main (int argc, char* argv[]) {
    test02();
    return 0;
}
