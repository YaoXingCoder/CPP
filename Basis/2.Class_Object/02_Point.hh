#ifndef __POINT_HH
#define __POINT_HH

class Point {
public:
    /* 构造函数 */
    Point();
    Point(const int x, const int y);

    /* 赋值运算符函数 */
    Point & operator=(const Point & rhs);

    /* 普通函数 */
    void setX(const int x);
    void setY(const int y);
    void print();
private:
    int _ix;
    int _iy;
};

#endif
