/*************************************************************************
    > File Name: test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 21时20分35秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Number {
public:
    int value;
    Number(int v) : value(v) {
        std::cout << "Number created: " << value << std::endl;
    }
    Number(const Number& other) : value(other.value) {
        std::cout << "Number copied: " << value << std::endl;
    }
    void print() const {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    std::vector<Number> vec = {Number(1), Number(2), Number(3)};

    /* std::function<void(Number)> fNum = std::bind(&Number::print, std::placeholders::_1); */
    /* std::for_each(vec.begin(), vec.end(), std::bind(&Number::print, std::placeholders::_1)); /1* 默认引用 *1/ */
    /* std::for_each(vec.begin(), vec.end(), fNum); /1* 显示指明后为拷贝 *1/ */
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print)); // 引用传递
    return 0;
}

