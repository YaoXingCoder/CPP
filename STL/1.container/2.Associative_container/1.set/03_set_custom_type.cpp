/*************************************************************************
    > File Name: 03_set_custom_type.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月04日 星期三 16时49分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: set 自定义类型
    > Content:
 ************************************************************************/

#include <iostream>
#include <cmath>
#include <set>
using namespace std;

template <typename Container>
void display(const Container &con) {
    for(auto &elem : con) { cout << elem << "  "; }
    cout << endl;
}

class Point {
public:
    Point(int x = 0, int y = 0) : _ix(x), _iy(y) {}
    ~Point() {};

    int getX() const { return _ix; }
    int getY() const { return _iy; }
    float getDistance () const { return hypot(_ix, _iy); }

    friend ostream & operator<<(ostream &, const Point &);
private:
    int _ix;
    int _iy;
};

ostream & operator<<(ostream & os, const Point & obj) {
    return os << "( " << obj._ix << ", " <<  obj._iy <<" )";
}

/* 运算符重载 */
bool operator<(const Point & lhs, const Point & rhs) {
    cout << "运算符重载调用" << endl;
    if ( lhs.getDistance() < rhs.getDistance() ) { return true; }
    else if ( lhs.getDistance() == rhs.getDistance() ) {
        if ( lhs.getX() < rhs.getX() ) { return true; }
        else if ( lhs.getX() == rhs.getX() ) {
            if ( lhs.getY() < rhs.getY() ) { return true; }
            else { return false; }
        }else { return false; }
    }else { return false; }
}

bool operator>(const Point & lhs, const Point & rhs) {
    if ( lhs.getDistance() > rhs.getDistance() ) { return true; }
    else if ( lhs.getDistance() == rhs.getDistance() ) {
        if ( lhs.getX() > rhs.getX() ) { return true; }
        else if ( lhs.getX() == rhs.getX() ) {
            if ( lhs.getY() > rhs.getY() ) { return true; }
            else { return false; }
        }else { return false; }
    }else { return false; }
}

/* 函数对象方式 */
struct ComparePoint {
    /* 最后的 const 必须带上, 因为对象在传递过程中可能采用常量的方式, 
     * 所以常量对象只能调用 const 函数 */
    bool operator()(const Point & lhs, const Point & rhs) const{
        if ( lhs.getDistance() > rhs.getDistance() ) { return true; }
        else if ( lhs.getDistance() == rhs.getDistance() ) {
            if ( lhs.getX() > rhs.getX() ) { return true; }
            else if ( lhs.getX() == rhs.getX() ) {
                if ( lhs.getY() > rhs.getY() ) { return true; }
                else { return false; }
            }else { return false; }
        }else { return false; }
    }
};

/* 命名空间的扩展 */
namespace std{
    template<>
    struct less<Point> {
        bool operator()(const Point & lhs, const Point & rhs) const{
            cout << "命名空间调用" << endl;
            if ( lhs.getDistance() < rhs.getDistance() ) { return true; }
            else if ( lhs.getDistance() == rhs.getDistance() ) {
                if ( lhs.getX() < rhs.getX() ) { return true; }
                else if ( lhs.getX() == rhs.getX() ) {
                    if ( lhs.getY() < rhs.getY() ) { return true; }
                    else { return false; }
                }else { return false; }
            }else { return false; }
        }
    };
}

/* =============== test =============== */
void test0() {
    /* set<Point> number = { */
    /* set<Point, ComparePoint> number = { */
    set<Point> number = {
        Point(1, 2),
        Point(1, -2),
        Point(-1, 2),
        Point(1, 2),
        Point(3, 2),
        Point(4, 2)
    };
    display(number);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
