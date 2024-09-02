/*************************************************************************
    > File Name: 06_abuse.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 11时12分15秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 智能指针可能出现问题
    > Content:
 ************************************************************************/

#include <iostream>
#include <memory>

class Point : public std::enable_shared_from_this<Point>{
public:
    Point(int x,int y) : _ix(x) , _iy(y) {}

    void print() const{
        std::cout << "(" << _ix << "," << _iy << ")" << std::endl;
    }

    /* Point * addPoint(Point * pt){ */
    /*     _ix += pt->_ix; */
    /*     _iy += pt->_iy; */
    /*     /1* return this; *1/ */
    /* } */

    std::shared_ptr<Point> addPoint(Point * pt){
        _ix += pt->_ix;
        _iy += pt->_iy;

        //临时的shared_ptr对象与sp使用了同一个裸指针
        return std::shared_ptr<Point>(this);

        //创建了新的Point对象，这样可以
        /* return std::shared_ptr<Point>(new Point(_ix + 1,_iy + 1)); */

        /* 利用辅助类封装好的函数, 返回一个共享*this所有权的shared_ptr */
        /* return shared_from_this(); */
    }

private:
    int _ix;
    int _iy;
};

/* =============== test =============== */
void test0() {
    //使用不同的智能指针托管同一片堆空间
    std::shared_ptr<Point> sp(new Point(1,2));
    std::shared_ptr<Point> sp2(new Point(1,2));
    /* sp.reset(sp2.get()); */
    std::cout << "test00" << std::endl;
    /* std::shared_ptr<Point> sp3(sp2->addPoint(sp.get())); */
    sp2->addPoint(sp.get());
    sp->print();
    delete sp.get();
    std::cout << "test01" << std::endl;
    
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
