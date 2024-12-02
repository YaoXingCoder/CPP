#ifndef __LOG4CPP_OUT_H
#define __LOG4CPP_OUT_H

#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>

#define MAX_ROLL_FILESIZE 1024 * 1024
#define MAX_ROLL_FILENUM 4
#define FILENAME_ROLLING "roll.log"


#define addPrefix(msg)                                  \
    std::string("[ ").append(__FILE__)                  \
        .append(" : ").append(__func__)                 \
        .append(" : ").append(std::to_string(__LINE__)) \
        .append(" ] ").append(msg).c_str()              


#define LogInfo(msg) {                                  \
    Mylogger::getInstance()->info(addPrefix(msg));      \
}
#define LogNotice(msg) {                                \
    Mylogger::getInstance()->notice(addPrefix(msg));    \
}
#define LogWarn(msg) {                                  \
    Mylogger::getInstance()->warn(addPrefix(msg));      \
}
#define LogError(msg) {                                 \
    Mylogger::getInstance()->error(addPrefix(msg));     \
}
#define LogCrit(msg) {                                  \
    Mylogger::getInstance()->crit(addPrefix(msg));      \
}
#define LogAlert(msg) {                                 \
    Mylogger::getInstance()->Alert(addPrefix(msg));     \
}
#define LogEmerg(msg) {                                 \
    Mylogger::getInstance()->emerg(addPrefix(msg));     \
}


class Mylogger {
public:
    class AutoRelease{
    public:
        ~AutoRelease();
    private:
        static AutoRelease _ar;
    };
public:
    static Mylogger * getInstance();
    static void destroy();

    void info(const char * );
    void notice(const char * );
    void warn(const char * );
    void error(const char * );
    void crit(const char * );
    void alert(const char * );
    void emerg(const char * );
private:
    Mylogger();
    ~Mylogger();
    Mylogger(const Mylogger & ) = delete;
    Mylogger & operator=(const Mylogger &) = delete;
private:
    log4cpp::Category & _sub;
    static Mylogger * _pMylogger;
};

#endif
