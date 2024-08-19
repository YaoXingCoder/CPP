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
#include <limits>
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

/* 通用的输出流错误处理 */
void inputInt(std::istream& is, int & number) {
    cout << "请输入一个整形数据：" << endl;
    is >> number;
    while(!is.eof()) {
        if(is.bad()) {
            cout << "istream has braoken!" << endl;
            return;
        } else if ( is.fail()) {
            cout << "请输入整型："  << endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            is >> number;
        } else {
            cout << "输入成功~ " << endl;
            break;
        }
    }
}

void test02() {
    int num = 0;
    inputInt(cin, num);

    cout << "num : " << num << endl;
    cout << "end~~~" << endl;
}

/* 流对象也可以自动转换为bool, 
 * cin 作为判断条件, 
 * 无错误则正确
 * 出现错误时, 自动转换为false 
 * */
void test03() {
    int num = 0;
    cout << "please input int :> " ;
    cin >> num;
    cout << "num : " << num << endl;
    if ( cin ) {
        cout << "goodbit" << endl;
    } else {
        cout << "error input" << endl;
    }
}

/* 连续赋值
 * cout << "hello," 返回值仍是 cout
 * cout << "hello" << "world" << endl;
 * 上边等价于：cout < "hello" , cout << "world" , cout << endl;
 *
 * 输入同理: 称为链式输入法
 * */
void test04() {
    /* 类比 */
    int a = 1, b = 2, c = 3;
    a = b = c;
    cout << "a,b,c = " << a << ", " << b << ", " << c << endl;

    cout << "hello, " << "world" << endl;
    int num = 10, num2 = 10;
    cin >> num >> num2;
    cout << "num:" << num << endl;
    cout << "num2:" << num2 << endl;
} 

int main (int argc, char* argv[]) {
    /* test01(); */
    /* test02(); */
    /* test03(); */
    test04();
    return 0;
}
