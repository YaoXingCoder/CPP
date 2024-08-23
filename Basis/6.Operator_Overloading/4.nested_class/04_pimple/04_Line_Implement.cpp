/*************************************************************************
    > File Name: 04_Line_Implement.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 11时13分03秒
    > Mail: JiaZiChunQiu@163.com
    > Title: Line.hh 的实现
    > Content:
 ************************************************************************/
#include "04_Line.hh"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Line::LineImpl {
    class Point{
    public:
        Point(int x,int y)
            : _ix(x)
              , _iy(y)
        {}
		//...
    private:
        int _ix;
        int _iy;
    };

private:
    Point _pt1;
    Point _pt2;
};

Line::Line(int x1, int y1, int x2, int y2)
    : _pimpl(new LineImpl(x1, y1, x2, y2)){}

Line::~Line() {
    if (_pimpl) {
        delete _pimpl;
        _pimpl = nullptr;
    }
}

/* ============ 测试 ============ */

void test0(){
    Line line(10,20,30,40);
    line.printLine();
}

int main (int argc, char* argv[]) {
    test0();
    return 0;
}
