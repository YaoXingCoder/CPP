#ifndef __ECHOSERVER_HH__
#define __ECHOSERVER_HH__

#include "threadPool.hh"
#include "TcpServer.hh"

class MyTask {
public:
    using TcpConnectionPtr = TcpServer::TcpConnectionPtr;
public:
    MyTask(std::string, const TcpConnectionPtr &);
    ~MyTask();
public:
    void process();
private:
    std::string _msg;
    TcpConnectionPtr _conn;
};

class EchoServer {
public:
    using TcpConnectionPtr = TcpServer::TcpConnectionPtr;
public:
    EchoServer(std::size_t threadNum, std::size_t queSize, const std::string & ip, unsigned short port);
    ~EchoServer();
public:
    void start();
    void stop();
    void OnConnection( const TcpConnectionPtr &);
    void OnMessage( const TcpConnectionPtr &);
    void OnClosed( const TcpConnectionPtr &);
private:
    ThreadPool _pool;
    TcpServer _server;
};

#endif
