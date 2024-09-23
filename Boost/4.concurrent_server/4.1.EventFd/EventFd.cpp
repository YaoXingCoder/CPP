/*************************************************************************
    > File Name: EventFd.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月22日 星期日 19时48分09秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "EventFd.hh"

#include <sys/poll.h>
#include <errno.h>
#include <stdio.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <iostream>


EventFd::EventFd(EventFdCallBack && callBack) 
: _evtFd(createEventFd())
, _callBack(std::move(callBack))
, _isStarted(false)
{}

EventFd::EventFd(const EventFdCallBack & callBack) 
: _evtFd(createEventFd())
, _callBack(callBack)
, _isStarted(false)
{}

EventFd::~EventFd() { 
    close(_evtFd);
}


void EventFd::start() {
    _isStarted = true;
    struct pollfd pd;
    pd.fd = _evtFd;
    pd.events = POLLIN;

    while (_isStarted) {
        int nready = poll(&pd, 1, 3000);
        if ( nready == -1 && errno == EINTR) { continue; }
        else if ( nready == -1 ) { perror("pool"); return; }
        else if ( nready == 0 ) { std::cout << ">> poll timeout" << std::endl; }
        else {
            if ( pd.revents & POLLIN ) {
                handleRead();
                if ( _callBack ) { _callBack(); }
            }
        }
    }
}
void EventFd::stop(){
    _isStarted = false;
}

int EventFd::createEventFd(){
    int fd = eventfd(10, 0);
    if ( fd < 0 ) { perror("createEventFd"); return -1; }
    return fd;
}

void EventFd::handleRead(){
    uint64_t one = 1;
    ssize_t ret = read(_evtFd, &one, sizeof(one));
    if( ret != sizeof(uint64_t)) { perror("handleRead"); return; }
}

void EventFd::wakeup(){
    uint64_t one;
    ssize_t ret = write(_evtFd, &one, sizeof(one));
    if ( ret != sizeof( uint64_t) ) { perror("wakeup"); return; }
}
