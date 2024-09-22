/*************************************************************************
    > File Name: client.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月19日 星期四 10时58分31秒
    > Mail: JiaZiChunQiu@163.com
    > Title: IOMultiplex client epoll
    > Content:
 ************************************************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>

#define SERVER_PORT 8888
#define OPEN_MAX 1024

/* =============== test =============== */
void test0() {
    /* 1. 创建套接字 */
    int clientfd = socket(AF_INET, SOL_SOCKET, 0);

    /* 2. 绑定端口地址 */
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    /* 3. 创建epoll结构体, 添加监听事件和读就绪数组 */
    int epfd = epoll_create1(0);
    epoll_event ep_evt;
    ep_evt.data.fd = clientfd;
    ep_evt.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ep_evt); // 服务器监听
    ep_evt.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ep_evt); // 读就绪监听
    epoll_event ep_evtarr[OPEN_MAX];

    /* 4. 循环监听 */
    int nready = 0;
    while(1) {
        nready = epoll_wait(epfd, ep_evtarr, OPEN_MAX, -1);
    
        for ( int i = 0; i < nready; ++i ) {
            int sockfd = ep_evtarr[i].data.fd;
            char buf[BUFSIZ] = { 0 };
            if ( clientfd == sockfd ) {
                bzero(buf, sizeof(buf));
                int nByte = read(sockfd, buf, sizeof(buf));
                std::cout << "server response is : "  << buf << std::endl;
            } else if ( sockfd == STDIN_FILENO ) {
                bzero(buf, sizeof(buf));
                fgets(buf, sizeof(buf), stdin);
                write(clientfd, buf, strlen(buf) + 1);
            }
        }
    }

    /* 5. 关闭资源 */
    close (clientfd);
    close (epfd);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
