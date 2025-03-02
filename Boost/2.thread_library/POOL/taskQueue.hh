#ifndef __TASKQUEUE_HH__
#define __TASKQUEUE_HH__

#include <queue>
#include <mutex>
#include <condition_variable>

class Task;

class TaskQueue{
public:
    using Element = Task *;
    TaskQueue(const std::size_t capacity = 10);
    ~TaskQueue();

public:
    bool full() const;
    bool empty() const;
    void push(Element);
    Element pop();
    void wakeup();

private:
    std::size_t _capacity;
    std::queue<Element> _que;
    std::mutex _mutex;
    std::condition_variable _notFull;
    std::condition_variable _notEmpty;
    bool _flag; // 退出标位置, false退出

};

#endif
