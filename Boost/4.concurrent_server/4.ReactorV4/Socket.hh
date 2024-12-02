#ifndef __SOCKET_HH__
#define __SOCKET_HH__

#include "NonCopyable.hh"

class Socket : NonCopyable{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
public:
    int getFD() const;
private:
    int _fd;
};

#endif
