/*************************************************************************
    > File Name: 07_mem_fn.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 20时25分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title: mem_fn 从成员指针创建出函数对象
    > Content:
    >   1.成员函数的绑定
 ************************************************************************/

#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

class Number {
public:
    Number(std::size_t data = 0) : _data(data) {}
    ~Number(){}

    void print() const { std::cout << _data << " "; }

    bool isEven() const { return _data % 2 == 0; }
    bool isPrime() const {
        if( _data <= 3 ){ return _data > 1; }

        if( _data % 6 != 1 && _data % 6 != 5){ return false; }

        for(int i= 5; i<= (int)std::sqrt(_data); i += 6){
            if( _data % i == 0 || _data % ( i + 2) == 0 ){ return false; }
        }
        return true;  
    }
private:
    std::size_t _data;
};

/* =============== test =============== */
/* 成员函数的绑定 */
void test0() {
    /* 放入元素 */
    std::vector<Number> vec;
    for(std::size_t idx = 1; idx <= 30; ++idx) {
        vec.push_back(Number(idx));
    }

    /* 遍历输出所有元素 */
    /* std::function<void(Number)> fNum = std::bind(&Number::print, std::placeholders::_1); // bind 返回的函数类型 function<void(Number)>;*/
    /* std::function<void(Number &)> fNum = std::bind(&Number::print, std::placeholders::_1); */
    /* std::for_each(vec.begin(), vec.end(), fNum); // for_each 传入bind中的类型为迭代器解引用： *(vec.begin()) = Number对象 */ 

    /* std::cout << std::endl; */
    /* std::for_each(vec.begin(), vec.end(), std::bind(&Number::print, std::placeholders::_1)); // for_each 传入bind中的类型为迭代器解引用： *(vec.begin()) = Number对象 */ 

    /* 方式2 mem_fn */
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
    std::cout << std::endl;

    /* 删除偶数 */
    vec.erase(std::remove_if(vec.begin(), vec.end(), std::mem_fn(&Number::isEven)), vec.end());
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
    std::cout << std::endl;

    /* 删除质数 */
    vec.erase(std::remove_if(vec.begin(), vec.end(), std::mem_fn(&Number::isPrime)), vec.end());
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
    std::cout << std::endl;

    /* 删除不是质数的 */
    /* std::not_fn() */
    vec.erase(std::remove_if(vec.begin(), vec.end(), std::not_fn(std::mem_fn(&Number::isPrime))), vec.end());
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
    std::cout << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
