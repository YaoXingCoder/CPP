/*************************************************************************
    > File Name: const_02.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 15时57分10秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

#define MAX "hello"

int main (int argc, char* argv[]) {
    
    cout << MAX + 1 << endl;

    const char* str = "hello";
    cout << str + 1 << endl;

    int arr[5] = { 1,2,3,4,5 };
    int (*p)[5] = &arr;

    return 0;
}
