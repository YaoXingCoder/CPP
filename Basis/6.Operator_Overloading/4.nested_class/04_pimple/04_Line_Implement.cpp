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
using std::cout;
using std::endl;

class Line::LineImpl {
private:
    class Point{
        public:
            Point(int x,int y) : _ix(x) , _iy(y) {
                cout << "Point(int, int) 构造" << endl;
            }
            ~Point() { cout << "~Point() 析构" << endl; }

            void printPoint() const {
                cout << "( " << _ix << " ," << _iy << " )";
            }
        private:
            int _ix;
            int _iy;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2) : _pt1(x1, y1), _pt2(x2, y2) {
        cout << "LineImpl(int, int, int, int) 构造" << endl;
    }

    ~LineImpl() {cout << "~LineImpl() 析构 " << endl;}

    void printLine() const{
        _pt1.printPoint();
        cout << " -----> ";
        _pt2.printPoint();
        cout << '\n';
    }
private:
    Point _pt1;
    Point _pt2;
};

Line::Line(int x1, int y1, int x2, int y2) : _pimpl(new LineImpl(x1, y1, x2, y2)) {
    cout << "Line(int, int, int, int) 构造" << endl;
}

Line::~Line() {
    cout << "~Line() 析构 start" << endl;
    if ( _pimpl ){
        delete _pimpl;
        _pimpl = nullptr;
    }
    cout << "~Line() 析构 end" << endl;
}

void Line::printLine() const{
   _pimpl->printLine(); 
}
