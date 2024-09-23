/*************************************************************************
    > File Name: EchoServer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月23日 星期一 09时02分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "EchoServer.hh"
#include "TcpConnection.hh"

#include <iostream>

EchoServer::EchoServer(std::size_t threadNum, std::size_t queSize, const std::string & ip, unsigned short port) 
: _pool()
, _server(ip, port)
{}

EchoServer::~EchoServer() {  }

void EchoServer:: start() {
    _pool.start();
    _server.setAllCallBack(std::bind(&EchoServer::OnConnection, this, std::placeholders::_1)
                           ,std::bind(&EchoServer::OnMessage, this, std::placeholders::_1)
                           ,std::bind(&EchoServer::OnClosed, this, std::placeholders::_1));
    _server.start();
}

void EchoServer:: stop() {
    _pool.stop();
    _server.stop();
}

void EchoServer:: OnConnection( const TcpConnectionPtr & conn) {
    std::cout << conn->toString() << " has connected" << std::endl;
}

void EchoServer:: OnMessage( const TcpConnectionPtr & conn) {
    std::string msg = conn->recvive();
    std::cout << ">> server received message is " << msg << std::endl;
    MyTask task(msg, conn);
    _pool.addTask(std::bind(&MyTask::process, task));
}

void EchoServer:: OnClosed( const TcpConnectionPtr & conn){
    std::cout << conn->toString() << " is closing" << std::endl;
}

MyTask::MyTask(std::string msg, const TcpConnectionPtr & conn) 
: _msg(msg)
, _conn(conn)
{}

MyTask::~MyTask() {}

void MyTask::process() {
    _conn->sendToLoop(_msg);
}
