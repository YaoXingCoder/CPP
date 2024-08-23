/*************************************************************************
    > File Name: 02_Func_Pointer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 17时24分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 函数指针 +  成员函数
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

typedef void(*FuncPtr)(int);
using FuncPtr2 = void(*)(int);

/* ==================== 成员函数 ====================== */
class FFF {
public:
    void print(int x){ cout << "FFF::print: " << x << endl; }
    void display(int x){ cout << "FFF::display: " << x << endl; }
    static void show(int x ) { cout << "FFF::show: " << x << endl; }
};
typedef void(FFF::*FFFunc)(int);
using FFFunc2 = void(FFF::*)(int);

/* ===================== 普通函数 ====================== */
void print(int x) {  cout << "print: " << x << endl; }
void display( int x ) { cout << "display: " << x << endl; }
void show() { cout << "show" << endl; }

/* ========================  测试 ========================= */

/* 成员函数 指针
 * 定义时要确定其指向的成员函数的 类、返回类型、参数信息(记得加上 &取地址符)
 * 注意：仅限定在FFF类中, p1 不能再指向其他同类型的普通函数
 * 如果非静态的函数, 则必须加上 &取地址符  */
void test01() {
    /* FFFunc p2 = FFF::display; /1* 错误的赋值方式 *1/ */
    void(FFF::*p1)(int) = &FFF::print; /* 完整的形式 */
    FFFunc p2 = &FFF::display; /* 使用别名 */

    FuncPtr p3 = FFF::show; /* 如果成员函数为静态成员函数, 可以使用普通类型别名声明定义 */
    p3(1); /* 直接调用 */

    /* 调用时需要完整形式使用 
     * 此时, 上边的 p1,p2,p3 都是指针, 指向的都是类中的函数, 所以调用时也要符合成员函数的形式
     * */
    FFF fff;
    (fff.*p1)(2); /* .* 为 成员指针运算符 */
    (FFF().*p2)(2); /* 也可以创建历史对象, 再调用成员函数指针 */
    p1 = &FFF::display; /* p1 重新指向 display */

    /* 对象方式调用 */
    FFF *fp = new FFF();
    fp->print(3);
    (fp->*p1)(3); /* 通过堆上对象方式调用成员函数指针 */
    /* ((new FFF())->*p1)(3); /1* 临时的堆上对象, 调用成员函数指针, 只是内存泄漏 *1/ */
    delete fp;

    fp = nullptr; 
    fp->print(4); /* 仍能调用, 空指针调用 */
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
