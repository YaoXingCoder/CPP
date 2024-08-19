/*************************************************************************
    > File Name: 03_read_tellg_seekg.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 22时54分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 用read + tellg + seekg实现读取一个文件全部内容的程序
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;

void readFile(const char* filename) {
    /* 关联文件 */
    ifstream ifs(filename);
    if ( !filename ) { 
        cerr << "ifs open file fail";
        return;
    }

    /* 读取文件大小 */
    ifs.seekg(0, std::ios_base::end); /* 指示器定位到文件末尾 */
    long len_filecontent = ifs.tellg();
    cout << len_filecontent << endl;

    /* 开始读取文件 */
    char* buff = new char[len_filecontent + 1]();
    ifs.seekg(0, std::ios::beg); /* 重新将指示器定位文件起始 */
    ifs.read(buff, len_filecontent);

    /* 输出到终端 */
    string content(buff);
    /* cout << " constent is " << content << endl; */
    cout << buff << endl;

    delete[] buff;
    ifs.close();
}

/* 读取文件 */
void test01() {
    cout << "start" << endl;
    readFile("02_ifstream_file_content.cpp");
    cout << "end" << endl;
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
