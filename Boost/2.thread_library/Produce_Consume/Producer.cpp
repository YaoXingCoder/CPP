/*************************************************************************
    > File Name: Producer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月14日 星期六 17时40分45秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 生产者
    > Content:
 ************************************************************************/

#include "Producer.hh"
#include "TaskQueue.hh"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <ctime>

Producer::Producer(){}
Producer::~Producer(){}

void Producer::produce(TaskQueue &taskQue){
    /* 随机数 */
    ::srand(::time(nullptr));
    int produce_num = 20;
    while( produce_num-- ) {
        int rand_num = rand() % 100;
        taskQue.push(rand_num);
        std::cout << "push num is " << rand_num << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
