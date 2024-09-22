/*************************************************************************
    > File Name: TcpConnection.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 16时31分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "TcpConnection.hh"

#include <sstream>
#include <iostream>

TcpConnection::TcpConnection(int fd) :_socketIO(fd), _socket(fd), _localAddr(getLocalAddr()), _peerAddr(getPeerAddr()) {}

TcpConnection::~TcpConnection() {}

std::string TcpConnection::recvive() {
    char buf[BUFSIZ] = { 0 };
    _socketIO.readLine(buf, sizeof(buf));
    return std::string(buf);
}

void TcpConnection::send(const std::string & msg) {
    _socketIO.writen(msg.c_str(), msg.size());
}

std::string TcpConnection::toString() {
    std::ostringstream oss;
    oss << _localAddr.getIP() << ":" << _localAddr.getPort() 
        << "---->"
        << _peerAddr.getIP() << ":" << _peerAddr.getPort();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr() {
    struct sockaddr_in localAddr;
    socklen_t localAddr_len = sizeof(localAddr);
    /* socklen_t localAddr_len = sizeof(struct sockaddr); */
    int ret = getsockname(_socket.getFD(), (struct sockaddr*)&localAddr, &localAddr_len);
    if ( -1 == ret ) { perror("getsockname"); }
    return InetAddress(localAddr);
}

InetAddress TcpConnection::getPeerAddr() {
    struct sockaddr_in peerAddr;
    socklen_t peerAddr_len = sizeof(peerAddr);
    /* socklen_t peerAddr_len = sizeof(struct sockaddr); */
    int ret = getpeername(_socket.getFD(), (struct sockaddr*)&peerAddr, &peerAddr_len);
    if ( -1 == ret ) { perror("getpeername"); }
    return InetAddress(peerAddr);
}

bool TcpConnection::isColsed() {
    char buf[10];
    int ret = recv(_socket.getFD(), buf, sizeof(buf), MSG_PEEK);
    return ret == 0;
}


/* 
 * 回调函数设置
 */
void TcpConnection::setConnectionCallBack(const TcpConnectionCallBack & cb_connection){
    _onConnection = cb_connection;
}
void TcpConnection::setMessageCallBack(const TcpConnectionCallBack & cb_message){
    _onMessage = cb_message;
}
void TcpConnection::setClosedCallBack(const TcpConnectionCallBack & cb_closed){
    _onClosed = cb_closed;
}

/* 
 * 回调函数执行
 */
void TcpConnection::handleConnectionCallBack(){
    if ( _onConnection ) { _onConnection(shared_from_this()); }
    else { std::cout << "_onMessage is nullptr" << std::endl; }
}
void TcpConnection::handleMessageCallBack(){
    if ( _onMessage ) { _onMessage(shared_from_this()); }
    else { std::cout << "_onMessage is nullptr" << std::endl; }
}
void TcpConnection::handleClosedCallBack(){
    if ( _onClosed ) { _onClosed(shared_from_this()); }
    else { std::cout << "_onClosed is nullptr" << std::endl; }
}
