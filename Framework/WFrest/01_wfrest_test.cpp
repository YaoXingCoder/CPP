/*************************************************************************
    > File Name: 01_wfrest_test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月08日 星期二 21时04分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title: wfrest 使用
    > Content:
 ************************************************************************/

#include <signal.h>

#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>

#include <iostream>

static WFFacilities::WaitGroup waitGroup(1);
void handler(int signum) {
    std::cout << "done\n";
    waitGroup.done();
}

/* =============== test =============== */
void test0() {
    /* 构造了一个server对象 */
    wfrest::HttpServer server;

    // server.GET("/", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
    //     std::string req_body(req->body());
    //     resp->String(req_body);
    // });

    server.GET("/hello",
               [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
                   resp->append_output_body("hello");
               });

    server.POST("/world",
                [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
                    resp->append_output_body("world");
                });

    /* map<string, string> */
    server.GET("/query",
               [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
                   // http://192.168.225.129:8888/query?wd=123&content=q
                   // 不带 & 符号的 auto 会触发拷贝
                   // auto queryMap = req->query_list();
                   // 可以看为 map<string, string>
                   auto &queryMap = req->query_list();
                   for (auto pair : queryMap) {
                       std::cout << "first = " << pair.first
                                 << " second = " << pair.second << "\n";
                   }
               });
    /* 与query类似 只是在body中 */
    server.POST("/urlencoded",
                [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
                    auto &urlencodedMap = req->form_kv();
                    for (auto &pair : urlencodedMap) {
                        std::cout << "first = " << pair.first
                                  << " second = " << pair.second << "\n";
                    }
                });

    /* form-data map<string ,pair<string, string>> */
    server.POST(
        "/form_data", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
            std::cout << "form_data is called\n";
            auto &formdataMap = req->form();
            for (auto pair : formdataMap) {
                std::cout << "first = " << pair.first
                          << " second.first = " << pair.second.first
                          << " second.second = " << pair.second.second << "\n";
            }
        });

    server.GET("/upload",
               [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
                   resp->File("index.html");
               });

    server.POST(
        "/upload", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp) {
            auto &formdataMap = req->form_kv();
            for (auto pair : formdataMap) {
                std::cout << "first = "
                          << pair.first
                          //   << " second.first = " << pair.second.first
                          << " second.second = " << pair.second << "\n";
            }
        });

    server.POST("/login", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp,
                             SeriesWork *series) {
        // http://192.168.72.128:1234/login?username=niqiu&password=123
        auto queryMap = req->query_list();
        std::string username = queryMap["username"];
        std::string password = queryMap["password"];
        WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
            "redis://127.0.0.1:6379", 10,
            [username, password, resp](WFRedisTask *redisTask) {
                protocol::RedisValue value;
                redisTask->get_resp()->get_result(value);
                if (value.is_string() && value.string_value() == password) {
                    resp->String("success");
                } else {
                    resp->String("fail");
                }
            });
        redisTask->get_req()->set_request("hget", {"login", username});
        series->push_back(redisTask);
    });

    server.Static("/", "./index.html");
    server.Static("/static", "./hello.html");

    server.ROUTE()

    if (server.track().start(8888) == 0) {
        server.list_routes(); // list_routes 列出支持的方法和路径,
                              // 仅限于track()被调用时生效
        waitGroup.wait();     // 阻塞住主线程
        server.stop();
    } else {
        perror("server start");
        return;
    }
}

/* =============== main =============== */
int main(int argc, char *argv[]) {
    std::cout << "start\n";
    signal(SIGINT, handler);
    test0();
    std::cout << "finished\n";
    return 0;
}
