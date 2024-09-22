/*************************************************************************
    > File Name: InetAddress.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月20日 星期五 10时19分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "InetAddress.hh"
/* #include <iostream> */

InetAddress::InetAddress(const std::string & ip, unsigned short port) {
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in & addr) :_addr(addr) {}

InetAddress::InetAddress(const InetAddress & other): _addr(other._addr) {}

InetAddress::~InetAddress() {}

std::string InetAddress::getIP() {
    char ip_str[INET_ADDRSTRLEN];
    return std::string(inet_ntop(AF_INET, &_addr.sin_addr, ip_str, INET_ADDRSTRLEN));
}

unsigned short InetAddress::getPort() {
    return ntohs(_addr.sin_port);
}

struct sockaddr_in * InetAddress::getInetAddressPtr() {
    return &_addr;
}

/* int main() { */
/*     InetAddress inet_addr("127.0.0.1", 8888); */
/*     std::cout << inet_addr.getInetAddressPtr() << std::endl; */
/*     std::cout << inet_addr.getIP() << std::endl; */
/*     std::cout << inet_addr.getPort() << std::endl; */
/*     return 0; */
/* } */
