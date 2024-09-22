/*************************************************************************
    > File Name: Socket.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 09时41分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: Socket 实现
    > Content:
 ************************************************************************/

#include "Socket.hh"

#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

/* #include <iostream> */

Socket::Socket() {
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( _fd < 0 ) { perror("socket"); return; }
}

Socket::Socket(int fd) :_fd(fd) {}

Socket::~Socket() { close(_fd); }

int Socket::getFD() const { return _fd; }

/* int main() { */
/*     Socket socket; */
/*     std::cout << socket.getFD() << std::endl; */
/*     return 0; */
/* } */
