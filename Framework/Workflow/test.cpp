/*************************************************************************
    > File Name: test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月05日 星期六 22时23分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
// wait_group 实现有条件的等待
#include <iostream>
#include <signal.h>
#include <string>
#include <unistd.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
using std::cerr;
using std::cout;
using std::string;
struct SeriesContext {
    int id;
    string name;
};
static WFFacilities::WaitGroup waitGroup(1);
void handler(int signum) {
    cout << "done\n";
    waitGroup.done();
}
void redisCallback1(WFRedisTask *redisTask) {
    cerr << "callback 1 begin\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(redisTask)->get_context());
    cerr << "before id = " << context->id << " name = " << context->name
         << "\n";
    context->id = 1001;
    context->name = "task1";
    cerr << "after id = " << context->id << " name = " << context->name << "\n";
    cerr << "callback 1 end!\n";
}
void redisCallback2(WFRedisTask *redisTask) {
    cerr << "callback 2 begin\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(redisTask)->get_context());
    cerr << "before id = " << context->id << " name = " << context->name
         << "\n";
    context->id = 1002;
    context->name = "task2";
    cerr << "after id = " << context->id << " name = " << context->name << "\n";
    cerr << "callback 2 end!\n";
}
void redisCallback3(WFRedisTask *redisTask) {
    cerr << "callback 3 begin\n";
    SeriesContext *context =
        static_cast<SeriesContext *>(series_of(redisTask)->get_context());
    cerr << "before id = " << context->id << " name = " << context->name
         << "\n";
    cerr << "callback 3 end!\n";
}
void seriesCallback(const SeriesWork *series) {
    SeriesContext *context =
        static_cast<SeriesContext *>(series->get_context());
    cerr << "series callback id = " << context->id
         << " name = " << context->name << "\n";
    delete context;
}
int main() {
    signal(SIGINT, handler);
    // 创建任务
    WFRedisTask *redisTask1 = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", 10, redisCallback1);
    // 找到请求
    redisTask1->get_req()->set_request("SET", {"key", "123"});
    // 创建任务
    WFRedisTask *redisTask2 = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", 10, redisCallback2);
    // 找到请求
    redisTask2->get_req()->set_request("SET", {"key", "123"});
    // 创建任务
    WFRedisTask *redisTask3 = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", 10, redisCallback3);
    // 找到请求
    redisTask3->get_req()->set_request("SET", {"key", "123"});

    // 创建序列
    SeriesWork *series = Workflow::create_series_work(redisTask1, nullptr);
    series->push_back(redisTask2);
    series->push_back(redisTask3);

    // 构造一个SeriesContext对象
    SeriesContext *context = new SeriesContext;
    context->id = 1000;
    context->name = "main";
    // 将context的地址存入序列中
    series->set_context(context);

    series->set_callback(seriesCallback);
    series->set_callback([](const SeriesWork *series) {
        SeriesContext *context =
            static_cast<SeriesContext *>(series->get_context());
        cerr << "series callback id = " << context->id
             << " name = " << context->name << "\n";
        delete context;
    });
    series->set_callback([context](const SeriesWork *series) {
        cerr << "series callback id = " << context->id
             << " name = " << context->name << "\n";
        delete context;
    });
    // 将序列交给框架
    series->start();

    waitGroup.wait();
    cout << "finish!\n";
    int i = 1;
}
