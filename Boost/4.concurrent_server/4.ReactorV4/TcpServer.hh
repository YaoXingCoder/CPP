#ifndef __TCPSERVER_HH__
#define __TCPSERVER_HH__

#include "Acceptor.hh"
#include "Eventloop.hh"

class TcpServer{
public:
    using TcpConnectionPtr = Eventloop::TcpConnectionPtr;
    using TcpConnectionCallBack = Eventloop::TcpConnectionCallBack;
public:
    TcpServer(const std::string &, unsigned short, std::size_t evt_capa = EPOLL_EVENT_MAX);
    ~TcpServer();

public:
    void start();
    void stop();
    void setAllCallBack(TcpConnectionCallBack && cb_connection, TcpConnectionCallBack && cb_message, TcpConnectionCallBack && cb_closed);
private:
    Acceptor _acceptor;
    Eventloop _loop;
};

#endif
