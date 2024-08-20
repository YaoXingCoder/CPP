/*************************************************************************
    > File Name: 05_fstream_ofstream.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 11时17分00秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 输出流
    > Content:
    >   1.输出到文件
 ************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::ofstream;

void test01() {
    /* 关联文件 
     * 如果该文件不存在, 则默认创建该文件
     * */
    /* ofstream ofs("res.txt", std::ios::app); /1* 打开|创建, 更改模式为app, 每次写入 *1/ */
    ofstream ofs("res.txt"); /* 默认是打开|创建, 并且每次写入都是清空 */
    
    cout << ofs.good() << endl;

    string line("hello,world\n");
    
    /* 写入文件中 
     * 每次流都会清空文件, 再写入
     * */
    ofs << line;
    ofs << line;

    ofs.clear();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
