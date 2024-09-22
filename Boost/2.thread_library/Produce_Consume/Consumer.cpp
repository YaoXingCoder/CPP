/*************************************************************************
    > File Name: Consumer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月14日 星期六 19时41分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 消费者
    > Content:
 ************************************************************************/

#include "Consumer.hh"
#include "TaskQueue.hh"

#include <iostream>
#include <thread>

Consumer::Consumer() {  }
Consumer::~Consumer() {  }
void Consumer::consume(TaskQueue & taskQue){
   int consume_num = 20;
   while ( consume_num-- ) {
        std::cout << "consume_num is " << taskQue.pop() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
   }
}


