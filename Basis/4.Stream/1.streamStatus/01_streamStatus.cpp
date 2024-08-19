/*************************************************************************
    > File Name: 01_streamStatus.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 11时48分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 输出流错误
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;

/* const 不再更改cin中缓冲区内容 
 * & 是一个cin，cin 为全局变量
 * */
void checkStatus(const istream& is) {
    cout << "cin is goodbit : "  << cin.good() << endl;
    cout << "cin is badbit : "  << cin.bad() << endl;
    cout << "cin is failbit : "  << cin.fail() << endl;
    cout << "cin is eofbit : "  << cin.eof() << endl;
}

/* 测试 */
void test01() {
    checkStatus(cin);
    cout << endl;

    int num = 0;
    cin >> num;
    cout << "num is : " << num << endl;
    checkStatus(cin);

    if( !cin.good() ) { 
        cout << "cin.clear()" << endl;
        cin.clear();  /* 恢复流的状态 */
        /* cin.ignore(10); /1* 清空10个缓冲区字符 *1/ */
        cin.ignore(10, '\n'); /* 清空10个缓冲区字符 */
    }
    checkStatus(cin);
    cout << endl;

    num = 5;
    cin >> num;
    cout << "num is : " << num << endl;
    checkStatus(cin);
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
