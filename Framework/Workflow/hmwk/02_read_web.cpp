/*************************************************************************
    > File Name: 02_read_web.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月06日 星期日 09时20分51秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <signal.h>

#include <iostream>
#include <string>

#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

#define HTTP_URL "http://www.taobao.com"
#define REDIS_URL "redis://127.0.0.1:6379"
#define REDIRECT_MAX 5
#define RETRY_MAX 2

static WFFacilities::WaitGroup waitGroup(1);
void sig_handler(int signo) { waitGroup.done(); }

void httpCallBack(WFHttpTask *httpTask) {
    protocol::HttpRequest *req = httpTask->get_req();
    protocol::HttpResponse *resp = httpTask->get_resp();
    const void *body;
    size_t body_len;
    int state = httpTask->get_state(); // 获取状态值
    int error = httpTask->get_error(); // 如果出错，获取出错值
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
        resp->get_parsed_body(&body, &body_len);
        break;
    }

    if (state == WFT_STATE_SUCCESS) {
        WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
            REDIS_URL, RETRY_MAX,
            [](WFRedisTask *redisTask) { std::cerr << "redisTask fininshed"; });
        redisTask->get_req()->set_request("set",
                                          {HTTP_URL, std::to_string(body_len)});
        series_of(httpTask)->push_back(redisTask);
    }

    // fwrite(body, body_len, 1, stdout);
    // fflush(stdout);
    std::cout << "\nresp body_len is " << body_len << "\n";
}

/* =============== test =============== */
void test0() {
    WFHttpTask *httpTask = WFTaskFactory::create_http_task(
        HTTP_URL, REDIRECT_MAX, RETRY_MAX, httpCallBack);
    httpTask->start();
    waitGroup.wait();
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    std::cout << "start\n";
    signal(SIGINT, sig_handler);
    test0();
    std::cout << "finished\n";
    return 0;
}
