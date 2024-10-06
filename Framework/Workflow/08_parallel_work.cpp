/*************************************************************************
    > File Name: 08_parallel_work.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月05日 星期六 22时33分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 平行
    > Content:
 ************************************************************************/

#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

#define RETRY_MAX 2
#define REDIRECT_MAX 5

struct SeriesContext {
    std::string url;
    size_t body_len;
};

static WFFacilities::WaitGroup waitGroup(1);
void sig_handler(int signo) { waitGroup.done(); }

void httpCallBack(WFHttpTask *task) {
    // 获取到resp
    protocol::HttpResponse *resp = task->get_resp();

    int state = task->get_state(); // 获取状态
    int error = task->get_error(); // 获取错误原因
    switch (state) {
    case WFT_STATE_SYS_ERROR:
        std::cerr << "system error: " << strerror(error) << "\n";
        break;
    case WFT_STATE_DNS_ERROR:
        std::cerr << "DNS error: " << gai_strerror(error) << "\n";
        break;
    case WFT_STATE_SSL_ERROR:
        std::cerr << "SSL error\n";
        break;
    case WFT_STATE_TASK_ERROR:
        std::cerr << "Task error\n";
        break;
    case WFT_STATE_SUCCESS:
        break;
    }
    if (state != WFT_STATE_SUCCESS) {
        std::cerr << "Failed. Press Ctrl-C to exit.\n";
        return;
    }

    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(task)->get_context());
    const void *body;
    resp->get_parsed_body(&body, &context->body_len);
    std::cerr << "url = " << context->url << ", len = " << context->body_len
              << "\n";
}

void parallelCallback(const ParallelWork *parallelWork) {
    std::string name;
    size_t body_len = 0;
    for (int i = 0; i < parallelWork->size(); ++i) {
        SeriesContext *context = static_cast<SeriesContext *>(
            parallelWork->series_at(i)->get_context());
        if (body_len < context->body_len) {
            name = context->url;
            body_len = context->body_len;
        }
        delete context;
    }

    std::cerr << "longest body_len  url = " << name
              << " body_len = " << body_len << "\n";

    WFRedisTask *redisTask =
        WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 10, nullptr);
    redisTask->get_req()->set_request("SET", {name, std::to_string(body_len)});
    series_of(parallelWork)->push_back(redisTask);
}

/* =============== test =============== */
void test0() {
    // 创建并行序列
    ParallelWork *parallelWork =
        Workflow::create_parallel_work(parallelCallback);
    // vector 存放需要访问的网站
    std::vector<std::string> urls = {
        "http://www.baidu.com", "http://www.jd.com", "http://www.taobao.com"};
    for (int i = 0; i < urls.size(); ++i) {
        // 创建任务
        WFHttpTask *http = WFTaskFactory::create_http_task(
            urls[i], REDIRECT_MAX, RETRY_MAX, httpCallBack); // http任务
        // 创建串行序列
        SeriesWork *series =
            Workflow::create_series_work(http, nullptr); // 序列包装http任务
        // 加入context
        SeriesContext *context = new SeriesContext;
        context->url = urls[i];
        series->set_context(context);
        // 添加到并行序列
        parallelWork->add_series(series);
    }

    parallelWork->start();

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
