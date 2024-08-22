/*************************************************************************
    > File Name: 05_Type_conversion_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 20时32分53秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 类型转换函数
    > Content:
    >   1.类型转换函数 (优先级次之)
    >   2.特殊赋值函数 (三个存在时 特殊赋值优先级最高)
    >   3.隐式转换(特殊构造函数 + 赋值函数) (少用)
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Point{
public:
    Point(int x = 1, int y = 2)
        : _ix(x)
        , _iy(y)
    {  }

    operator int(){
        cout << "operator int()" << endl;
        return _ix + _iy;
    }

    void print() {
        cout << "( " << _ix << ", " << _iy << " )" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test01() {
    /* 隐式转换 */
    Point pt1 = 1;
    pt1.print();

    /* Point 对象转换为 int类型的变量
     * 本质上是 Point 对象产生一个临时的int型变量
     * 赋值给 a 
     */
    int a = pt1;
    /* int b = pt1.operator int(); /1* 本质 *1/ */
    cout << a << endl;
    pt1.print();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
