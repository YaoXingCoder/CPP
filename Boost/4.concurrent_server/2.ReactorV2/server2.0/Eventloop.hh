#ifndef __EVENTLOOP_HH__
#define __EVENTLOOP_HH__

#include <sys/epoll.h>

#include <vector>
#include <map>
#include <memory>

class Acceptor;
class TcpConnection;

#define EPOLL_EVENT_MAX 1024

class Eventloop {
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
public:
    Eventloop(Acceptor &, std::size_t list_capa = EPOLL_EVENT_MAX);
    ~Eventloop();
public:
    void loop();
    void unloop();
private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int);
    int createEpollFd();
    void addEpollReadFd(int);
    void delEpollReadFd(int);
private:
    int _epfd;
    std::vector<struct epoll_event> _evtList;
    bool _isLooping;
    Acceptor & _acceptor;
    std::map<int, TcpConnectionPtr> _conns;
};

#endif
