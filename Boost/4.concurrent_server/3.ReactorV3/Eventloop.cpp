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

/*
 * 析构
 * 关闭epfd套接字
 */
Eventloop::~Eventloop(){ close (_epfd); }

/*
 * 循环开始
 */
void Eventloop::loop() {
    _isLooping = true;
    while( _isLooping ) { waitEpollFd(); } // 进入循环
}

/*
 * 循环结束
 */
void Eventloop::unloop() {
    _isLooping = false;
}

/* 
 * 监听事件
 * 处理就绪队列
 */
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

/*
 * 处理新连接
 */
void Eventloop::handleNewConnection() {
    int connfd = _acceptor.accept();
    if( connfd == -1 ) { perror("handleNewConnection"); return; }

    addEpollReadFd(connfd); // 添加套接字到监听事件中

    TcpConnectionPtr conn(new TcpConnection(connfd));
    _conns[connfd] = conn; // 添加新的TcpConnection到map中

    /* 连接成功后设置任务处理函数 */
    conn->setConnectionCallBack(_onConnection); 
    conn->setMessageCallBack(_onMessage);
    conn->setClosedCallBack(_onClosed);

    /* 通过TcpConnection对象调用对应函数 */
    conn->handleConnectionCallBack();
}

/*
 * 处理客户端任务
 */
void Eventloop::handleMessage(int connfd) {
    std::map<int, TcpConnectionPtr>::iterator it = _conns.find(connfd);
    if ( it != _conns.end() ) {
        bool flag = it->second->isColsed(); // 连接是否关闭
        if ( flag ) {
            it->second->handleClosedCallBack();
            delEpollReadFd(connfd); // 将连接移除
            _conns.erase(it); // 删除连接
        } else {
            it->second->handleMessageCallBack();
            /* std::string msg = it->second->recvive(); */
            /* it->second->send(msg); // 回应客户端消息 */
        }
    } else {
        std::cout << "Connection does not exist." << std::endl;
        return;
    }
}

/*
 * 创建底层结构
 */
int Eventloop::createEpollFd() {
    return epoll_create1(0);
}

/*
 * 添加读就绪监听事件
 */
void Eventloop::addEpollReadFd(int sockfd) {
    struct epoll_event evt;
    evt.data.fd = sockfd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, sockfd, &evt);
    if ( ret == -1 ) { perror("epoll_ctl add"); return; }
}


/*
 * 删除读就绪事件
 */
void Eventloop::delEpollReadFd(int sockfd) {
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, sockfd, nullptr);
    if ( ret == -1 ) { perror("epoll_ctl del"); return; }
}

/* 
 * 回调函数设置
 */
void Eventloop::setConnectionCallBack(TcpConnectionCallBack && cb_connection){
    _onConnection = std::move(cb_connection);
}
void Eventloop::setMessageCallBack(TcpConnectionCallBack && cb_message){
    _onMessage = std::move(cb_message);
}
void Eventloop::setClosedCallBack(TcpConnectionCallBack && cb_closed){
    _onClosed = std::move(cb_closed);
}
