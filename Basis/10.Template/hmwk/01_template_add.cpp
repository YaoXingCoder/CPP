/*************************************************************************
    > File Name: 01_template_add.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 23时47分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 使用函数模板实现两个整数类型数据相加、两个double型数据相加、两个存放int型元素的set融合
    > Content:
 ************************************************************************/

#include <iostream>
#include <set>

/* template<class T> */
/* T add(T t1, T t2) { */
/*     return t1 + t2; */
/* } */

/* template<> */
/* std::set<int>* add<std::set<int>*>(std::set<int> *s1, std::set<int> *s2){ */
/*     std::set<int>* s3 = new std::set<int>(); */
/*     s3->insert(s1->begin(), s1->end()); */
/*     s3->insert(s2->begin(), s2->end()); */
/*     return s3; */
/* } */

template<typename T>
T & add(T & t1, const T & t2){
    t1 += t2;
    return t1;
}

template<>
std::set<int>& add<std::set<int>>(std::set<int>& lhs, const std::set<int>& rhs) {
    lhs.insert(rhs.begin(), rhs.end());
    return lhs;
}

/* =============== test =============== */
void test0() {
    int i1 = 1, i2 = 2;
    double d1 = 1.1, d2 = 2.2;
    /* std::cout << add(1, 2) << std::endl; */
    /* std::cout << add(1.1, 2.2) << std::endl; */
    std::cout << add (i1, i2) << std::endl;

    std::set<int> si_1 = { 1, 2, 3 };
    std::set<int> si_2 = { 4, 5, 6 };
    add(si_1, si_2);
    /* std::set<int> s3 = add(si_1, si_2); */
    for(int i : si_1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
