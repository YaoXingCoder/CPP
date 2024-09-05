/*************************************************************************
    > File Name: rss.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月04日 星期三 21时52分37秒
    > Mail: JiaZiChunQiu@163.com
    > Title: RSS 文本文档解析存储
    > Content:
 ************************************************************************/

#include "rss.hh"
#include <tinyxml2.h>
#include <iostream>
#include <fstream>
#include <regex>
using namespace tinyxml2;

RssItem::RssItem(const std::string & str_title, const std::string & str_link, const std::string & str_description, const std::string & str_content)
: title(str_title)
, link(str_link)
, description(str_description)
, content(str_content)
{}

RssItem::RssItem(RssItem && other) 
: title(std::move(other.title))
, link(std::move(other.link))
, description(std::move(other.description))
, content(std::move(other.content))
{ std::cout << "移动" << std::endl; }

/* 默认构造, 初始化 vector 的容量 */
RssReader::RssReader(const int capacity) {
    _rss.reserve(capacity);
}

/* 处理 xml 文件, 并存入 vector 容器中 */
void RssReader::parseRss(const std::string & filename) {
    /* 载入xml文件 */
    XMLDocument doc;
    XMLError error = doc.LoadFile(filename.c_str());
    if( error != XMLError::XML_SUCCESS ) {
        std::cerr << "LoadFile error" << std::endl;
        std::cout << "ERROR : " << doc.ErrorStr() << std::endl;
        return;
    }

    /* 正则表达式处理 */
    std::regex html_regex("<[^>]+>");

    /* 定位节点 item */
    XMLElement *item = doc.RootElement()->FirstChildElement("channel")->FirstChildElement("item");

    /* 循环处理并存入 */
    while(item) {
        XMLElement *title = item->FirstChildElement("title");
        std::string str_title = title->GetText();

        XMLElement *link = item->FirstChildElement("link");
        std::string str_link = link->GetText();

        XMLElement *description = item->FirstChildElement("description");
        std::string str_description = std::regex_replace(description->GetText(), html_regex, "");

        XMLElement *content = item->FirstChildElement("content:encoded");
        std::string str_content = std::regex_replace(content->GetText(), html_regex, "");

        /* 寻找下个标签 */
        item = item->NextSiblingElement("item");

        /* 存入容器 */
        _rss.emplace_back(str_title, str_link, str_description, str_content);
    }

    /* int count = 1; */
    /* for ( RssItem & rss : _rss ) { */
    /*     std::cout << count << std::endl; */
    /*     std::cout << rss.title << std::endl; */
    /*     std::cout << rss.link << std::endl; */
    /*     ++count; */
    /* } */
}

/* 遍历 vector 容器输出内容到 文件 */
void RssReader::dump(const std::string & filename ) {
    /* 关联输出文件 */
    std::ofstream ofs(filename);
    if ( !ofs ) { 
        std::cerr << "ofs open error" << std::endl;
        return;
    }

   /* 循环遍历容器, 添加格式, 并输出到文件 */ 
    for ( std::size_t idx = 0; idx < _rss.size(); ++idx ) {
        ofs << "<doc>\n\t<docid>" << idx + 1
            << "</docid>\n\t<title>" << _rss[idx].title
            << "</title>\n\t<link>" << _rss[idx].link
            << "</link>\n\t<description>" << _rss[idx].description
            << "</description>\n\t<content>" << _rss[idx].content
            << "</content>\n</doc>" << '\n';
    }

    /* 关闭资源 */
    ofs.close();
}

