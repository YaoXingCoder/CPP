/*************************************************************************
    > File Name: 09_http_server.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月06日 星期日 11时29分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: http服务端 输出
    > Content:
 ************************************************************************/

#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <iostream>
#include <sstream>
#include <string>

#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>

static WFFacilities::WaitGroup waitGroup(1);

void sig_handle(int signo) { waitGroup.done(); }

void process(WFHttpTask *serverTask) {
    /* 获取时间 */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(stderr, "process start %ld.%06ld\n", tv.tv_sec,
            tv.tv_usec); // 并输出

    /* 获取客户端请求头数据 method uri http_version*/
    protocol::HttpRequest *req = serverTask->get_req();
    std::stringstream ss;
    ss << req->get_method() << " " << req->get_request_uri() << " "
       << req->get_http_version() << "\n";
    std::cout << ss.str();
    ss.str("");
    ss.clear(); // 重置状态标志位
    /* 遍历输出请求头信息 */
    protocol::HttpHeaderCursor reqCursor(req);
    std::string name;
    std::string value;
    while (reqCursor.next(name, value)) {
        ss << name << " : " << value << "\n";
        std::cout << ss.str();
        ss.str("");
        ss.clear(); // 重置状态标志位
    }

    /* 设置响应头数据 http_version status phrase header_pair*/
    protocol::HttpResponse *resp = serverTask->get_resp();
    resp->set_http_version("HTTP/1.1");
    resp->set_status_code("200");
    resp->set_reason_phrase("OK");
    resp->set_header_pair("Content-Type", "text/plain");

    /*
        在httpTask当中除了可以获取HTTP协议的内容
        还可以获取传输层和网络层的内容
    */
    char addrstr[128];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    unsigned short port;
    serverTask->get_peer_addr((sockaddr *)&addr,
                              &addr_len); // 获取ip地址和端口号
    if (addr.sin_family == AF_INET) {
        ss << "sin_family:AF_INET" << "\n";
        ss << "ip:" << inet_ntoa(addr.sin_addr) << "\n";
        ss << "port:" << ntohs(addr.sin_port) << "\n";
        std::cout << ss.str();
        ss.str("");
        ss.clear(); // 重置状态标志位
    }

    gettimeofday(&tv, NULL);
    fprintf(stderr, "process end %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
}

/* =============== test =============== */
void test0() {
    WFHttpServer server(process);

    if (server.start(8888) == 0) {
        std::cout << "server start success\n";
        waitGroup.wait(); // 主线程阻塞
        server.stop();
    } else {
        perror("server start");
        return;
    }
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handle);
    test0();
    return 0;
}
