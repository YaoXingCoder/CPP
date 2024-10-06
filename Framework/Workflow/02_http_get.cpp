/*************************************************************************
    > File Name: 02_http_get.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月04日 星期五 21时22分10秒
    > Mail: JiaZiChunQiu@163.com
    > Title: workflow 连接发送http请求
    > Content:
 ************************************************************************/

#include <iostream>
#include <signal.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>

#define REDIRECT_MAX 5
#define RETRY_MAX 2

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo) { wait_group.done(); }

/* =============== test =============== */
void test0() {
    std::cout << "start\n";
    WFHttpTask *http_task = WFTaskFactory::create_http_task(
        "http://www.baidu.com", 10, 10, nullptr);
    http_task->start();
    wait_group.wait();
}

void wget_callback(WFHttpTask *task) {
    protocol::HttpRequest *req = task->get_req();    // 获取请求段指针
    protocol::HttpResponse *resp = task->get_resp(); // 获取响应段指着
    int state = task->get_state();                   // 获取状态值
    int error = task->get_error(); // 如果出错，获取出错值

    /* 根据枚举值，输出对应错误信息 */
    switch (state) {
    case WFT_STATE_SYS_ERROR: // 系统错误
        fprintf(stderr, "system error: %s\n", strerror(error));
        break;
    case WFT_STATE_DNS_ERROR: // DNS域名解析错误
        fprintf(stderr, "DNS error: %s\n", gai_strerror(error));
        break;
    case WFT_STATE_SSL_ERROR: //
        fprintf(stderr, "SSL error: %d\n", error);
        break;
    case WFT_STATE_TASK_ERROR: // 任务错误
        fprintf(stderr, "Task error: %d\n", error);
        break;
    case WFT_STATE_SUCCESS:
        break;
    }

    // 状态为失败
    if (state != WFT_STATE_SUCCESS) {
        fprintf(stderr, "Failed. Press Ctrl-C to exit.\n"); // 输出错误信息
        return;
    }

    std::string name; // key-value 值
    std::string value;

    /*
     * Print request.
     * methond : 请求的方法
     * version : http 版本
     * uri : 资源文件
     */
    std::cout << "\n------------------Request Head-----------------\n";
    fprintf(stdout, "method is %s, http version is %s, uri is %s\n\n",
            req->get_method(), req->get_http_version(), req->get_request_uri());

    protocol::HttpHeaderCursor req_cursor(
        req); // HttpHeaderCursor 可以遍历请求体

    /*
        循环遍历
    */
    while (req_cursor.next(name, value))
        fprintf(stdout, "name is %s: value is %s\n", name.c_str(),
                value.c_str()); // 键值对信息

    /*
        Print response header.
        输出响应头信息
    */
    std::cout << "\n------------------Response Head-----------------\n";
    fprintf(stdout, "http vesion is %s, status is %s, status message is %s\n",
            resp->get_http_version(), resp->get_status_code(),
            resp->get_reason_phrase());

    protocol::HttpHeaderCursor resp_cursor(resp); // 遍历响应头

    /* 循环遍历
        name, value 输入输出函数
    */
    while (resp_cursor.next(name, value))
        fprintf(stdout, "name is %s: value is %s\n", name.c_str(),
                value.c_str());

    /* Print response body. */
    const void *body; // body指向字符串的首地址
    size_t body_len;

    std::cout << "\n------------------Response Body-----------------\n";
    resp->get_parsed_body(
        &body, &body_len); // 获取到响应体，&body用于改变 body指针的指向
    fwrite(body, 1, body_len, stdout); // 输出响应体到 stdout
    fflush(stdout);                    // 刷新用户态缓冲区

    fprintf(stdout, "\n\nSuccess. Press Ctrl-C to exit.\n");
}

void test1() {
    std::cout << "start\n";
    WFHttpTask *task = WFTaskFactory::create_http_task(
        "http://www.baidu.com", REDIRECT_MAX, RETRY_MAX,
        wget_callback); // 创建WFHttpTask任务对象
    task->start();
    // protocol::HttpRequest *req = task->get_req(); // 获取请求对象
    wait_group.wait();
}

/* =============== main =============== */
int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handler);
    // test0();
    test1();
    return 0;
}
