/*************************************************************************
    > File Name: SocketIO.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 14时42分17秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "SocketIO.hh"

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

SocketIO::SocketIO(int fd) :_fd(fd) {}

SocketIO::~SocketIO() {}

/* 读取指定字符数的字符串 
 * parameter char *buf : 字符串首地址
 * parameter len :
 * */
int SocketIO::readn(char * buf, int len) {
    int total = 0; // 已读取的字节数
    int left = len; // 剩余字节数
    int ret = 0; // 异常记录
    char * pstr = buf; // 字符指针, 存放读取字符

    while(left > 0) {
        ret = read(_fd, pstr, left);
        if ( -1 == ret && errno == EINTR ) { continue; }
        else if ( -1 == ret ) { perror("readn"); return -1; }
        else if ( ret == 0 ) { break; }
        else { 
            total += ret;
            left -= ret;
            pstr += ret;
        }
    }

    return total;
}

int SocketIO::writen(const char * buf, int len) {
    int total = 0;
    int left = len;
    int ret = 0;
    const char *pstr = buf;
    
    while ( left > 0 ) {
        ret = write(_fd , pstr, left);
        if ( -1 == ret && errno == EINTR ) { continue; }
        else if ( -1 == ret ) { perror("writen"); return -1; }
        else if ( ret == -1 && errno == EPIPE ) { perror("has closed");  break; }
        else if ( 0 == ret ) { break; } 
        else {
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }

    return total;
}

int SocketIO::readLine(char * buf, int len) {
    int total = 0;
    int left = len - 1;
    int ret = 0;
    char * pstr = buf;

    while( left > 0 ) {
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if ( -1 == ret && errno == EINTR ) { continue; }
        else if ( -1 == ret ) { perror("readLine"); return -1; }
        else if ( ret == 0 ) { break; }
        else {
            for ( int i = 0; i < ret ; ++i ) {
                if ( pstr[i] == '\n' ) {
                    int str_offset = i + 1;
                    readn(pstr, str_offset);
                    pstr += str_offset;
                    *pstr = '\0';
                    return total + str_offset;
                }
            }

            readn(pstr, ret);
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }

    *pstr = '\0';
    return total - left;
}
