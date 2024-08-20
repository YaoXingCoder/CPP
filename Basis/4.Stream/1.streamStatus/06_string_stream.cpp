/*************************************************************************
    > File Name: 05_string_stream.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 11时13分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: string 流的使用
    > Content:
    >   1.输出流存入文件中
    >   2.解析字符串
    >   3.读取配置文件
 ************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;

#define FILENAME_PATH "myserver.conf"

void test01() {
    /* 关联文件 */
    ifstream  ifs("myserver.conf");

    if ( !ifs ) {
        cout << "ifstream open file failed" << endl;
        return;
    }

    string line;
    string key;
    string value;
    while( std::getline(ifs, line) ) {
        istringstream iss(line);
        /* iss 相当于一个缓冲区, iss(line) 将 line对象的数据放入缓冲区 */
        /* iss >> key >> value 将缓冲区中的内容输出到 key 和 value */
        /* 因为 iss 默认是以 ' ' 空格符 为 分隔符 所以两次输出效果 */
        iss >> key >> value;
        cout << key << " -------------> " << value << endl;
    }

    ifs.close();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
