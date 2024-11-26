/*************************************************************************
    > File Name: 02_priority_queue_customize.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月06日 星期五 21时42分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 自定义类型
    > Content:
 ************************************************************************/

#include <math.h>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

class Point{
public:
    Point(int ix = 0, int iy = 0) : _ix(ix) , _iy(iy) {}

    //计算点到原点的距离
    float getDistance() const { return hypot(_ix, _iy); }
    int getX() const { return _ix; }
    int getY() const { return _iy; }

    ~Point(){  }
private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs) {
    os << "(" << rhs.getX() << ", " <<rhs.getY() << ")";
    return os;
}

/* 运算符重载 */
bool operator<(const Point & lhs, const Point & rhs) {
    std::cout << "operator < 运算符重载\n";
    if ( lhs.getDistance() == rhs.getDistance() ) {
        if ( lhs.getX() == rhs.getX() ) {
            if ( lhs.getY() == rhs.getY()) { return false; }
            else { return lhs.getY() < rhs.getY(); }
        } else { return lhs.getX() < rhs.getX(); }
    } else { return lhs.getDistance() < rhs.getDistance(); }
}

/* 函数对象 */
struct Compare {
    bool operator()(const Point & lhs, const Point & rhs) const {
        if ( lhs.getDistance() == rhs.getDistance() ) {
            if ( lhs.getX() == rhs.getX() ) {
                if ( lhs.getY() == rhs.getY()) { return false; }
                else { return lhs.getY() < rhs.getY(); }
            } else { return lhs.getX() < rhs.getX(); }
        } else { return lhs.getDistance() < rhs.getDistance(); }
    }
};

/* 模板特化 */
namespace std {
template <>
    struct less<Point> {
        bool operator()(const Point & lhs, const Point & rhs) const {
            cout << "template : struct less : operator() \n";
            if ( lhs.getDistance() == rhs.getDistance() ) {
                if ( lhs.getX() == rhs.getX() ) {
                    if ( lhs.getY() == rhs.getY()) { return false; }
                    else { return lhs.getY() < rhs.getY(); }
                } else { return lhs.getX() < rhs.getX(); }
            } else { return lhs.getDistance() < rhs.getDistance(); }
        }
    };
}

/* =============== test =============== */
void test0() {
    vector<Point> vec = {
        Point(1, 2),
        Point(-1, 2),
        Point(1, -2),
        Point(1, 2),
        Point(3, 2)
    };

    priority_queue<Point, std::vector<Point>> pque;
    /* priority_queue<Point, std::vector<Point>, Compare> pque; */
    /* priority_queue<Point, std::vector<Point>> pque; */

    for(size_t idx = 0; idx != vec.size(); ++idx) {
        pque.push(vec[idx]);
        cout << "优先级最高的元素 : " << pque.top() << endl;
    }

    while(!pque.empty()) {
        cout << pque.top() << " ";
        pque.pop();
    }
    cout <<endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
