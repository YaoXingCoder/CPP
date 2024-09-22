/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月15日 星期日 11时21分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "Task.hh"
#include "Task.hh"
#include "threadPool.hh"

#include <iostream>
#include <memory>

/* =============== test =============== */
void test0() {
    std::unique_ptr<Task> ptask(new MyTask());

    ThreadPool t_pool;
    t_pool.start();

    int cnt = 20;
    while( cnt-- ) {
        t_pool.addTask(ptask.get());
        /* std::cout << "cnt = " << cnt << std::endl; */
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
