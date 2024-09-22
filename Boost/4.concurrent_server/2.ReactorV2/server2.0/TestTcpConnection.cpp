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

#include <iostream>

/* =============== test =============== */
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

void test1() {
    Acceptor acceptor("127.0.0.1", 8888);
    /* acceptor.ready(); */

    Eventloop evloop(acceptor);
    evloop.loop();
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
