/*************************************************************************
    > File Name: TestTcpConnection.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 16时46分19秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "Acceptor.hh"
#include "TcpConnection.hh"
#include "Eventloop.hh"
#include "TcpServer.hh"

#include "threadPool.hh"

#include <iostream>

using TcpConnectionPtr = Eventloop::TcpConnectionPtr;

ThreadPool * p_pool = nullptr;

class MyTask {
public:
    MyTask(const std::string & msg, const TcpConnectionPtr & con)
    : _msg(msg)
    , _con(con)
    {}
    ~MyTask() {}
public:
    void process() {
        _con->sendToLoop(_msg);
    }
private:
    std::string _msg;
    TcpConnectionPtr _con;
};

void onConnection(const TcpConnectionPtr & conn) {
    std::cout << "onConnection is running" << std::endl;
    std::cout << conn->toString() << " has connected" << std::endl;
}

void onMessage(const TcpConnectionPtr & conn) {
    std::string msg = conn->recvive();
    std::cout << ">> sever received : " << msg << std::endl;
    /* conn->send(msg); */
    MyTask myTask(msg, conn);
    p_pool->addTask(std::bind(&MyTask::process, &myTask));
}

void onClosed(const TcpConnectionPtr & conn) {
    std::cout << conn->toString() << " has closed" << std::endl;
}

/* =============== test =============== */
#if 0
void test0() {
    Acceptor acceptor("127.0.0.1", 8888);
    acceptor.ready(); // 服务端启动

    TcpConnection con(acceptor.accept()); // 等待accept获取连接
    
    std::cout << con.toString() << std::endl; // 调试输出

    while(1) {
        std::cout << ">> recv msg from client : " << con.recvive() << std::endl; // 接收客户端信息
        con.send("hello, client"); // 客户端返回信息
    }
}
#endif

void test1() {
    Acceptor acceptor("127.0.0.1", 8888);
    /* acceptor.ready(); */

    Eventloop evloop(acceptor);
    evloop.loop();
}

void test2() {
    Acceptor acceptor("127.0.0.1", 8888);

    Eventloop evloop(acceptor);
    evloop.setConnectionCallBack(std::move(onConnection));
    evloop.setMessageCallBack(std::move(onMessage));
    evloop.setClosedCallBack(std::move(onClosed));
    evloop.loop();
}

void test3() {
    TcpServer server("127.0.0.1", 8888);
    server.setAllCallBack(std::move(onConnection), std::move(onMessage), std::move(onClosed));
    server.start();
}

void test4() {
    ThreadPool pool;
    pool.start();
    p_pool = &pool;

    TcpServer server("127.0.0.1", 8888);
    server.setAllCallBack(std::move(onConnection), std::move(onMessage), std::move(onClosed));
    server.start();
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();
    return 0;
}
