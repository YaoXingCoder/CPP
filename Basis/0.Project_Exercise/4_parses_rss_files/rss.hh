#ifndef __RSS_XML_H
#define __RSS_XML_H

#include <string>
#include <vector>

#define FILENAME_INPUT "coolshell.xml"
#define FILENAME_OUTPUT "pagelib.txt"

/* 接收文件格式 */
struct RssItem {
public:
    RssItem(const std::string &, const std::string &, const std::string &, const std::string &);
    RssItem(RssItem &&);
public:
    std::string title;
    std::string link;
    std::string description;
    std::string content;
};

/* RssReader 类 */
class RssReader {
public:
    RssReader(const int capacity = _init);
    void parseRss(const std::string &);
    void dump(const std::string &);
private:
    std::vector<RssItem> _rss;
    static const int _init = 16;
};

#endif
