/*************************************************************************
    > File Name: 06_erase_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 23时48分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 删除元素
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/* =============== test =============== */
void test0() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 打印初始状态
    std::cout << "Initial vector: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 获取指向第一个元素的迭代器
    std::vector<int>::iterator it = vec.begin();
    std::vector<int>::iterator it2 = vec.begin();
    it2+=2;
    std::cout << "Before erase, first element: " << *it << std::endl;
    std::cout << "Before erase, second element: " << *it2 << std::endl;

    // 擦除第一个元素
    vec.erase(it);

    // 尝试访问被擦除元素
    // 这会导致未定义行为，因为it现在是悬挂迭代器
    std::cout << "After erase, first element: " << *it << std::endl;
    std::cout << "After erase, second element: " << *it2 << std::endl;
    std::cout << "After erase, fourth element: " << vec[3] << std::endl;
    std::cout << "After erase, fifth element: " << vec[4] << std::endl;

    // 打印擦除后的状态
    std::cout << "After erase: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
