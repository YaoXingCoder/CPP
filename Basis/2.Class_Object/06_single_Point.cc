/*************************************************************************
    > File Name: 03_const_member.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月16日 星期五 19时38分57秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式: 想在整个系统中只能出现类的一个实例，即一个类只有一个对象
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;


/* ====================类的定义==================== */

class Point{
public:    
    static Point& getInstance();
    /* Point & operator=(const Point& rhs); /1* 赋值运算符函数 *1/ */
    void print(); /* 普通函数 */

private:
    Point(); /* 无参构造函数 */ 
    Point(int, int y); /* 有参构造函数 */
    /* Point(const Point& rhs); /1* 拷贝构造函数 *1/ */
    Point(const Point& rhs) = delete; /* 拷贝构造函数 */

    ~Point(); /* 析构函数 */

private:
    int _ix;
    int _iy;
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

inline Point& Point::getInstance() {
    static Point pt(2, 8);
    return pt;
}

inline Point::Point () : _ix(0), _iy(0) {
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

/* inline Point& Point::operator=(const Point& rhs) { */
/*     cout << "Point& operator=(const Point& rhs) 赋值运算符函数" << endl; */
/*     _ix = rhs._ix; */
/*     _iy = rhs._iy; */
/*     return *this; */
/* } */

inline void Point::print() {
    cout << "(" << _ix << ", "  << _iy << ")" << endl;
}

/* ======================测试函数==================== */
void test01() {
    Point& pt1 = Point::getInstance();
    Point& pt2 = Point::getInstance();
    cout << &pt1 << endl;
    cout << &pt2 << endl;
    
}


/* ======================主函数==================== */

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
