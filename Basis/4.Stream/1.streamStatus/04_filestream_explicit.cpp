/*************************************************************************
    > File Name: 04_filestream_explicit.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 16时33分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 文件流 explicit
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Point{
public:
    /* explicit//禁止隐式转换 */
    Point(int x = 0, int y = 0)
    : _ix(x)
    , _iy(y)
    {
        cout << "Point(int,int) 有参" << endl;
    }

    Point(const Point & rhs)
    : _ix(rhs._ix)
    , _iy(rhs._iy)
    {
        cout << "Point(const Point &) 拷贝" << endl;
    }

    ~Point(){
        cout << "~Point() 析构" << endl;
    }

    void print() const{
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test0(){
    /* Point pt(1,2); */
    //缺省调用
    /* Point pt2(3); */
    /* Point pt3; */

    //隐式转换
    //编译器会尝试使用一个int型参数初始化一个匿名的Point对象
    //再通过拷贝构造初始化pt4
    /* Point pt4 = Point(3); */
    Point pt4 = 3;
    pt4.print();
}

int main(void){
    test0();
    return 0;
}

