/*************************************************************************
    > File Name: 02_log4cpp_encapsulation.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 21时24分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 将log4cpp 进行封装 只提供一个接口
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Mylogger {
public:
	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);
	
private:
	Mylogger();
	~Mylogger();
    
private:
};


void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
}

void test1() {
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

int main (int argc, char* argv[]) {

    return 0;
}
