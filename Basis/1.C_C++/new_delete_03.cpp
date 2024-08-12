/*************************************************************************
    > File Name: new_delete_03.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 16时14分27秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 申请堆空间
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {

    int* p1 = new int();
    cout << *p1 << endl;

    int* p2 = new int(1); /* 初始化该类型的默认值 */
    cout << *p2 << endl;
    return 0;
}
