/*************************************************************************
    > File Name: 08_compile_polymorphism.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 17时50分15秒
    > Mail: JiaZiChunQiu@163.com
    > Title: bind + function 实现 编译时多态
    > Content:
 ************************************************************************/

#include <iostream>
#include <functional>
#include <cmath>

class Figure {
public:
    using DisplayCallBack = std::function<void()>;
    using AreaCallBack = std::function<double()>;
public:
    /* 注册回调函数 */
    void setDisplayCB(DisplayCallBack && displayCB) {
        _displayCB = displayCB;
    }
    void setAreaCallBack(AreaCallBack && areaCB) {
        _areaCB = areaCB;
    }

    /* 执行 */
    void handleDisplayCB() const {
        if ( _displayCB ) { _displayCB(); }
    }
    double handleAreaCB() const {
        if ( _areaCB ) { return _areaCB(); }
        else return 0.0;
    }
private:
    DisplayCallBack _displayCB;
    AreaCallBack _areaCB;
};

void call(const Figure & fig) {
    fig.handleDisplayCB();
    std::cout << "area is : " << fig.handleAreaCB() << std::endl;
}

/* 矩形 */
class Rectangle {
    public:
        Rectangle(double length, double width) : _length(length), _width(width) {}
        void display() const { std::cout << "Rectangle" << std::endl; }
        double area() const { return _length * _width; }
    private:
        double _length;
        double _width;
};

/* 圆 */
class Circle {
public:
    Circle(double radis) :_radis(radis) {}
    void show() const { std::cout << "Circle" << std::endl; }
    double area() const { return PI * _radis * _radis; }
private:
    static constexpr double PI = 3.14;
    double _radis;
};

/* 三角形 */
class Traingle {
public:
    Traingle(double a, double b, double c) : _a(a), _b(b), _c(c) {}
    void print() const { std::cout << "Traingle" << std::endl; }
    double area() const { return std::sqrt(((_a+_b+_c) / 2) * (_b/2+_c/2-_a/2) * (_a/2+_b/2-_c/2) * (_a/2+_c/2-_b/2) ); }
private:
    double _a;
    double _b;
    double _c;
};

/* =============== test =============== */
void test0() {
    Rectangle rectangle(10, 20);
    Circle circle(10);
    Traingle traingle(3, 4, 5);

    Figure figure1;
    figure1.setDisplayCB(std::bind(&Rectangle::display, rectangle));
    figure1.setAreaCallBack(std::bind(&Rectangle::area, rectangle));
    call(figure1);

    Figure figure2;
    figure2.setDisplayCB(std::bind(&Circle::show, circle));
    figure2.setAreaCallBack(std::bind(&Circle::area, circle));
    call(figure2);

    Figure figure3;
    figure3.setDisplayCB(std::bind(&Traingle::print, traingle));
    figure3.setAreaCallBack(std::bind(&Traingle::area, traingle));
    call(figure3);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
