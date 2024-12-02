#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>

class TaskQueue {
public:
    TaskQueue(const std::size_t & capacity = 10);
    ~TaskQueue();

public:
    void push(const int &);
    int pop();
    bool full();
    bool empty();

private:
    std::size_t _capacity;
    std::queue<int> _que;
    std::mutex _mutex;
    std::condition_variable _notFull;
    std::condition_variable _notEmpty;
};

#endif
