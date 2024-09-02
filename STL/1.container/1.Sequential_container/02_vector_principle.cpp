/*************************************************************************
    > File Name: 02_vector_principle.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 17时01分05秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 底层原理
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

/* =============== test =============== */
void test0() {
    /* 取第一个元素的首地址 */
    vector<int> v1 = { 1,2,3,4,5,6,7,8 };
    cout << &v1 << endl; // error, 取的是 v1 这个容器对象的栈上地址, 并不是首个元素的地址
    cout << &v1[0] << endl;
    cout << &*v1.begin() << endl;
    int *pdata = v1.data();
    cout << pdata << endl;

}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
