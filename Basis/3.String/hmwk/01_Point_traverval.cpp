/*************************************************************************
    > File Name: 01_Point_traverval.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 23时43分57秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建存放Point对象的vector，尝试进行遍历
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Point {
public:
    /* 构造函数 */
    Point()
    : _ix(0)
    , _iy(0)
    {
        std::cout << "Point() 无参构造" << std::endl;
    }

    Point(const int x, const int y = 1)
    : _ix (x)
    , _iy (y)
    {   
        std::cout << "Point(const int x, const int y) 有参构造" << std::endl;
    }

    Point(const Point& rhs) 
    : _ix (rhs._ix)
    , _iy (rhs._iy)
    {
        cout << "Point(const Point& rhs) 拷贝构造" << endl;
    }

    /* 赋值运算符函数 */
    Point& operator=(const Point & rhs) {
        _ix = rhs._ix;
        _iy = rhs._iy;
        std::cout << "operator=() 赋值运算符函数" << std::endl;
        return *this;
    }

    ~Point() {
        cout << "~Point() 析构函数" << endl;
    }

    void print() {
        cout << "( " << _ix << ", " << _iy << " )" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test01() {
    vector<Point> pnums0; /* 创建vector容器, 存放元素为 vector */

#if 0
    vector<Point> pnums1(5); /* 创建vector容器，初始化容器大小为5, Point会默认初始化(即无参构造)*/
    /* 迭代器遍历 */
    vector<Point>::iterator itv = pnums1.begin();
    while(itv != pnums1.end()) {
        itv->print();
        itv++;
    }

    /* for 循环遍历 */
    for( int i = 0; i < pnums1.size(); ++i ) {
        pnums1[i].print();
    }

    /* 增强for循环 */
    for (Point& p : pnums1) {
        p.print();
    }
#endif

    /* vector<Point> vPoint1(5, 1); */
    /* for ( Point& p : vPoint1 ) { */
    /*     p.print(); */
    /* } */

    /* vector<Point> vPoint2{3, 4}; */
    /* for( Point& p : vPoint2 ){ */
    /*     p.print(); */
    /* } */

    /* vector<Point> vPoint3{Point(1, 2), Point(3, 4)}; */
    /* for(Point & p : vPoint3) { */
    /*     p.print(); */
    /* } */
    
    /* vector<Point> vPoint3{{1, 2}, {3, 4}}; */
    /* for( Point& p : vPoint3 ){ */
    /*     p.print(); */
    /* } */
}

void test02() {
    /* Point p = Point(); */
    /* p.print(); */
    vector<Point> vPoint;
    vPoint.reserve(10);
    cout << vPoint.size() << endl;
    cout << vPoint.capacity() << endl;
    vPoint.push_back(Point());
    vPoint[0].print();
    vPoint.push_back(Point(1, 2));
    vPoint.push_back(Point(2, 3));
    vPoint[1].print();
    vPoint[2].print();
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
