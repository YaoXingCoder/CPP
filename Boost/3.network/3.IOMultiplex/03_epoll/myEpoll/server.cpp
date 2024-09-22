/*************************************************************************
    > File Name: server.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月19日 星期四 09时56分20秒
    > Mail: JiaZiChunQiu@163.com
    > Title: IOMutiplex Epoll server
    > Content:
 ************************************************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>

#include <iostream>

#define SERVER_PORT 8888
#define LISTEN_MAX 128
#define OPEN_MAX 1024

/* =============== test =============== */
void test0() {
    /* 1. 创建套接字 */
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( listenfd < 0 ) { perror("socket error"); exit(-1); }

    /* 2. 套接字多路复用 */
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    /* 3. 创建地址, bind 绑定地址 */
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if ( ret < 0 ) { perror("bind error"); close(listenfd);  exit(-1); }

    /* 4. 开启监听 */
    ret = listen(listenfd, LISTEN_MAX);
    if ( ret < 0 ) { perror("listen error"); close(listenfd); exit(-1); }

    /* 5. 创建epoll结构体, 添加监听事件和初始化就绪队列*/
    int epfd = epoll_create1(0);
    struct epoll_event ep_evt;
    ep_evt.data.fd = listenfd;
    ep_evt.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ep_evt);
    if ( ret < 0 ) { perror("epoll_clt error"); close(listenfd); close(epfd); exit(-1); }

    /* 6. 循环监听事件 */
    epoll_event ep_arr[OPEN_MAX];
    int nready = 0;
    while ( 1 ) {
        nready = epoll_wait(epfd, ep_arr, OPEN_MAX, -1);
        if ( nready == -1 && errno == EINTR ) { continue; }
        else if ( nready == -1 ) { perror("epoll_wait error"); close(listenfd); close(epfd); exit(-1); }

        /* 循环遍历就绪队列 */
        for ( int i = 0; i < nready; ++i ) {
            /* 异常处理 */
            if ( !(ep_arr[i].events & EPOLLIN) ) { continue; } // 确保是读就绪监听

            int sockfd = ep_arr[i].data.fd;
            /* 如果listenfd就绪 */
            if ( sockfd == listenfd ) {
                /* accept获取新的通信套接字, 获取客户端ip地址 */
                struct sockaddr_in clientAddr;
                socklen_t clientAddr_len = sizeof(clientAddr);
                int netfd = accept(listenfd, (struct sockaddr*)&clientAddr, &clientAddr_len);
                if ( netfd < -1 ) { perror("accept error"); close(listenfd); close(epfd); exit(-1); }
                char ip_str[INET_ADDRSTRLEN];
                printf("client addredd'ip is %s, port is %d.\n", inet_ntop(AF_INET, &clientAddr.sin_addr, ip_str, INET_ADDRSTRLEN), ntohs(clientAddr.sin_port));

                /* 添加新的套接字到读就绪监听 */
                struct epoll_event cli_evt;
                cli_evt.data.fd = netfd;
                cli_evt.events = EPOLLIN;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &cli_evt);
                if ( ret < 0 ) { perror("epoll_clt error"); close(listenfd); close(epfd); close(netfd); exit(-1); }
            } else {
                /* 客户端读就绪 */
                char buf[BUFSIZ] = { 0 };
                int nByte = read(sockfd, buf, sizeof(buf));
                /* 异常判断处理 */
                if ( nByte == 0 ) {
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if ( ret < 0 ) { perror("epoll_ctl del error"); }
                    close(sockfd);
                    printf("client[%d] closed connected.\n", sockfd);
                } else if ( nByte < 0 ) {
                    perror("read error");
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if ( ret < 0 ) { perror("epoll_ctl del error"); }
                    close(sockfd);
                } else {
                    /* 无异常, 正常处理 */
                    for(int j = 0; j < nByte; ++j)  {buf[j] = toupper(buf[j]); }
                    write(sockfd, buf, nByte);
                    write(STDOUT_FILENO, buf, nByte);
                }
            }
        }
    }
    close(listenfd);
    close(epfd);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
