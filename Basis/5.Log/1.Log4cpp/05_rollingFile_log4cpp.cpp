/*************************************************************************
    > File Name: 03_customize_log4cpp.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 22时37分29秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 写入到回卷文件
    > Content:
    >   1.了解回卷
 ************************************************************************/

#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using namespace log4cpp;

#define MAX_ROLL_FILESIZE 1024
#define MAX_ROLL_FILENUM 10

void test01() {
    /* 创建布局对象 */
    PatternLayout* ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d [%p] %c : %m%n");

    PatternLayout* ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d [%p] %c : %m%n");

    PatternLayout* ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d [%p] %c : %m%n");

    /* 创建目的地 */
    OstreamAppender* appender1 = new OstreamAppender("output", &cout);
    FileAppender* appender2 = new FileAppender("fileApp", "pattern.log");
    RollingFileAppender* appender3 = new RollingFileAppender("rollingApp", "roll.log", MAX_ROLL_FILESIZE, MAX_ROLL_FILENUM);
    
    /* 目的地绑定布局 */
    appender1->setLayout(ptn1);
    appender2->setLayout(ptn2);
    appender3->setLayout(ptn3);
    
    /* 创建记录器 */
    Category& root = Category::getRoot();
    /* Category& sub1 = Category::getInstance("sub1"); */

    /* 记录器设置优先级 */
    root.setPriority(Priority::DEBUG);

    /* 记录器添加目的地 */
    /* root.addAppender(appender1); */
    /* root.addAppender(appender2); */
    root.addAppender(appender3);

    /* 写入日志 */
    /* root << Priority::ERROR << "Streamed root error"; */

    int count = 30;
    while ( count > 0 ) {
        root.emerg("this is an emerg msg");
        root.fatal("this is a fatal msg");
        root.alert("this is an alert msg");
        root.crit("this is a crit msg");
        root.error("this is an error msg");
        root.warn("this is a warn msg");
        root.notice("this is a notice msg");
        root.info("this is an info msg");
        root.debug("this is a debug msg");
        count--;
    }

    /* 关闭资源 不需要主动调用*/
    Category::shutdown();
}

int main() {
    test01();
    return 0;
}
