/*************************************************************************
    > File Name: 01_derived_class_basis.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月25日 星期日 21时10分30秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 派生类
    > Content:
    >   1.基本使用
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class Point {
public:
    Point(int x,int y) : _ix(x) , _iy(y)
    { cout << "Point(int,int) 构造" << endl; }

    ~Point(){ cout << "~Point() 析构" << endl; }

    void print() const {
        cout << "( " << _ix << ", " << _iy << " )" << endl;
    }
/* public: */
protected:
    int _ix;
private:
    int _iy;
};

class PointXYZ : public Point {
public:
    PointXYZ(int x, int y, int z) : Point(x, y), _iz(z) {
        cout << "PointXYZ 构造" << endl;
    }

    ~PointXYZ() { cout << "~PointXYZ() 析构"  << endl; }

    void display() const {
        print();
        cout << _iz << endl;
    }
private:
    int _iz;
};

/* =============== test =============== */
void test0() {
    PointXYZ pt_xyz1(1, 2, 3);
    Point pt1(4, 5);

    /* cout << pt1._ix << endl; /1* 对象不可访问 protected *1/ */
    /* cout << pt_xyz1._ix << endl;  /1* 派生类也不能访问 protected *1/ */
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
