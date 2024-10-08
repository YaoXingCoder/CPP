/*************************************************************************
    > File Name: 09_http_server.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月06日 星期日 11时29分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: http服务端 newTask
    > Content:
 ************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

#include <iostream>
#include <string>

#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>

struct SeriesContext {
    std::string url;
    WFHttpTask *serverTask; // 让newTask找到serverTask, 从而可以修改其响应
};

static WFFacilities::WaitGroup waitGroup(1);

void sig_handle(int signo) { waitGroup.done(); }

void serverTaskCallBack(WFHttpTask *httpTask) {
    std::cout << "\nserverTaskCallBack is called\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(httpTask)->get_context());
    protocol::HttpResponse *resp = httpTask->get_resp();
    size_t size = resp->get_output_body_size();
    if (httpTask->get_state() == WFT_STATE_SUCCESS) {
        std::cerr << "Http success\n";
    }
}

void newTaskCallBack(WFHttpTask *newTask) {
    std::cout << "\nnewTaskCallBack is called\n";

    int state = newTask->get_state();
    int error = newTask->get_error();
    switch (state) {
    case WFT_STATE_SYS_ERROR:
        std::cerr << "system error :" << strerror(error) << std::endl;
        break;
    case WFT_STATE_DNS_ERROR:
        std::cerr << "DNS error :" << gai_strerror(error) << std::endl;
        break;
    case WFT_STATE_SSL_ERROR:
        std::cerr << "SSL error :" << error << std::endl;
        break;
    case WFT_STATE_TASK_ERROR:
        std::cerr << "Task error :" << error << std::endl;
        break;
    case WFT_STATE_SUCCESS:
        break;
    }
    if (state != WFT_STATE_SUCCESS) {
        std::cerr << "Task failed!" << std::endl;
        return;
    }

    // 找到http任务响应体的内容
    protocol::HttpResponse *resp = newTask->get_resp();
    const void *body;
    size_t size;

    resp->get_parsed_body(&body, &size); // 获取响应体的首地址

    /* 获取序列中的 context */
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(newTask)->get_context());
    context->serverTask->set_callback(
        serverTaskCallBack); // 在序列结束之前,都可以设置服务端任务的回调
    protocol::HttpResponse *serverTaskResp;
    serverTaskResp = context->serverTask->get_resp(); // process 的 resp
    // const void *body_process;
    // size_t size_process;
    // context->serverTask->get_resp()->get_parsed_body(&body_process,
    //                                                  &size_process);
    // serverTaskResp->get_parsed_body(&body_process, &size_process);
    // serverTaskResp->append_output_body(body, size);

    // 将http任务的resp对象移动为服务端任务的resp对象
    *serverTaskResp = std::move(*resp); // process 的 resp 变为 newTask 的 resp
    serverTaskResp->append_output_body(body, size);
    body = nullptr;
    size = 0;
    serverTaskResp->get_parsed_body(&body, &size);
    fwrite(body, size, 1, stdout);
    fflush(stdout);
}

void process(WFHttpTask *serverTask) {
    std::cout << "\nprocess is called\n";
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(stderr, "process start %ld.%06ld\n", tv.tv_sec, tv.tv_usec);

    /* 设置服务端任务的回调函数,这个回调函数会在序列执行 */
    serverTask->set_callback(
        serverTaskCallBack); // 仍在process的序列中, 只是序列中的最后一个任务

    /*
        将服务端任务的指针存入序列的上下文当中
        值得注意的是,任务对象会在任务的回调函数执行完成之后析构
    */
    protocol::HttpRequest *req = serverTask->get_req();
    SeriesWork *series = series_of(serverTask); // 找到serverTask所在的序列
    SeriesContext *context = new SeriesContext;
    context->serverTask = serverTask; // 把第一个httpTask任务的指针写入到上下文
    context->url = "http://www.baidu.com";
    series->set_context(static_cast<void *>(context)); // 设置序列的上下文

    /*
        在序列的回调函数中去销毁context
        在process序列结束后执行该lambda表达式
    */
    series->set_callback([](const SeriesWork *series) {
        std::cout << "\nlambda is called\n";
        struct timeval tv;
        gettimeofday(&tv, NULL);
        fprintf(stderr, "lambda %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
        delete (SeriesContext *)series->get_context(); // 销毁
    });

    /*
        创建一个访问目标服务器的http任务, 并且加入到服务端任务所在的序列之中
    */
    WFHttpTask *newTask = WFTaskFactory::create_http_task(
        "http://www.baidu.com", 5, 2, newTaskCallBack);
    series->push_back(newTask); // 在process序列中, 只是在 process之后添加,
                                // process的callback之前
    gettimeofday(&tv, NULL);
    fprintf(stderr, "process end %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
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
