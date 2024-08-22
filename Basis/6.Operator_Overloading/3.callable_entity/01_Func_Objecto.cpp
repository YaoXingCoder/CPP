/*************************************************************************
    > File Name: 01_Func_Objecto.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 16时50分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 调用() 运算符重载
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class FunctionObject{
public:
    void operator()(){
        cout << "FunctionObject operator()()" << endl;
        ++ _count;
    }

    int operator()(int x, int y){
        cout <<"operator()(int,int)" << endl;
        ++ _count;
        return x + y;
    }

    double operator()(double x)  {
        return x;
    }

    int getCount() {
        return _count;
    }
private:
    int _count = 0; // 携带状态
};

/* 函数对象相较于普通函数 的优缺点
 * 1.可以携带状态
 * 原因: 普通函数如果需要统计, 需要设置全局变量
 * 但是全局变量能够被随意调用
 * 而 函数对象 就可以解决该问题 可以设置 一个成员变量 并设置为 私有的 防止状态被修改
 * 如需查看状态可以使用一个公共函数调用
 * 该状态对所有的函数对象都可以记录
 */

void test01() {
    FunctionObject fo;

    fo();
    /* fo.operator()() // 本质 */

    cout << fo(5,6) << endl;
    cout << fo.operator()(5,6) << endl; // 本质

    /* cout << "fo._count: " << fo._count << endl; // 记录这个函数对象被调用的次数 */
    cout << "fo._count: " << fo.getCount() << endl; // 记录这个函数对象被调用的次数

}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
