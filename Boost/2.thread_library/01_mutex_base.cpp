/*************************************************************************
    > File Name: 01_mutex_base.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月14日 星期六 10时45分51秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

int gCount = 0;
mutex mtx; // 初始化互斥锁
void threadFunc() {
    for (int idx = 0; idx < 1000000; ++idx) {
        mtx.lock();   // 上锁
        ++gCount;     // 共享资源
        mtx.unlock(); // 解锁
    }
}
int main(int argc, char *argv[]) {
    thread th1(threadFunc);
    thread th2(threadFunc);
    th1.join(); // 等待线程结束
    th2.join(); // 等待线程结束
    cout << "gCount = " << gCount << endl;
    return 0;
}
