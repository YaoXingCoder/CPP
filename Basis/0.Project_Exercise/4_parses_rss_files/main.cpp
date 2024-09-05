/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月04日 星期三 22时44分06秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "rss.hh"

/* =============== test =============== */
void test0() {
    RssReader r_reader;
    r_reader.parseRss(FILENAME_INPUT);
    r_reader.dump(FILENAME_OUTPUT);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
