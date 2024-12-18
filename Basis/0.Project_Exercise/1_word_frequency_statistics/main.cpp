/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 14时00分43秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 文件读取
    > Content:
    >   1.vector遍历 12s, 优化后 7.2s
    >   2.map 0.45s
 ************************************************************************/

/* #include "01_vector_traversal_method.hh" */
/* #include "02_map_method.hh" */
#include "03_unorder_map_method.hh"
#include <chrono>
#include <iostream>

/* =============== test =============== */
void test0() {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    Dictionary dict;
    dict.read(FILENAME_IN);
    /* dict.print(); */
    dict.store(FILENAME_OUT);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    /* std::chrono::duration<int> duration = std::chrono::duration_cast<std::chrono::seconds>(end - start); */
    std::chrono::duration<double> duration = end - start;
    std::cout << "Program time is : " << duration.count() << " seconds" << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
