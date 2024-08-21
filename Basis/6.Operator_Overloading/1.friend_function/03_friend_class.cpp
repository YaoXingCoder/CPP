/*************************************************************************
    > File Name: 01_friend_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 23时36分37秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 友元类
    > Content:
 ************************************************************************/
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

class Point; /* 前向声明 Point 是一个不完整类型 */

class Line{
public:
    double distance(const Point& p1, const Point& p2);

    void setX(Point & rhs, int x);
};

/* 在Line 和 Point 对Point的成员进行访问
 * 尝试访问一个不完整类型的成员时。
 * 不完整类型是指一个声明了但没有定义的类型，
 * 也就是说编译器知道类型的存在，
 * 但不知道它的内部结构，因此不能访问它的成员。
 * */
/* double distance(const Point & p1,const Point & p2){ */
/*     return sqrt(pow(p1._ix - p2._ix, 2) + pow(p1._iy - p2._iy, 2)); */
/* } */

class Point{
public:
    Point(int x, int y)
    : _ix(x)
    , _iy(y)
    {}
    
    void print(){
        cout << "( " << _ix << ", " << _iy << " )" << endl;
    }

    /*
     * 将一个普通函数声明为Point类的友元函数
     * 那么这个友元函数中可以通过Point对象访问Point类私有的成员
     */
    /* friend */
    /* double Line::distance(const Point & p1,const Point & p2); */
    /* friend */
    /* void Line::setX(Point& rhs, int x); */
    
    /* 友元类声明 */
    friend class Line;
private:
    int _ix;
    int _iy;
};

double Line::distance(const Point & p1,const Point & p2){
    return sqrt(pow(p1._ix - p2._ix, 2) + pow(p1._iy - p2._iy, 2));
}

void Line::setX(Point & rhs, int x) {
    rhs._ix = x;
}

/* ============================================================== */

void test0(){
    Point pt1(0,0);
    Point pt2(3,4);
    Line li;
    Line li1 = Line();
    cout << li.distance(pt1,pt2) << endl;
    cout << Line().distance(pt1, pt2) << endl;
}

void test1() {
    Point pt1(0,0);
    Point pt2(3,4);
    pt1.print();
    
    Line().setX(pt1, 4);

    pt1.print();
}

int main(void){
    /* test0(); */
    test1();
    return 0;
}
