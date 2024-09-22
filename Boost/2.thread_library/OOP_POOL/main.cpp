/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月15日 星期日 11时21分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "threadPool.hh"

#include <iostream>
#include <memory>

class MyTask{
    public:
        void process( int x ) {
            ::srand(::clock());
            int number = ::rand()% 100;
            std::cout << ">> MyTask number = " << number << std::endl;
        }
};

/* =============== test =============== */
void test0() {
    std::unique_ptr<MyTask> ptask(new MyTask());

    ThreadPool t_pool;
    t_pool.start();

    int cnt = 20;
    ThreadPool::Task taskcb = std::bind(&MyTask::process, ptask.get(), 1);
    while( cnt-- ) {
        /* t_pool.addTask(std::bind(&MyTask::process, ptask.get(), 1)); */
        /* t_pool.addTask(std::bind(taskcb)); */
        t_pool.addTask(taskcb);
        /* std::cout << "cnt = " << cnt << std::endl; */
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
