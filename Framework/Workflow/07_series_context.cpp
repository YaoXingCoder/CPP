/*************************************************************************
    > File Name: 07_series_context.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月05日 星期六 21时41分14秒
    > Mail: JiaZiChunQiu@163.com
    > Title: Series 数据共享
    > Content:
 ************************************************************************/

#include <signal.h>

#include <iostream>
#include <string>
#include <unistd.h>

#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

#define REDIS_URL "redis://127.0.0.1:6379"
#define RETRY_MAX 5

struct SeriesContext {
    int id;
    std::string name;
};

static WFFacilities::WaitGroup waitGroup(1);
void sig_handler(int signo) { waitGroup.done(); }

void redis_task1(WFRedisTask *redisTask) {
    std::cout << "\n----------------redis_task1 begin-------------------\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(redisTask)->get_context());
    std::cout << "before id is " << context->id << ", name is " << context->name
              << ".\n";
    context->id = 200;
    context->name = "key1";
}
void redis_task2(WFRedisTask *redisTask) {
    std::cout << "\n----------------redis_task2 begin-------------------\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(redisTask)->get_context());
    std::cout << "before id is " << context->id << ", name is " << context->name
              << ".\n";
    context->id = 300;
    context->name = "key2";
}
void redis_task3(WFRedisTask *redisTask) {
    std::cout << "\n----------------redis_task3 begin-------------------\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(redisTask)->get_context());
    std::cout << "before id is " << context->id << ", name is " << context->name
              << ".\n";
    context->id = 400;
    context->name = "key3";
}

void series_callback(const SeriesWork *series) {
    std::cout << "\n----------------series_callback begin-------------------\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series->get_context());
    std::cout << "series callback id = " << context->id
              << " name = " << context->name << "\n";
    delete context;
}

/* =============== test =============== */
void test0() {
    // 任务1
    WFRedisTask *redisTask1 =
        WFTaskFactory::create_redis_task(REDIS_URL, RETRY_MAX, redis_task1);
    redisTask1->get_req()->set_request("set", {"key1", "value1"});

    // 任务2
    WFRedisTask *redisTask2 =
        WFTaskFactory::create_redis_task(REDIS_URL, RETRY_MAX, redis_task2);
    redisTask2->get_req()->set_request("set", {"key2", "value2"});

    // 任务3
    WFRedisTask *redisTask3 =
        WFTaskFactory::create_redis_task(REDIS_URL, RETRY_MAX, redis_task3);
    redisTask3->get_req()->set_request("set", {"key3", "value3"});

    // 创建序列
    SeriesWork *series = Workflow::create_series_work(redisTask1, nullptr);
    // series->push_back(redisTask1);
    series->push_back(redisTask2);
    series->push_back(redisTask3);

    // 创建共享数据结构
    SeriesContext *context = new SeriesContext;
    context->id = 100;
    context->name = "key";
    series->set_context(context); // 添加到序列中

    series->set_callback([context](const SeriesWork *series) {
        std::cout << "series callback id = " << context->id
                  << " name = " << context->name << "\n";
        delete context;
    });

    series->start(); // 执行
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
