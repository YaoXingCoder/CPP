/*************************************************************************
    > File Name: Acceptor.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 16时06分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "Acceptor.hh"

#include <sys/socket.h>
#include <sys/types.h>

Acceptor::Acceptor(const std::string & ip, unsigned short port)  : _sock() , _addr(ip, port) {}

Acceptor::~Acceptor() {}

void Acceptor::ready() {
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr() {
    int opt = 1;
    int ret = setsockopt(_sock.getFD(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if( ret) {
        perror("setsockopt SO_REUSEADDR");
        return;
    }
}

void Acceptor::setReusePort() {
    int opt = 1;
    int ret = setsockopt(_sock.getFD(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if( ret) {
        perror("setsockopt SO_REUSEPORT");
        return;
    }
}

void Acceptor::bind() {
    int ret = ::bind(_sock.getFD(), (struct sockaddr*)_addr.getInetAddressPtr(), sizeof(struct sockaddr));
    if ( -1 == ret ) { perror("bind()"); return; }
}

void Acceptor::listen() {
    int ret = ::listen(_sock.getFD(), LISTEN_MAX);
    if ( -1 == ret ) { perror("listen()"); return; }
}

int Acceptor::accept() {
    int connfd = ::accept(_sock.getFD(), nullptr, nullptr);
    if(-1 == connfd) { perror("accept"); return -1; }
    return connfd;
}
