/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 14时36分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 日志记录
    > Content:
 ************************************************************************/

#include "log4cpp_file.hh"

/* =============== test =============== */
void test0() {
    /* Mylogger::getInstance()->warn("hello"); */
    LogCrit("hello");
    LogInfo("world");
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
