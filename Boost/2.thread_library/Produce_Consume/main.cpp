/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月14日 星期六 20时00分19秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "TaskQueue.hh"
#include "Producer.hh"
#include "Consumer.hh"

#include <thread>

/* =============== test =============== */
void test0() {
    TaskQueue tq(10);
    /* Producer().produce(tq); */
    std::thread pro(&Producer::produce, std::move(Producer()), std::ref(tq));
    std::thread cum(&Consumer::consume, std::move(Consumer()), std::ref(tq));

    pro.join();
    cum.join();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
