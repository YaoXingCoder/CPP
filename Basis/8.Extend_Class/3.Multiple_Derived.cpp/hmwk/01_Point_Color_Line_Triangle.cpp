/*************************************************************************
    > File Name: 01_Point_Color_Line_Triangle.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 20时24分13秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
    >   1.定义一个点Point类，数据成员是横纵坐标（float）；
    >   2.定义一个颜色类Color数据成员只有颜色（string）；
    >   3.一个直线类Line，数据成员是两个Point对象，表示起点和终点（即Point两个对象为Line的内嵌对象）；
    >   4.一个三角形类Triangle，继承自Line和Color，数据成员有三角形的高height（float），
    >       三角形理解成以基类Color为颜色，以基类直线为底，以height为高的直角三角形，(即直线和高分别为两条直角边)
    >   5.请实现相关函数，计算三角形的颜色、周长和面积并给出相关输出
 ************************************************************************/

#include <math.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define TRIANGLE_DIVISOR 2.0

/* ========================= Point =========================== */
class Point{
public:
    Point(float x, float y) : _x(x), _y(y) {
        cout << "Point(float, float) 有参" << endl;
    }

    ~Point() {
        cout << "~Point() 析构" << endl;
    }

    friend class Line;
private:
    float _x;
    float _y;
};

/* ========================= Color =========================== */
class Color{
public:
    Color(const char* pstr) : _color(pstr) {
        cout << "Color(const char*) 有参" << endl;
    }
    Color(const string& rhs) : _color(rhs) {
        cout << "Color(const string&) 有参" << endl;
    }

    ~Color() {
        cout << "~Color() 析构" << endl;
    }

protected:
    const string& getColor() {
        return _color;
    }

    const char* getColor_C() {
        return _color.c_str();
    }
private:
    string _color;
};

/* ========================= Line =========================== */
class Line {
public:
    Line(float x_f1, float y_f1, float x_f2, float y_f2) : _start(x_f1, y_f1), _end(x_f2, y_f2) {
        cout << "Line(float, float, float, float) 有参" << endl;
    }
    Line(const Point& p1, const Point& p2) : _start(p1), _end(p2) {
        cout << "Line(const Point&, const Point&) 有参" << endl;
    }

    ~Line() {
        cout << "~Line() 析构" << endl;
    }
protected:
    /* 计算出直线长度 */
    float distance_p2p () {
        return sqrt(pow(_end._x - _start._x, 2) + pow(_end._y - _start._y, 2));
    }
private:
    Point _start;
    Point _end;
};

/* ========================= Triangle =========================== */
class Triangle : public Line, public Color{
public:
    Triangle(Line& line, Color& color, float height) 
    : Line(line)
    , Color(color)
    , _height(height)
    {
        cout << "Triangle(Line&, Color&, float) 构造" << endl;
    }

    ~Triangle() {
        cout << "~Triangle() 析构" << endl;
    }
public:
    /* 周长 */
    float circumference() {
        return len_hypotenuse() + distance_p2p()  + _height;
    }

    /* 面积 */
    float area() {
        return distance_p2p() * _height / TRIANGLE_DIVISOR;
    }

    /* 颜色 */
    const string& get_color() {
        return getColor();
    }

    const char* get_color_c() {
        return getColor_C();
    }

private:
    /* 斜边长 */
    float len_hypotenuse() {
        return sqrt(pow(_height, 2) + pow(distance_p2p(), 2));
    }

private:
    float _height;
};


/* =============== test =============== */
void test0() {
    cout << endl << "====== test0 ======" << endl;
    Line l1(0, 0, 0, 3);
    Color c1("red");
    Triangle t1 (l1, c1, 4);

    cout << endl << "====== start ======" << endl;

    cout << "circumference : " << t1.circumference() << endl;
    cout << "area : " << t1.area() << endl;
    cout << "color : " << t1.get_color() << endl;

    cout << endl << "====== end ======" << endl;

}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
