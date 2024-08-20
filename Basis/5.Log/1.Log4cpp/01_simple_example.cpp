/*************************************************************************
    > File Name: 01_simple_example.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 14时32分00秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 了解 log4cpp
    > Content: 流程为
    >   1.创建目的地对象
    >   2.目的地绑定布局
    >   3.创建记录器
    >   4.记录器设置优先级
    >   5.记录器添加目的地
    >   6.写入日志
 ************************************************************************/
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

using namespace log4cpp;

int main(int argc, char** argv) {
    /* 可以传入string 对象 , 也可以 const char* 
     * 这里 用 Appender 指向 new OstreamAppender 
     * 使用 基类指针 指向 派生类对象
     * 直接使用 OstreamAppender 指向也可 或者 auto
     * */
	/* log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout); */

    /* 1. 创建目的地地址 
     * 设置的为终端的目的地地址
     * OstreamAppender 用于终端输出
     * 第一个参数目的地名字, 第二个ostream* 此处传入 &cout, 目的设为终端 
     * */
	OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);
    /* 2. 目的地绑定布局
     * 设置布局（格式）, 将目的地与与日志布局绑定 */
	appender1->setLayout(new BasicLayout()); /* 该布局为基本布局 */

    /* 1. 创建目的地地址
     * 设置的保存到文件的目的地址 
     * FileAppender 通常用于保存到文件
     * 第一个参数: 目的地名字
     * 第二个参数: 保存文件的文件名
     * */
	Appender *appender2 = new FileAppender("default", "program.log");
    /* 2. 目的地绑定布局 */
	appender2->setLayout(new BasicLayout());


    /* 3. 创建记录器
     * getRoot 创建 root节点 的 Category 类似单例模式
     * 重复调用 getRoot 只会返回同一个实例
     * 使用 Catagory 类型的变量 root 进行绑定 */
	Category& root = Category::getRoot();
    /* 4. 记录器设置优先级
     * 低于该等级的不会记录
     */
	root.setPriority(Priority::WARN);
    /* 5. 记录器添加目的地
     * 该 root记录器 添加目的地 appender1, 输出到终端 */
	root.addAppender(appender1);


    /* 3. 创建记录器 (子记录器)
     * getInstance 创建 root 节点的 Category对象 的下一级的叶子节点
     * 叶子节点也是 Category对象
     * 会继承 root节点 的优先级和目的地
     */
	Category& sub1 = Category::getInstance(std::string("sub1"));
    /* 5. 记录器添加目的地
     * 该子节点已经继承 root 的 目的地 和 优先加 
     * 该 sub1.addAppender 为另外添加的 目的地 输出到文件, 同时输出到终端
     * */
	sub1.addAppender(appender2);


    /* 6. 写入日志 */
	// use of functions for logging messages
    /* 记录器.函数(记录信息), 函数也为信息的优先级 */ 
	root.error("root error"); 
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << Priority::ERROR << "Streamed root error";
	root << Priority::INFO << "Streamed root info";
	sub1 << Priority::ERROR << "Streamed sub1 error";
	sub1 << Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}
