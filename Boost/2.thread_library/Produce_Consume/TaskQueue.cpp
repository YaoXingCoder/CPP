/*************************************************************************
    > File Name: TaskQueue.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月14日 星期六 17时14分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 生产者消费者模式实现
    > Content:
 ************************************************************************/

#include "TaskQueue.hh"


TaskQueue::TaskQueue(const std::size_t & capacity)
: _capacity(capacity)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
{}

TaskQueue::~TaskQueue(){  }

/* 入队 */
void TaskQueue::push(const int & value){
    std::unique_lock<std::mutex> ul(_mutex); // 上锁

    while( full() ) { _notFull.wait(ul); } // 循环判满
    
    _que.emplace(value); // 放入任务
    _notEmpty.notify_one(); // 唤醒取出
}
/* 出队 */
int TaskQueue::pop() {
    std::unique_lock<std::mutex> ul(_mutex); // 上锁

    while( empty() ) { _notEmpty.wait(ul); } // 循环判空
    
    int tmp = _que.front();
    _que.pop();
    _notFull.notify_one();

    return tmp;
}

bool TaskQueue::full(){
    return _que.size() == _capacity;
}
bool TaskQueue::empty(){
    return 0 == _que.size();
}
