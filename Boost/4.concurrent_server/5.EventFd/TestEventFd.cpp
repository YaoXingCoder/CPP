/*************************************************************************
    > File Name: TestEventFd.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月22日 星期日 20时06分52秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "EventFd.hh"

#include <unistd.h>

#include <iostream>
#include <thread>
#include <functional>

class MyTask{
    public:
        void process() {
            std::cout << ">> MyTask is running" << std::endl;
        }
};

/* =============== test =============== */
void test0() {
    EventFd evt(std::bind(&MyTask::process, MyTask()) );
    
    std::thread th(std::bind(&EventFd::start, &evt));

    int cnt = 10;
    while (cnt--) {
        evt.wakeup();
        sleep(1);
    }

    evt.stop();
    th.join();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
