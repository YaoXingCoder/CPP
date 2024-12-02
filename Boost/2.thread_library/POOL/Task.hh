#ifndef __TASK_HH__
#define __TASK_HH__


class Task {
public:
    /* Task(); */
    virtual void process() = 0;
    virtual ~Task();
private:
};

class MyTask : public Task {
public:
    void process() override;
};

#endif
