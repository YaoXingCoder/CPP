#ifndef __TCPCONNECTION_HH__
#define __TCPCONNECTION_HH__

#include "SocketIO.hh"
#include "InetAddress.hh"
#include "Socket.hh"


class TcpConnection {
public:
    explicit TcpConnection(int);
    ~TcpConnection();
public:
    std::string recvive();
    void send(const std::string &);
    std::string toString(); // 测试输出
    bool isColsed();
private:
    /* 获取地址 */
    InetAddress getPeerAddr();
    InetAddress getLocalAddr();
private:
    SocketIO _socketIO;
    /* 打印测试 */
    Socket _socket; // 必须定义在 InetAddress 前边
    InetAddress _localAddr;
    InetAddress _peerAddr;
};

#endif
