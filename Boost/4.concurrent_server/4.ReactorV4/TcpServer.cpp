/*************************************************************************
    > File Name: TcpServer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月22日 星期日 14时25分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "TcpServer.hh"

TcpServer::TcpServer(const std::string & ip, unsigned short port, std::size_t evt_capa )
: _acceptor(ip, port)
, _loop(_acceptor)
{}
TcpServer::~TcpServer() {}


void TcpServer::start() {
    _loop.loop();
}
void TcpServer::stop() {
    _loop.unloop();
}
void TcpServer::setAllCallBack(TcpConnectionCallBack && cb_connection, TcpConnectionCallBack && cb_message, TcpConnectionCallBack && cb_closed) {
    _loop.setConnectionCallBack(std::move(cb_connection));
    _loop.setMessageCallBack(std::move(cb_message));
    _loop.setClosedCallBack(std::move(cb_closed));
}

