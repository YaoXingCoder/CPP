/*************************************************************************
    > File Name: 06_Single_log4cpp.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 21时25分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式封装 log4cpp
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
using namespace log4cpp;


#define addPrefix(msg)                                  \
        string(" [ ").append(__FILE__)                  \
        .append(" : ").append(__func__)                 \
        .append(" : ").append(std::to_string(__LINE__)) \
        .append(" ] ").append(msg).c_str()              \

#define LogWarn(msg) {                                  \
    Mylogger::getInstance().warn(addPrefix(msg));       \
}

class Mylogger {
public:
    static Mylogger& getInstance() {
        static Mylogger mylog;
        return mylog;
    }

    void warn(const char* msg){ _sub.warn(msg); }
    void error(const char* msg){ _sub.error(msg); }
    void debug(const char* msg){ _sub.debug(msg); }
    void info(const char* msg){ _sub.info(msg); }
    
    Mylogger(const Mylogger& rhs) = delete;
    Mylogger& operator=(const Mylogger& rhs) = delete;
private:
    /* 初始化 */
    Mylogger()
    : _sub(Category::getRoot().getInstance("_sub"))
    {
        /* 创建布局 */
        PatternLayout* ptn = new PatternLayout();
        ptn->setConversionPattern("%d [%p] %c : %m%n");
        /* 创建目的地 */
        OstreamAppender* appender = new OstreamAppender("output", &cout);
        /* 绑定布局 */
        appender->setLayout(ptn);
        /* 设置优先级 */
        _sub.setPriority(Priority::DEBUG);
        _sub.addAppender(appender);
        cout << "Mylogger initialization" << endl;
    }

    /* 析构 */
    ~Mylogger(){
        cout << "~Mylogger end" << endl;
    }
private:
    Category& _sub;
};

/* string addPrefix(const char* msg) { */
/*     return string(" [ ").append(__FILE__) */
/*         .append(" : ").append(__func__) */
/*         .append(" : ").append(std::to_string(__LINE__)) */
/*         .append(" ] ").append(msg).c_str(); */
/* } */

/* ======================= 测试 ========================= */

void test01() {
    Mylogger& log = Mylogger::getInstance();
    log.info("The log is info message");
}

void test02() {
    LogWarn("This is a warn message.");
    LogWarn("This is a warn message.");
    LogWarn("This is a warn message.");
}

/* ======================= main  ========================= */

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
