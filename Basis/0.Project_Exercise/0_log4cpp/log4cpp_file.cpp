/*************************************************************************
    > File Name: log4cpp_file.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 09时59分26秒
    > Mail: JiaZiChunQiu@163.com
    > Title: log4cpp 输出的日志信息到终端和文件，文件中最好能有文件的名字，函数的名字及其所在的行号
    > Content: 
 ************************************************************************/

#include "log4cpp_file.hh"
#include <iostream>
#include <string>

/* 初始化 */
Mylogger * Mylogger::_pMylogger = nullptr;
Mylogger::AutoRelease Mylogger::AutoRelease::_ar;

Mylogger::AutoRelease::~AutoRelease() {
    if ( _pMylogger != nullptr ) {
        delete _pMylogger;
        _pMylogger = nullptr;
    }
}

/* 构造 */
Mylogger::Mylogger() : _sub(log4cpp::Category::getRoot().getInstance("_sub")) {
    log4cpp::PatternLayout *ptlt_file = new log4cpp::PatternLayout();
    ptlt_file->setConversionPattern("%d [%p] %c : %m%n");
    log4cpp::PatternLayout *ptlt_terminal = new log4cpp::PatternLayout();
    ptlt_terminal->setConversionPattern("%d [%p] %c : %m%n");

    log4cpp::OstreamAppender * appender_terminal = new log4cpp::OstreamAppender("output", &std::cout);
    appender_terminal->setLayout(ptlt_terminal);
    log4cpp::RollingFileAppender * appender_rolling = new log4cpp::RollingFileAppender("rollAppender", FILENAME_ROLLING, MAX_ROLL_FILESIZE, MAX_ROLL_FILENUM);
    appender_rolling->setLayout(ptlt_file);

    _sub.addAppender(appender_rolling);
    _sub.addAppender(appender_terminal);

    _sub.setPriority(log4cpp::Priority::INFO);
}

/* 析构 */
Mylogger::~Mylogger() { std::cout << "end of Mylogger" << std::endl; }

/* 获取实例 */
Mylogger * Mylogger::getInstance() {
    if ( _pMylogger == nullptr ) { _pMylogger = new Mylogger(); }
    return _pMylogger;
}

/* 销毁 */
void Mylogger::destroy() {
    if ( _pMylogger != nullptr ) {
       delete _pMylogger;
       _pMylogger = nullptr;
    }
}

/* static std::string addPrefix(const char* msg) { */
/*     return std::string("[ ").append(__FILE__) */
/*         .append(" : ").append(__func__) */
/*         .append(" : ").append(std::to_string(__LINE__)) */
/*         .append(" ] ").append(msg); */
/* } */

/* 日志输出 */
void Mylogger::info(const char * msg) {
    _pMylogger->_sub.warn(msg);
}
void Mylogger::notice(const char * msg) {
    _pMylogger->_sub.warn(msg);
}
void Mylogger::warn(const char * msg) {
    _pMylogger->_sub.warn(msg);
}
void Mylogger::error(const char * msg) {
    _pMylogger->_sub.error(msg);
}
void Mylogger::crit(const char * msg) {
    _pMylogger->_sub.crit(msg);
}
void Mylogger::alert(const char * msg) {
    _pMylogger->_sub.alert(msg);
}
void Mylogger::emerg(const char* msg) {
    _pMylogger->_sub.emerg(msg);
}

