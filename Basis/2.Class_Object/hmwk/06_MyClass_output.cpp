/*************************************************************************
    > File Name: 06_MyClass_output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 10时40分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title: MyClass 输出
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class MyClass
{
public:
    MyClass(int i = 0)
    {
        cout << i;
    }
    MyClass(const MyClass &x)
    {
        cout << 2;
    }
    MyClass &operator=(const MyClass &x)
    {
        cout << 3;
        return *this;
    }
    ~MyClass()
    {
        cout << 4;
    }
};

/* 测试 */
void test01() {
    MyClass obj1(1), obj2(2);
    MyClass obj3 = obj1;
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
