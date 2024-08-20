/*************************************************************************
    > File Name: 07_string_stream_output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 14时24分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 字符串流 输出
    > Content:
    >   1.将各种类型的数据转换成字符串类型
 ************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

void test01() {
    int num = 123, num2 = 456;
    ostringstream oss;
    oss << "num = " << num << ", num2 = " << num2 << endl;
    ostringstream iss;
    cout << oss.str() << endl; /* str() 能够获取 oss 中 string对象的内容 不过只是临时副本, 不能够被指向 */
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
