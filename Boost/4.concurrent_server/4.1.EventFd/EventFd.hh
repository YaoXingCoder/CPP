#ifndef __EVENTFD_HH__
#define __EVENTFD_HH__

#include <functional>

class EventFd{
public:
    using EventFdCallBack = std::function<void()>;
public:
    EventFd(EventFdCallBack &&);
    EventFd(const EventFdCallBack &);
    ~EventFd();
public:
    void start();
    void stop();
    int createEventFd();
    void handleRead();
    void wakeup();
private:
    int _evtFd;
    EventFdCallBack _callBack;
    bool _isStarted;
};
#endif
