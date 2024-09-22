/*************************************************************************
    > File Name: 01_aton_ntoa.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月17日 星期二 22时32分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <arpa/inet.h>

int test() {
	const char *ipstr = "192.168.0.1";
//	char *ipstr = "255.255.255.255";
	struct sockaddr_in sockaddr;
	int ret;
	char *str;

	/* convert ip from text to binary for IPv4  */
	ret = inet_aton(ipstr, &sockaddr.sin_addr);
	/* if (ret == 0) { */
	/* 	fprintf(stderr, "inet_aton error: invalid ip string: %s\n", ipstr); */
	/* 	return -1; */
	/* } */
	printf("inet_aton convert ip : from %s to %d\n", ipstr, sockaddr.sin_addr.s_addr);

	/* convert ip from text to binary for IPv4 except 255.255.255.255 */
	sockaddr.sin_addr.s_addr = inet_addr(ipstr); /* avoid to use inet_addr */
	/* if (sockaddr.sin_addr.s_addr == INADDR_NONE) { */
	/* 	fprintf(stderr, "inet_addr error: invalid ip string: %s\n", ipstr); */
	/* 			return -1; */
	/* } */
	printf("inet_addr convert ip : from %s to %d\n", ipstr, sockaddr.sin_addr.s_addr);

	/* convert ip from binary to text for IPv4 */
	str = inet_ntoa(sockaddr.sin_addr);
	/* if (str == NULL) { */
	/* 	fprintf(stderr, "inet_ntoa error: invalid ip structure: %d\n", sockaddr.sin_addr.s_addr); */
	/* 	return -1; */
	/* } */
	printf("inet_ntoa convert ip : from %d to %s\n", sockaddr.sin_addr.s_addr, str);

	return 0;
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test();
    return 0;
}
