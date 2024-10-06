/*************************************************************************
    > File Name: http_test_01.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月04日 星期五 21时01分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: workflow 使用
    > Content:
    >   1.使用条件等待
 ************************************************************************/

#include <iostream>
#include <signal.h>
#include <workflow/WFFacilities.h>

static WFFacilities::WaitGroup waitGroup(2);

void handle(int signum) {
    std::cout << "SIGING\n";
    waitGroup.done();
}

/* =============== test =============== */
void test0() {
    std::cout << "start\n";
    ::signal(SIGINT, handle);
    waitGroup.wait(); // 仍需 ctrl+c 两次
    std::cout << "finished\n";
}

/* =============== main =============== */
int main(int argc, char *argv[]) {
    test0();
    return 0;
}
