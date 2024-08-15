/*************************************************************************
    > File Name: 02_Point.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月15日 星期四 22时13分18秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "02_Point.hh"
#include <iostream>

/* 构造函数 */
Point::Point()
    : _ix(0)
    , _iy(0)
{
    std::cout << "Point()" << std::endl;
}

Point::Point(const int x, const int y)
    : _ix(x)
    , _iy(y)
{
    std::cout << "Point(const int x, const int y)" << std::endl;
}

/* 赋值运算符函数 */
Point & Point::operator=(const Point & rhs) {
    _ix = rhs._ix;
    _iy = rhs._iy;
    std::cout << "operator=()" << std::endl;
    return *this;
}

/* 普通函数 */
void Point::print() {
    std::cout << "(" << _ix << "," << _iy << ")" << std::endl;
}
