/*************************************************************************
    > File Name: 03_redis_task.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月05日 星期六 17时51分08秒
    > Mail: JiaZiChunQiu@163.com
    > Title: redis_task 使用
    > Content:
 ************************************************************************/

#include <signal.h>

#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>

#define RETRY_MAX 5

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signo) { waitGroup.done(); }

/* =============== test =============== */
void test0() {
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", RETRY_MAX, nullptr);
    protocol::RedisRequest *redisReq = redisTask->get_req();
    redisReq->set_request("set", {"hello", "world"});
    redisTask->start();
    waitGroup.wait();
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handler);
    test0();
    return 0;
}
