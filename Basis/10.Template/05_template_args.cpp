/*************************************************************************
    > File Name: 03_template_args.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 15时07分41秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 模板参数 参数类型
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

/* 模板函数的函数中的参数可以时任意类型 */
template <class T >
T multiply(T x, T y, int kBase = 10) {
    cout << "template1" << endl;
    return x * y * kBase;
}

/* 函数模板中的非类型参数只能是整型 */
template <class T = int, int kBase = 10>
T multiply(T x, T y){
    cout << "template2" << endl;
	return x * y * kBase;
}

void test0(){
    int i1 = 3, i2 = 4;
    // 此时想要进行隐式实例化就不允许了，因为 kBase无法推导
    /* std::cout << multiply(i1, i2) << std::endl;  // error */
    cout << multiply(1.4, 1.4, 10) << endl; /* ok, kBase自动转换为double */

    cout << endl; 
    /* Kbase 添加默认值后可以, T推导出double, kBase使用默认值 
     * 如果连个都添加默认值, 则该调用会产生二义性 */
    /* cout << multiply(1.4, 1.4) << endl; // 当template2的kBase没指定默认时, 无法推导 *1/ */
    std::cout << multiply<int, 10>(i1, i2) << std::endl;   // 显示指定可以成功
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
