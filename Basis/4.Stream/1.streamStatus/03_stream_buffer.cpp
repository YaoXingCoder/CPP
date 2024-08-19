/*************************************************************************
    > File Name: 03_stream_buffer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 16时15分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 标准输出缓冲
    > Content:
 ************************************************************************/

#include <unistd.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void test01() {
    /* 程序结束 */
    /* for( int i = 0; i < 1024; ++i ) { */
    /*     cout << 'a'; */
    /* } */

    /* 遇到换行符 */
    for ( int i = 0; i < 1024; ++i ) {
        if ( i % 5 == 0 ) { cout << endl; }
        cout << 'a';
    }
    sleep(3);
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
