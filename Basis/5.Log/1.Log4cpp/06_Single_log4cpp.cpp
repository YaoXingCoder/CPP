/*************************************************************************
    > File Name: 06_Single_log4cpp.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 21时25分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式封装 log4cpp
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
using namespace log4cpp;

class Mylogger {
public:
    static Mylogger* getInstance() {
        if ( _pInstance == nullptr ) {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }

    void warn(const char* msg){
       _sub.warn(msg);
    }

    void error(const char* msg){
       _sub.error(msg);
    }

    void debug(const char* msg){
       _sub.debug(msg);
    }

    void info(const char* msg){
        _pInstance->_sub.info(msg);
    }

    static void destroy() {
        Category::shutdown();
        if( _pInstance != nullptr ) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

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

        /* 记录器添加目的地 */
        _sub.addAppender(appender);

        cout << "Mylogger initialization" << endl;
    }

    /* 析构 */
    ~Mylogger(){
        cout << "~Mylogger end" << endl;
    }

private:
    Category& _sub;
    static Mylogger* _pInstance;
};
Mylogger* Mylogger::_pInstance = nullptr;

void LogInfo(const char* msg) { Mylogger::getInstance()->info(msg);  Mylogger::destroy(); }
void LogError(const char* msg) { Mylogger::getInstance()->error(msg); Mylogger::destroy();}
void LogWarn(const char* msg) { Mylogger::getInstance()->warn(msg); Mylogger::destroy(); }
void LogDebug(const char* msg) { Mylogger::getInstance()->debug(msg); Mylogger::destroy(); }


/* ======================= 测试 ========================= */

void test01() {
    Mylogger* log = Mylogger::getInstance();

    log->info("The log is info message.");

    Mylogger::destroy();
}

void test02() {
    LogInfo("The log is info message.");
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
