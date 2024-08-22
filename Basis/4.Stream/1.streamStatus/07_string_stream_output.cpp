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
    oss << "num = " << num << ", num2 = " << num2 << endl;;
    cout << oss.str() << endl; /* str() 能够获取 oss 中 string对象的内容 不过只是临时副本, 不能够被指向 */

    /* ostringstream 的拼接 能够接收任意类型的数据
     * 通过 ostringstream 的 str() 函数 获取缓存区的字符串副本(右值, 不能够取地址)
     */
    oss << "123123" << " ";
    cout << oss.str() << endl;
    /* oss.str(""); /1* str("") 调用该函数 会将缓冲区内容全部置空 *1/ */
    oss << "abcabcd" << " ";
    cout << oss.str() << endl;

    string str1("hello");
    cout << &str1 << endl;
    cout << str1 << endl;
    /* append 会返回 *this, 可以取地址&, 且地址是调用append的对象的地址 */
    cout << &(str1.append(",wrold").append("~~~!")) << endl;
    /* 但是 append 不能够添加 其他类型的 数据, 须借助 to_string 的函数帮助 */
    /* str1.append(123); */
    str1.append(std::to_string(123));
    cout << str1 << endl;

    /* */
    string str2("test + ");
    /* +号 不会修改str2对象中的值, 且是右值(不能够取地址) */
    cout << str2 + ", hello" + "wrold" << endl;
    cout << str2 << endl;
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
