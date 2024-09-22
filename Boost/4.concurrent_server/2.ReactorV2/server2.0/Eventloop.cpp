/*************************************************************************
    > File Name: Eventloop.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 20时27分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "Eventloop.hh"
#include "Acceptor.hh"
#include "TcpConnection.hh"

#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <stdio.h>

#include <iostream>

Eventloop::Eventloop(Acceptor & acceptor, std::size_t list_capa) :_epfd(createEpollFd()), _evtList(list_capa), _isLooping(false), _acceptor(acceptor) {
    int listenfd = acceptor.getFD(); // 获取server的listenfd
    addEpollReadFd(listenfd); // 将listenfd添加到事件监听
}

Eventloop::~Eventloop(){ close (_epfd); }

void Eventloop::loop() {
    _isLooping = true;
    while( _isLooping ) { waitEpollFd(); } // 进入循环
}

void Eventloop::unloop() {
    _isLooping = false;
}


void Eventloop::waitEpollFd() {
    int nready = 0;
    do{
        nready = epoll_wait(_epfd, _evtList.data(), _evtList.size(), 3000);
    }while( -1 == nready && errno == EINTR ); // 能容忍的异常
    if ( nready == -1 ) { perror("epoll_wait"); return; } // 异常
    else if ( 0 == nready ) { std::cout << ">> epoll_wait timeout" << std::endl; } // 等待事件结束
    else {
        if ( _evtList.size() == nready ) { _evtList.resize(2 * nready); } // 扩容
        for ( int idx = 0; idx < nready; ++idx ) {
            int sockfd = _evtList[idx].data.fd; // 获取到就绪队列中的fd
            int listenfd = _acceptor.getFD(); // 获取到server的listenfd
            
            /* 新用户连接, 且为读就绪 */
            if ( listenfd == sockfd ) {
                if ( EPOLLIN & _evtList[idx].events ) { handleNewConnection(); } // 处理新连接请求
            } else {
                if ( EPOLLIN & _evtList[idx].events ) { handleMessage(sockfd); } // 处理老链接上的数据的收发
            }
        }
    }
}

void Eventloop::handleNewConnection() {
    int connfd = _acceptor.accept();
    if( connfd == -1 ) { perror("handleNewConnection"); return; }

    addEpollReadFd(connfd); // 添加套接字到监听事件中

    TcpConnectionPtr conn(new TcpConnection(connfd));
    _conns[connfd] = conn; // 添加新的TcpConnection到map中
    
    std::cout << conn->toString() << std::endl; // 打印新连接的地址
}

void Eventloop::handleMessage(int connfd) {
    std::map<int, TcpConnectionPtr>::iterator it = _conns.find(connfd);
    if ( it != _conns.end() ) {
        bool flag = it->second->isColsed(); // 连接是否关闭
        if ( flag ) {
            delEpollReadFd(connfd); // 将连接移除
            _conns.erase(it); // 删除连接
        } else {
            std::string msg = it->second->recvive();
            it->second->send(msg); // 回应客户端消息
        }
    } else {
        std::cout << "Connection does not exist." << std::endl;
        return;
    }
}

int Eventloop::createEpollFd() {
    return epoll_create1(0);
}

void Eventloop::addEpollReadFd(int sockfd) {
    struct epoll_event evt;
    evt.data.fd = sockfd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, sockfd, &evt);
    if ( ret == -1 ) { perror("epoll_ctl add"); return; }
}

void Eventloop::delEpollReadFd(int sockfd) {
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, sockfd, nullptr);
    if ( ret == -1 ) { perror("epoll_ctl del"); return; }
}
