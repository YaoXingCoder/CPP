/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 16时27分22秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "textQuery.hh"

/* =============== test =============== */
void test0() {
    std::string queryWord("time");
    TextQuery tq;
    tq.readFile();
    tq.query(queryWord);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
