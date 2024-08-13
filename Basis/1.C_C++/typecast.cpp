/*************************************************************************
    > File Name: typecast.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月13日 星期二 11时47分31秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 强制类型转换
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
    /* const char* pstr = "hello"; */
    /* C语言转换 */
    /* char* p1 = (char*)pstr; */
    /* p1[1] = 'i'; /1* 报错并不安全 *1/ */ 
    /* C++ 转换 */
    /* char* p1 = static_cast<char*>(pstr); /1* 直接爆红 *1/ */
    /* char* p2 = const_cast<char*>(pstr); /1* 可以转换 *1/ */
    /* p2[1] = 'i'; /1* 报段错误 *1/ */

/* =================================================================== */

    /* int -> const int* -> int* */
    /* const int n0 = 123; */
    /* const int* pn0 = &n0; */

    /* C语言方法 */
    /* int* pn01 = (int*)pn0; */
    /* *pn01 = 100; /1* 输出 100 *1/ */
    /* cout << *pn01 << endl; */

    /* C++ 方法 */
    /* int* pn02 = const_cast<int*>(pn0); */
    /* *pn02 = 200; /1* 输出 200 *1/ */
    /* cout << *pn02 << endl; */

    /* cout << n0 << endl; /1* 仍为 123 *1/ */

/* =================================================================== */

    int n1 = 100;
    float f1 = 10.123f;

    int* pn1 = &n1;
    float* pf1 = &f1;

    cout << *pn1 << endl;
    cout << *pf1 << endl;

    /* int* pf2 = static_cast<int*>(pf1); */
    /* int* pf2 = const_cast<int*>(pf1); */
    int* pf2 = reinterpret_cast<int*>(pf1); /* 万能转换能够完成不同类型指针之间的转换 */
    cout << *pf2 << endl; /* 因为整型和浮点型之间的存储规则所以强转后输出差异较大 */

    cout << 5/2 << endl; /* 输出 2 */


    
    return 0;
}
