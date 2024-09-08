/*************************************************************************
    > File Name: 02_multiset_customize.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 20时25分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 自定义 multiset
    > Content:
    >   1.operator 函数重载
    >   2.命名空间 + 特例模板
    >   3.函数对象
 ************************************************************************/
#include <math.h>
#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::multiset;

template <typename Container>
void display(const Container &con) {
    for(auto &elem : con) { cout << elem << "  "; }
    cout << endl;
}

class Point {
public:
    Point(int ix = 0, int iy = 0) : _ix(ix) , _iy(iy) {}

    //计算点到原点的距离
    float getDistance() const { return hypot(_ix, _iy); }
    int getX() const { return _ix; }
    int getY() const { return _iy; }

    ~Point(){}
private:
    int _ix;
    int _iy;
};

/* < 运算符重载 */
bool operator<(const Point & lhs, const Point & rhs) {
    if ( lhs.getDistance() == rhs.getDistance() ) {
        if ( lhs.getX() == rhs.getX() ) {
            if ( lhs.getY() == rhs.getY()) { return false; } 
            else { return lhs.getY() < rhs.getY(); }
        } else { return lhs.getX() < rhs.getX(); }
    } else { return lhs.getDistance() < rhs.getDistance(); }
}

/* 命名空间 + 特例模板 */
namespace std {
template<>
    struct less<Point>{
        bool operator()(const Point & lhs, const Point & rhs) const {
            /* cout << "template + namespace" << endl; */
            if ( lhs.getDistance() == rhs.getDistance() ) {
                if ( lhs.getX() == rhs.getX() ) {
                    if ( lhs.getY() == rhs.getY()) { return false; } 
                    else { return lhs.getY() < rhs.getY(); }
                } else { return lhs.getX() < rhs.getX(); }
            } else { return lhs.getDistance() < rhs.getDistance(); }
        }
    };
}

/* 函数对象 */
struct Compare {
    bool operator()(const Point & lhs, const Point & rhs) const {
        cout << "struct Compare" << endl;
        if ( lhs.getDistance() == rhs.getDistance() ) {
            if ( lhs.getX() == rhs.getX() ) {
                if ( lhs.getY() == rhs.getY()) { return false; } 
                else { return lhs.getY() < rhs.getY(); }
            } else { return lhs.getX() < rhs.getX(); }
        } else { return lhs.getDistance() < rhs.getDistance(); }
    }
};

/* << 输出重载 */
std::ostream & operator<<(std::ostream & os, const Point & obj) {
    return os << "( " << obj.getX() << ", " << obj.getY() << " )";
}

/* =============== test =============== */
void test0() {
    /* multiset<Point> number = { */
    multiset<Point, Compare> number = {
        Point(1, 2),
        Point(1, -2),
        Point(-1, 2),
        Point(1, 2),
        Point(3, 2),
        Point(4, 2),
    };
    display(number);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
