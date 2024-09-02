/*************************************************************************
    > File Name: 05_multiplication_table.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 22时08分37秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 九九乘法表
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>

/* =============== test =============== */
void test0() {
    std::vector<std::vector<int>> vc_vc;

    for(int i = 1; i <= 9; ++i ) {
        std::vector<int> vc_i(i);
        for ( int j = 1; j <= i; ++j) { vc_i[j - 1] = i * j; }
        vc_vc.push_back(vc_i);
    }

    /* 输出 */
    int i = 1;
    for(std::vector<int> & vc_i : vc_vc) {
        int j = 1;
        for( int & val : vc_i ) {
            std::cout << i << " * " << j << " = " << val << "  ";
            ++j;
        }
        ++i;
        std::cout << std::endl;
    }

}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
