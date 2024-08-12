/*************************************************************************
    > File Name: hmwk_03.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 20时34分32秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
    int arr[5] = { 1,2,3,4,5 };
    int* parr = (int*)(&arr + 1);
    printf("%d, %d\n", *(arr + 1), *(parr - 1));
    return 0;
}
