/*************************************************************************
    > File Name: server.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月18日 星期三 17时24分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: POLL server
    > Content:
 ************************************************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <iostream>

#define SERVER_PORT 8888
#define LISTEM_MAX 128
#define OPEN_MAX 1024

void test() {
    /* 1. 创建socket套接字 */
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( listenfd < 0 ) { std::perror("socket error"); std::exit(-1); }

    /* 1.1 套接字复用 */
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // 允许套接字处于"TIME_WAIT"状态下重启
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)); // 允许多个套接字绑定到同一个地址和端口上

    /* 2. 绑定IP和PORT */
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) { std::perror("bind error"); close(listenfd); std::exit(-1); }

    /* 3. 开启监听 */
    ret = listen(listenfd, LISTEM_MAX);
    if ( ret < 0 ) { std::perror("listen error"); close(listenfd); std::exit(-1); }

    /* 4. 创建poll, 监听事件, 监听数组 */
    struct pollfd client[OPEN_MAX]; // 常见pollfd结构体数组
    for ( int i = 0; i < OPEN_MAX; ++i ) { client[i].fd = -1; } // 将所有的结构体fd赋值-1
    client[0].fd = listenfd; // listenfd 放入结构体数组
    client[0].events = POLLIN;
    int maxi = 0; // 数组中被监听时间个数

    /* 5. 循环监听 */
    int nready = 0;
    while (1) {
        /* 5.1 监听时间 */
        int i = 0;
        nready = poll(client, maxi + 1, -1); // timeout = -1, 持续阻塞
        if( nready == -1 && errno == EINTR ) { continue; }
        else if ( nready == -1 ) { 
            std::perror("poll error");
            close(listenfd);
            exit(-1);
        }

        /* 5.2 listenfd 就绪 */
        if ( client[0].revents & POLLIN ) {
            /* 5.2.1 获取 accept 的地址和套接字 */
            struct sockaddr_in clientAddr;
            bzero(&clientAddr, sizeof(clientAddr));
            socklen_t clientAddr_len = sizeof(serverAddr);
            int netfd = accept(client[0].fd, (struct sockaddr*)&clientAddr, &clientAddr_len);
            if ( netfd < 0 ) { perror("accept error"); exit(-1); }
            char ip_str[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN = 16
            printf("client address IP is %s, port is %d.\n", inet_ntop(AF_INET, &clientAddr.sin_addr, ip_str, INET_ADDRSTRLEN), ntohs(clientAddr.sin_port)); // 打印客户端地址

            /* 5.2.2 添加新套接字到监听事件中 */
            /* 遍历找出监听数组中第一个为-1的位置, 并添加fd和事件类型 */
            for ( i = 1; i < OPEN_MAX; ++i ) {
                if ( client[i].fd < 0 ) { client[i].fd = netfd; break; }
            }
            if ( i == OPEN_MAX ) { fputs("too manys clients.\n", stderr); std::exit(-1); } // 如果i达到最大监听数, 则提示报错退出
            client[i].events = POLLIN; // 更新事件类型
            if ( i > maxi ) { maxi = i; } // 监听数组的事件个数更新
            if ( --nready == 0 ) { continue; } // 如果只有一个就绪且还是listenfd套接字, 则不再进行下边的读就绪循环
        }

        /* 5.3 客户端读就绪监听 */
        /* 循环遍历就绪数组, 并读就绪事件做对应处理 */
        for ( i = 1; i <= maxi; ++i ) {
            int sockfd = 0; // 存储读就绪的套接字
            if ( (sockfd = client[i].fd) < 0 ) { continue; } // 之前连结果又断开后, 数组的前边可能存在没有连接的位置 
        
            /* 5.3.1 客户端套接字监听判断 */
            if ( client[i].revents & POLLIN ) {
                int n = 0; // 读取的字符个数
                char buf[BUFSIZ] = { 0 }; // BUFSIZ = 8192
                /* 5.3.2 
                 * 如果返回值 < 0 , 根据报错进行判断处理
                 * 如果>0, 处理并发送给客户端以及终端
                 * */
                if ( (n = read(sockfd, buf, sizeof(buf))) < 0 ) { 
                    if ( errno == ECONNABORTED ) { 
                        printf("client[%d] abort connect\n", i);
                        close(sockfd);
                        client[i].fd = -1;
                    } else { perror("read n = 0 error"); }
                } else if ( n > 0 ) {
                    for ( int j = 0; j < n; ++j ) { buf[j] = toupper(buf[j]); }
                    write(sockfd, buf, n);
                    write(STDOUT_FILENO, buf, n);
                } else {
                    close(sockfd);
                    client[i].fd = -1;
                }
            }
            if ( --nready == 0 ) { break; } // 如果nready == 0, 不再循环遍历, 直接退出读就绪循环
        }
    }
    close(listenfd);
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test();
    return 0;
}
