#ifndef __TCPCONNECTION_HH__
#define __TCPCONNECTION_HH__

#include "SocketIO.hh"
#include "InetAddress.hh"
#include "Socket.hh"

#include <memory>
#include <functional>


class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallBack = std::function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int);
    ~TcpConnection();
public:
    std::string recvive();
    void send(const std::string &);
    std::string toString(); // 测试输出
    bool isColsed();
private: // 获取地址
    InetAddress getPeerAddr();
    InetAddress getLocalAddr();
public: // 任务处理
    void setConnectionCallBack(const TcpConnectionCallBack &);
    void setMessageCallBack(const TcpConnectionCallBack &);
    void setClosedCallBack(const TcpConnectionCallBack &);
    void handleConnectionCallBack();
    void handleMessageCallBack();
    void handleClosedCallBack();
private:
    SocketIO _socketIO;
    /* 打印测试 */
    Socket _socket; // 必须定义在 InetAddress 前边
    InetAddress _localAddr;
    InetAddress _peerAddr;
private:
    TcpConnectionCallBack _onConnection;
    TcpConnectionCallBack _onMessage;
    TcpConnectionCallBack _onClosed;
};

#endif
