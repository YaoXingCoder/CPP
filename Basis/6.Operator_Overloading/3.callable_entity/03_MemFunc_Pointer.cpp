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
    void print(int x){
        cout << "FFF::print:" << x << endl;
    }

    void display(int x){
        cout << "FFF::display:" << x << endl;
    }
};
/* 报错 typedef 不能被限定 */
/* typedef void(*FFF::Function)(int); */

/* ===================== 普通函数 ====================== */
void print(int x) { 
    cout << "print: " << x << endl;
}

void display( int x ) {
    cout << "display: " << x << endl;
}

void show() {
    cout << "show" << endl;
}

typedef void(FFF::*FFFunc)(int);

/* ========================  测试 ========================= */

void test01() {
    /* 定义函数指针 要确定其 指向的函数的
     * 返回类型 和 参数信息 
     * */
    void (*p1)(int) = print;
    p1(3);

    p1 = display;
    p1(4);

    FuncPtr p2 = print;
    p2(5);

    FuncPtr2 p3 = display;
    p3(6);

    /* p1 = show; /1* 报错 因为:show的类型与p1声明不同 */
}

void test02() {
    /* 成员函数 指针 
     * 注意：仅限定在FFF类中, p1不能再指向其他的print
     * */
    void(FFF::*p1)(int) = &FFF::print;
    FFFunc p2 = &FFF::display;
    /* 调用时也需要完整形式调用 */
    FFF fff;
    (fff.*p1)(1); /* .* 为 成员指针运算符 */

    p1 = &FFF::display;

    /* 对象方式调用 */
    FFF *fp = new FFF();
    fp->print(2);
    delete fp;
    fp = nullptr; 
    fp->print(2); /* 仍能调用, 空指针调用 */
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
