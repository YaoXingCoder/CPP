#include "CloudiskServer.h"
#include <iostream>

int main() {
    CloudiskServer cloudiskServer(1); // 创建服务对象
    cloudiskServer.loadModules();     // 启动任务
    cloudiskServer.start(8888);       // 开启服务端口监听
    return 0;
}
