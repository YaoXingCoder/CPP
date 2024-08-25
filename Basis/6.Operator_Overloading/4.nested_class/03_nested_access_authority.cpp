/*************************************************************************
    > File Name: 03_nested_access_authority.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月24日 星期六 09时15分17秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 嵌套类的访问权限
    > Content:
    >   1.
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Line {
public:
    /* 2.1  私有成员访问
     *      外部类 -> 内部类 私有成员 
     *      对象 直接访问
     *      静态成员 直接访问 */
    void func2_1(){
        cout << _pt1._ix << ", " << _pt1._iy << endl;
        cout << _pt2._ix << ", " << _pt2._iy << endl;
    }
    /* 2.1 静态需要通过 声明友元才可 */
    /* void func2_1_1() { */
    /*     cout << _pt1._iz << endl; */
    /*     cout << Point::_iz << endl; */
    /* } */
private:
    class Point {
    public:
        Point(int x,int y): _ix(x) , _iy(y)
        { cout << "Point(int,int)" << endl; }
        ~Point(){ cout << "~Point()" << endl; }

        void print() const{ cout << "( " << _ix << ", " << _iy << " )"; }

        /* 1.1  公有成员访问
         *      内部类 访问 外部类 的 公有成员
         *      可以通过外部类对象 直接访问 */
        void func1_1(const Line& rhs) { rhs.print(); }

        /* 2.1  私有成员访问 
         *      外部类 -> 内部类 私有成员
         *      通过在被访问类中设置友元*/
        friend void Line::func2_1();
        /* friend void Line::func2_1_1(); */

        /* 2.2  私有成员访问
         *      内部类 -> 外部类 的 私有成员
         *      通过对象 直接访问
         *      */
        void func2_2(const Line& rhs) { 
            rhs._pt1.print(); 
            Line::_pt3.print();
        }
    private:
        int _ix;
        int _iy;
        static int _iz;
    };
public:
    Line(int x1,int y1,int x2,int y2) : _pt1(x1, y1) , _pt2(x2, y2)
    { cout << "Line(int*4)" << endl; }
    ~Line(){ cout << "~Line()" << endl; }


    /* 1.2  公有成员访问
     *      外部类 访问 内部类 公有成员
     *      可以通过内部类对象 直接访问*/
    void print() const{
        _pt1.print();
        cout << "----->";
        _pt2.print();
        cout << endl;
    }

    /* static void func3(){ cout << "public static func4()" << endl; } */
private:
    /* static void func4(){ cout << "private static func4()" << endl; } */
    Point _pt1;
    Point _pt2;
    static Point _pt3;
};
int Line::Point::_iz = 10;
Line::Point Line::_pt3 = Point(1, 2);

    /* 2.1  私有成员访问
     *      外部类 -> 内部类 私有成员*/
    /* void Line::func2() { */
    /*     /1* _pt1._ix; /2* 不能直接访问私有 *2/ *1/ */
    /*     cout << _pt1._ix << ", " << _pt1._iy << endl; */
    /*     cout << _pt2._ix << ", " << _pt2._iy << endl; */
    /* } */

/* ================ test ================= */
void test0() {
    Line l1(1, 2, 3, 4);
    cout << endl  << "====== start ======" << endl;
    l1.print();
    l1.func2_1();
    /* Line::func3(); */
    cout << endl  << "====== end ======" << endl;
}

int main (int argc, char* argv[]) {
    test0();
    return 0;
}
