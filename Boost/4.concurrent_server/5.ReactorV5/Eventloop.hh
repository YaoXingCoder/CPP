#ifndef __EVENTLOOP_HH__
#define __EVENTLOOP_HH__

#include <sys/epoll.h>

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <mutex>

class Acceptor;
class TcpConnection;

#define EPOLL_EVENT_MAX 1024

class Eventloop {
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>; // Tcp连接对象shared_ptr类型
    using TcpConnectionCallBack = std::function<void(const TcpConnectionPtr &)>; // Tcp回调函数类型
    using Functor = std::function<void()>; // 任务队列中的函数类型
public:
    Eventloop(Acceptor &, std::size_t list_capa = EPOLL_EVENT_MAX);
    ~Eventloop();
public:
    void loop(); // 循环开始
    void unloop();
private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int);
    int createEpollFd();
    void addEpollReadFd(int);
    void delEpollReadFd(int);
public: // 回调函数设置
    void setConnectionCallBack(TcpConnectionCallBack &&);
    void setMessageCallBack(TcpConnectionCallBack &&);
    void setClosedCallBack(TcpConnectionCallBack &&);
public: // V4 
    int createEventFd(); // 创建线程间通讯套接字
    void doPendingFunctors(); // 遍历并执行任务, 清空任务容器
    void putFunctorsPendings(Functor &&); // 存放任务到_pendings
private:
    void handleRead(); // 封装read, 读取_evtfd套接字
    void wakeup(); // 封装write, 写入内容, 用做通信
private: // V1
    int _epfd; // 监听结构套接字
    std::vector<struct epoll_event> _evtList; // 事件监听队列
    bool _isLooping;
    Acceptor & _acceptor; // 服务器相关操作的对象
    std::map<int, TcpConnectionPtr> _conns; // 文件描述符 int -- 连接对象 TcpConnection : 键值对
private: // V2添加自定义函数，通过回调函数实现
    TcpConnectionCallBack _onConnection;
    TcpConnectionCallBack _onMessage;
    TcpConnectionCallBack _onClosed;
private: // V4添加线程池, 用于线程间任务和通信
    int _evtfd; // 线程通信套接字
    std::vector<Functor> _pendings; // 存放任务容器
    std::mutex _mutex; // 互斥锁, 存放和读取任务会产生冲突
};

#endif
