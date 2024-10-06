/*************************************************************************
    > File Name: 03_redis_task.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月05日 星期六 17时51分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 串行
    > Content:
 ************************************************************************/

#include <signal.h>

#include <iostream>
#include <string>
#include <vector>

#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

#define RETRY_MAX 5

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signo) { waitGroup.done(); }

void redisCallback(WFRedisTask *redisTask) {

    protocol::RedisRequest *req = redisTask->get_req();    // 获取请求
    protocol::RedisResponse *resp = redisTask->get_resp(); // 获取响应
    protocol::RedisValue val; // 获取redis任务的返回结果
    int state = redisTask->get_state();
    int error = redisTask->get_error();
    switch (state) {
    case WFT_STATE_SYS_ERROR:
        std::cerr << "System error : " << strerror(error) << "\n";
        break;
    case WFT_STATE_DNS_ERROR:
        std::cerr << "DNS error : " << gai_strerror(error) << "\n";
        break;
    case WFT_STATE_SSL_ERROR:
        std::cerr << "SSL error\n";
        break;
    case WFT_STATE_TASK_ERROR:
        std::cerr << "Task error\n";
        break;
    case WFT_STATE_SUCCESS:
        resp->get_result(val); // 保存执行结果
        if (val.is_error()) {
            std::cerr << "Error reply\n";
            state = WFT_STATE_TASK_ERROR;
        }
        break;
    }

    /* 获取请求数据 */
    std::string command; // 获取请求命令
    req->get_command(command);
    std::cout << "command is " << command << "\t";
    std::vector<std::string> params;
    req->get_params(params); // 请求命令参数
    for (std::string str : params) {
        std::cout << "params is " << str << "\t";
    }
    std::cout << "\n";

    if (command == "get") {
        if (val.is_string()) {
            std::cout << "Redis GET success. value = " << val.string_value()
                      << "\n";
        } else if (val.is_array()) {
            for (int i = 0; i < val.arr_size(); ++i) {
                protocol::RedisValue &ele = val.arr_at(i);
                // auto ele = val.arr_at(i);
                std::cout << "value = " << ele.string_value() << "\t";
            }
            std::cout << "\n";
        } else {
            std::cerr << "Error: Not a string value.\n";
        }
    }

    if (state != WFT_STATE_SUCCESS) {
        std::cerr << "Failed. Press Ctrl-C to exit.\n";
        return;
    }

    std::cout << "\n\n";
}

/* =============== test =============== */
void test0() {
    std::string url("redis://127.0.0.1:6379");
    /* 先执行 set */
    // WFRedisTask *redisTask0 =
    //     WFTaskFactory::create_redis_task(url, RETRY_MAX, redisCallback);
    // protocol::RedisRequest *redisReq0 = redisTask0->get_req(); // 获取请求
    // redisReq0->set_request("select", {"1"});                   // select

    /* 先执行 set */
    WFRedisTask *redisTask1 =
        WFTaskFactory::create_redis_task(url, RETRY_MAX, redisCallback);
    protocol::RedisRequest *redisReq1 = redisTask1->get_req(); // 获取请求
    redisReq1->set_request("set", {"hi", "world"});            // set

    /* 再执行 get */
    WFRedisTask *redisTask2 =
        WFTaskFactory::create_redis_task(url, RETRY_MAX, redisCallback);
    protocol::RedisRequest *redisReq2 = redisTask2->get_req(); // 获取请求
    redisReq2->set_request("get", {"hi"});                     // get

    /* 将两个任务串行 */
    SeriesWork *series =
        Workflow::create_series_work(redisTask1, nullptr); // 创建序列
    series->push_back(redisTask2);                         // 添加任务
    series->start();

    /* 等待任务结束 */
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
