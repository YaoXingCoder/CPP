/*************************************************************************
    > File Name: 02_remove_if.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月08日 星期日 20时24分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: remove_if 
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

/* =============== test =============== */
void test0() {
    std::vector<int> vec_i{1,5,3,2,6,9,8,4};
    std::for_each(vec_i.begin(), vec_i.end(), [](int value) {
                  std::cout << value << " ";
                  });
    std::cout << std::endl;
    std::for_each(vec_i.begin()
                  , remove_if(vec_i.begin(), vec_i.end()
                                           , [](int value)->bool{ 
                                           return value > 4;
                                           })
                  , [](int value) { 
                  std::cout << value << " ";
                  });
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
