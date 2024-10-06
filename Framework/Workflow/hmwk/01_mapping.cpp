/*************************************************************************
    > File Name: 01_hmwk.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月06日 星期日 08时57分41秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
    >
 存在下列的redis键值映射关系，使用workflow的redis任务和序列，假如只知道"x1"，如何找到最终的"100"？
    >    "x1" --> "x2"
    >    "x2" --> "x3"
    >    "x3" --> "x4"
    >    "x4" --> "100"
 ************************************************************************/

#include <signal.h>

#include <iostream>
#include <string>

#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

#define REDIS_URL "redis://127.0.0.1:6379"
#define RETRY_MAX 2

static WFFacilities::WaitGroup waitGroup(1);
void sig_handler(int signo) { waitGroup.done(); }

void redisCallBack(WFRedisTask *redisTask) {
    protocol::RedisResponse *resp = redisTask->get_resp();
    protocol::RedisRequest *req = redisTask->get_req();
    protocol::RedisValue val;
    std::string cmd;
    req->get_command(cmd); // 获取命令
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
    if (cmd == "get") {
        if (val.is_string() && val.string_value() != "100") {
            WFRedisTask *next = WFTaskFactory::create_redis_task(
                REDIS_URL, RETRY_MAX, redisCallBack);
            next->get_req()->set_request("get", {val.string_value()});
            series_of(redisTask)->push_back(next);
        }
    } else {
        std::cerr << "100 has Founded\n";
        return;
    }

    std::cout << "RedisTask find " << val.string_value() << "\n";
}

/* =============== test =============== */
void test0() {
    WFRedisTask *redisTask =
        WFTaskFactory::create_redis_task(REDIS_URL, RETRY_MAX, redisCallBack);
    redisTask->get_req()->set_request("get", {"x1"});

    redisTask->start();
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
