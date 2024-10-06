/*************************************************************************
    > File Name: 03_redis_task.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月05日 星期六 17时51分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: redis_task callback 使用
    > Content:
 ************************************************************************/

#include <signal.h>

#include <iostream>
#include <vector>
#include <workflow/RedisMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>

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

    if (command == "get" || command == "hget" || command == "hgetall") {
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

    std::cout << "Ok\n";
}

/* =============== test =============== */
void test0() {
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", RETRY_MAX, nullptr);
    protocol::RedisRequest *redisReq = redisTask->get_req();
    redisReq->set_request("set", {"hi", "world"});
    redisTask->start();
    waitGroup.wait();
}

void test1() {
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", RETRY_MAX, redisCallback);
    protocol::RedisRequest *redisReq = redisTask->get_req();
    // redisReq->set_request("set", {"hi4", "world"}); // set
    // redisReq->set_request("get", {"hi"}); // get
    // redisReq->set_request("hset", {"HMAP1", "key1", "value1"});
    // redisReq->set_request("hget", {"HMAP1", "key1"});
    redisReq->set_request("hgetall", {"HMAP1"});
    redisTask->start();
    waitGroup.wait();
}

/* =============== main =============== */
int main(int argc, char *argv[]) {
    std::cout << "start\n";
    signal(SIGINT, sig_handler);
    // test0();
    test1();
    std::cout << "finished\n";
    return 0;
}
