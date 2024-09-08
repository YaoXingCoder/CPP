/*************************************************************************
    > File Name: 01_cutomize.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 21时46分16秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <unordered_set>

using std::cout;
using std::endl;
using std::unordered_set;

template <typename Container>
void display(const Container &con) {
    for(auto &elem : con) { cout << elem << "  "; }
    cout << endl;
}

class Point {
public:
    Point(int ix = 0, int iy = 0) : _ix(ix) , _iy(iy) {}

    int getX() const { return _ix; }
    int getY() const { return _iy; }

    ~Point(){}
private:
    int _ix;
    int _iy;
};

std::ostream & operator<<(std::ostream & os, const Point & obj) {
    return os << "( " << obj.getX() << ", " << obj.getY() << " )";
}

/* 哈希函数 */
/* 命名空间 */
namespace std {
template<>
    struct hash<Point>{
        size_t operator()(const Point & obj) const {
            return (obj.getX() << 2)^(obj.getY() << 2);
        }
    };
}

/* 函数对象 */
struct hash {
    size_t operator()(const Point & obj) const  {
        return (obj.getX() << 2)^(obj.getY() << 2);
    }
};

/* 处理哈希冲突 */
/* 运算符重载 */
bool operator==(const Point & lhs, const Point & rhs) {
    return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}

/* 函数对象 */
struct EqualToPoint {
    bool operator()(const Point &lhs, const Point &rhs) const {
        cout << "struct EqualToPoint" << endl;
        return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
    }
};

/* 模板特化 */
namespace std {
template <>
    struct equal_to<Point> {
        bool operator()(const Point &lhs, const Point &rhs) const {
            return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
        }
    };
}

/* =============== test =============== */
void test0() {
    unordered_set<Point, hash> number = {
        Point(-1, 2),
        Point(1, 2),
        Point(1, 2),
        Point(3, 2),
        Point(1, -2),
        Point(1, 2),
        Point(2, 7),
        Point(2, 1),
    };
    display(number);

    unordered_set<Point, hash>::iterator it_un = number.find(Point(1, -2));
    cout << *it_un << endl;
    it_un++;
    cout << *it_un << endl;
    cout << *it_un << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
