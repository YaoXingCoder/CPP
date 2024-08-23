/*************************************************************************
    > File Name: 01_Line_nest_Point.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 10时17分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 输出流输出
    > Content:
    >   1.Line 中定义 Point
    >   2.
 ************************************************************************/

#include <iostream>
#include <string>
#include <ostream>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

/* Point类 是为了给 Line类 服务
 * 可以将 Point类 定义成 Line类 的内部类 */
class Line {
public:
    /* 内部类 */
    class Point{
    public:
        Point(int x,int y) : _ix(x) , _iy(y) {}

        void print() const{
            cout << "( " << _ix << ", " << _iy << " )" << endl;
        }
        
        friend ostream& operator<<(ostream& os, const Point& rhs);
    private:
        int _ix;
        int _iy;
    };
public:
    Line(int x1, int y1, int x2, int y2)
    : _pt1(x1,y1)
    , _pt2(x2,y2)
    {}

    void printLine() const {
        _pt1.print();
        _pt2.print();
        cout << endl;
    }

    friend ostream& operator<<(ostream& os, const Line& rhs);
private:
    Point _pt1;
    Point _pt2;
};

ostream& operator<<(ostream& os, const Line::Point& rhs){
    return os << "( "  << rhs._ix << ", " << rhs._iy << " )";
}

ostream& operator<<(ostream& os, const Line& rhs){
    return os << rhs._pt1 << "---->" << rhs._pt2;
}

/* ================= 测试 ===================== */

void test01() {
    /* 如果需要创建 Point */
    Line::Point pt(1, 2);

    /* 创建 Line */
    Line ll(1, 2, 3, 4);
    ll.printLine();
    cout << ll;
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
