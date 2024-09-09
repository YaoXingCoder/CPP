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
#include <iterator>
#include <algorithm>
#include <functional>

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


/* =============== test1 =============== */
void test1() {
    std::vector<int> number { 1,3,5,4,9,7,6,2,10 };
    std::copy(number.begin(), number.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::greater<int> gt;
    std::less<int> lss;

    /* std::vector<int>::iterator rm_it = std::remove_if(number.begin(), number.end(), std::bind2nd(gt, 4)); */
    std::vector<int>::iterator rm_it = std::remove_if(number.begin(), number.end(), std::bind1st(lss, 4));
    number.erase(rm_it, number.end());
    std::for_each(number.begin(), number.end(), [](int value){
                  std::cout << value << " ";
                  });
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test1();
    return 0;
}
