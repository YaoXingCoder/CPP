/*************************************************************************
    > File Name: template_overload.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 11时02分48秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 模板重载
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

template <class T>
T add(T t1,T t2) { 
    std::cout << "template 1" << std::endl;
    return t1 + t2; 
}

/* 与上边的模板函数构成重载 */
template <class T1, class T2>
T1 add(T1 t1, T2 t2) {
    std::cout << "template 2" << std::endl;
    return t1 + t2;
}

/* add 的参数顺序不同, 同样构成模板函数重载 */
template <class T1, class T2>
T1 add(T2 t2, T1 t1) {
    cout << "template 3" << endl;
    return t1 + t2;
}
/* add 的返回值不同, 构成模板函数重载, 但对于一些调用与 tempate2 产生二义性, 所以少用 */
/* template <class T2, class T1> */
/* T1 add(T2 t2, T1 t1){ */
/*     cout << "template 4" << endl; */
/*     return t1 + t2; */
/* } */

/* =============== test =============== 
 * 模板的 隐式 | 显示 实例化 */

void test0() {
    short s1 = 1, s2 = 2;
    int i1 = 3, i2 = 4;
    long l1 = 5, l2 = 6;
    double d1 = 1.1, d2 = 2.2;

    /* 自动进行隐式实例化 */
    cout << "add(s1, s2): " << add(s1, s2) << endl;
    cout << "add(i1, i2): " << add(i1, i2) << endl;
    cout << "add(l1, l2): " << add(l1, l2) << endl;
    cout << "add(d1, d2): " << add(d1, d2) << endl; 
    cout << endl;
    /* 指定的方式: 显示的实例化 */
    /* cout << "add<int>(d1, d2): " << add<int>(d1, d2) << endl; */ 
}
/* =============== test =============== */
void test1() {
    int i1 = 2;
    double d1 = 3.7;

    /* 1.1 如果只有 template1 则会报错 , 接受类型不是同一个类型, */
    /* 2.1 可以定义另一个模板 */
    /* 3.1 加入template3 后产生报错, 二义性问题 */
    /* std::cout << add(i1, d1) << std::endl; // 2.1 return 时返回值为 i1 的类型, 会损失精度 */
    /* std::cout << add(d1, i1) << std::endl; // 2.1 return 时返回值为 d1 的类型, 不会损失精度 */
    /* 1.2 可以显示指定类型 */
    /* 2.2 因为只指定第一个模板参数, i1 是 int 不需要转换
     *      d1 如果走 template1 则需要进行隐式转换, 走 template2 则不需要隐式转换
     *      虽然看上边有优先选择 2, 不过最后输出时, 仍是按模板参数1的类型, 但编译器不会考虑那么多, 只看当前所需要转换次数最少的 */
    cout << add<int>(i1, d1) << endl;
    /* 2.2 同样指定第一个模板参数, 但 i1 是 int 所以不管 template1|2 都需要进行隐式转换
     *      d1 因为 template1 已经能够确定 返回值同样是 double, 且不不需要转换, 所以编译器会优先选择 template1 */
    /* 3.1 有函数模板3, 则选择3, 则 double 指定的是add 的第二个参数
     *      此时选择 template3, i1 不需要转换, 返回值会转换成 double, 但有限选择不需要转换的模板 */
    cout << add<double>(i1, d1) << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
