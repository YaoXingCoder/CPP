/*************************************************************************
    > File Name: 01_for_each.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月07日 星期六 10时52分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: for_each 使用
    > Content:
 ************************************************************************/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

void func(int &value) {
    ++value;
    std::cout << value << " ";
}

/* =============== test =============== */
void test0() {
    std::vector<int> vec = {1, 3, 7, 9, 6, 4};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    /* std::for_each(vec.begin(), vec.end(), func); */
        /* lambda 表达式
    *  [] 捕获列表
    *  () 函数的参数列表
    *  {} 函数体
    *  (){} 中间为 -> 返回类型
    */
    std::for_each(vec.begin(), vec.end(), [](int &value)->void{
                  ++value;
                  std::cout << value << " ";
                  });
    std::cout << std::endl;

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
