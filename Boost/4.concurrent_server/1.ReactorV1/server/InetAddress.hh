#ifndef __InetAddress_HH__
#define __InetAddress_HH__

#include <arpa/inet.h>
#include <string>

class InetAddress {
public:
    InetAddress(const std::string &, unsigned short);
    InetAddress(const struct sockaddr_in &);
    InetAddress(const InetAddress&);
    ~InetAddress();
public:
    std::string getIP();
    unsigned short getPort();
    struct sockaddr_in * getInetAddressPtr();
private:
    struct sockaddr_in _addr;
};


#endif
