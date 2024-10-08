/*************************************************************************
    > File Name: 09_http_server.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月06日 星期日 11时29分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: http服务端 login
    > Content:
 ************************************************************************/

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>

#define INDEX_PAHT "index.html"
#define BUFFER_SIZE 4096

#define REDIS_URL "redis://127.0.0.1:6379"
#define RETRY_MAX 2

struct SeriesContext {
    std::string url;
    WFHttpTask *serverTask; // 让newTask找到serverTask, 从而可以修改其响应
};

static WFFacilities::WaitGroup waitGroup(1);

void sig_handle(int signo) { waitGroup.done(); }

void process(WFHttpTask *serverTask) {
    /* 获取请求响应头  */
    protocol::HttpRequest *req = serverTask->get_req();
    protocol::HttpResponse *resp = serverTask->get_resp();

    /* 获取 url 和 path 字符串 */
    std::string method = req->get_method();
    std::string url = req->get_request_uri();
    std::string path = url.substr(0, url.find("?"));

    std::cout << path << "\n";

    /* 处理请求 */
    if (method == "GET" && path == "/login") {
        /* 获取文件大小 */
        struct stat sb;
        int ret = stat(INDEX_PAHT, &sb);
        off_t fd_size = sb.st_size;
        std::cout << fd_size << "\n";

        /* 创建IO任务 */
        char *buf = new char[fd_size + 1]{0}; // 缓存

        WFFileIOTask *readTask = WFTaskFactory::create_pread_task(
            INDEX_PAHT, static_cast<void *>(buf), fd_size, 0,
            [serverTask, buf](WFFileIOTask *ioTask) {
                serverTask->get_resp()->append_output_body(buf);
                delete[] buf;
            });

        series_of(serverTask)->push_back(readTask); // 添加任务到序列
    } else if (method == "POST" && path == "/login") {
        /* 获取请求数据 */
        const void *body;
        size_t body_len;
        req->get_parsed_body(&body, &body_len);
        // std::cerr << "\nbody is "
        //           << static_cast<char *>(const_cast<void *>(body)) << "\n";

        /* 解析字符串 */
        std::string wholeBody = static_cast<char *>(const_cast<void *>(body));
        std::string uname = wholeBody.substr(0, wholeBody.find("&"));
        std::string pwd = wholeBody.substr(wholeBody.find("&") + 1);
        std::string unameValue = uname.substr(uname.find("=") + 1);
        std::string pwdValue = pwd.substr(pwd.find("=") + 1);
        // std::cout << "uname is " << unameValue << ", pwd is " << pwdValue
        //           << "\n";

        /* 创建 redis 任务 */
        SeriesWork *series = series_of(serverTask);
        WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
            REDIS_URL, RETRY_MAX, [=](WFRedisTask *redisTask) {
                protocol::RedisResponse *resp = redisTask->get_resp();
                protocol::RedisValue val;
                resp->get_result(val);
                if (val.is_string()) {
                    if (pwdValue == val.string_value()) {
                        serverTask->get_resp()->append_output_body(
                            "<html>login successfully</html>");
                        return;
                    }
                }
                serverTask->get_resp()->append_output_body(
                    "<html>login failed</html>");
            });
        redisTask->get_req()->set_request("hget", {"login", unameValue});
        series->push_back(redisTask);
    }

    std::cout << "\nfinished\n";
}

/* =============== test =============== */
void test0() {
    struct WFServerParams params =
        HTTP_SERVER_PARAMS_DEFAULT; // 服务端的默认参数

    params.request_size_limit = 8 * 1024 * 1024; // 修改参数,限制请求的最大大小
    WFHttpServer server(
        &params,
        process); // 调用WFHttpServer的ctor(构造函数) 指定了server的process

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
