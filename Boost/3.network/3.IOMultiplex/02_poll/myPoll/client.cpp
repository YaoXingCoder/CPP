/*************************************************************************
    > File Name: client.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月18日 星期三 20时37分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: poll client
    > Content:
 ************************************************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#include <iostream>

#define SERVER_PORT 8888

/* =============== test =============== */
void test0() {
    /* 1. 常见套接字 */
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( clientfd < 0 ) { perror("sockfd error."); exit(0); }

    /* 2. 获取服务区IP地址 */
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* 3. 连接服务端 */
    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if ( ret < 0 ) { perror("connect error"); close(clientfd); std::exit(-1); }

    /* 4. 创建select监听事件 */
    fd_set mainSet;
    FD_ZERO(&mainSet);
    FD_SET(clientfd, &mainSet);
    FD_SET(STDIN_FILENO, &mainSet);
    int maxfd = clientfd > STDIN_FILENO ? clientfd : STDIN_FILENO;

    /* 循环监听 */
    int nready = 0;
    while( 1 ) {
        fd_set rset = mainSet; // 重置监听监听集合
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if ( nready < 0 ) { perror("select error"); std::exit(-1); }

        /* cilentfd 读就绪 */
        char buf[BUFSIZ] = { 0 };
        if ( FD_ISSET(clientfd, &rset) ) {
            bzero(buf, sizeof(buf));
            int n = read(clientfd, buf, sizeof(buf));
            if ( n < 0 ) { perror("read error"); std::exit(-1); }
            else if ( n == 0 ) { fputs("server is closed.\n", stdout); exit(-1);}
            else { std::cout << "server : " << buf << std::endl;  }
        }

        /* STDIN_FILENO 读就绪 */
        if ( FD_ISSET(STDIN_FILENO, &rset) ) {
            bzero(buf, sizeof(buf));
            fgets(buf, sizeof(buf), stdin);
            write(clientfd, buf, strlen(buf) + 1);
        }
    }
    close(clientfd);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
