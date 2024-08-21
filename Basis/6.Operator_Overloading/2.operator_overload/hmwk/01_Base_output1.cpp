/*************************************************************************
    > File Name: 01_Base_output1.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 23时36分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 编写 Base 使其输出 1
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Base {
public:
    Base(int i = 0) : _i(i) {}

    friend int operator+(const Base& b1, const Base& b2);
private:
    int _i;
};

int operator+(const Base& b1, const Base& b2){
    return b2._i - b1._i;
}

void test01() {
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);

    cout << (x+y == j-i) << endl;
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
