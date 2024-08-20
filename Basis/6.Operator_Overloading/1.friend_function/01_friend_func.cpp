/*************************************************************************
    > File Name: 01_friend_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 23时36分37秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 友元函数
    > Content:
 ************************************************************************/
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    : _ix(x)
    , _iy(y)
    {}
    
    /*
     * 将一个普通函数声明为Point类的友元函数
     * 那么这个友元函数中可以通过Point对象访问Point类私有的成员
     */
    friend
    double distance(const Point & p1,const Point & p2);
private:
    int _ix;
    int _iy;
};

class Line{
public:
    Line(int x1 = 1, int y1 = 1, int x2 = 2, int y2 = 2)
    : _p1(x1, y1)
    , _p2(x2, y2)
    {
        cout << "Line() 构造" << endl;
    }
    
    friend
    double distance(const Line & l1);
private:
    Point _p1;
    Point _p2;
};

double distance(const Point & p1,const Point & p2){
    return sqrt(pow(p1._ix - p2._ix, 2) + pow(p1._iy - p2._iy, 2));
}

double distance(const Line & l1) {
    return distance(l1._p1, l1._p2);
}

void test0(){
    Point pt1(0,0);
    Point pt2(3,4);
    cout << distance(pt1,pt2) << endl;
    
    Line l1(0, 0, 3, 4);
    cout << distance(l1) << endl;
}

int main(void){
    test0();
    return 0;
}
