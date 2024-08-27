/*************************************************************************
    > File Name: rss_parse.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 22时59分38秒
    > Mail: JiaZiChunQiu@163.com
    > Title: RSS文件解析
    > Content:
 ************************************************************************/

#include "tinyxml2.h"
#include "rss_parse.hh"
#include <iostream>
using std::cout;
using std::endl;
using namespace tinyxml2;

RssReader::RssReader(const int capacity)
: _rss(capacity)
{
    cout << "RssReader() 构造" << endl;
}

void RssReader::parseRss() {
    /* 关联文件 */
    XMLDocument doc;
    XMLError error = doc.LoadFile("coolshell.xml");
    if (error != XMLError::XML_SUCCESS) {
        std::cout << "Error: " << doc.ErrorStr() << std::endl;
		return;
    }

    XMLElement* rootELement = doc.RootElement();
    XMLElement* channelEle = rootELement->FirstChildElement("channel");
    struct RssItem rssItem;

    cout << "====== start ======" << endl;
    while(channelEle != nullptr) { 
        memset(&rssItem, 0, sizeof(rssItem));
        /* 处理 */
        /* title */
        XMLElement* titleEle = channelEle->FirstChildElement("title");
        rssItem.title = titleEle->GetText(); 

        /* link */
        XMLElement* linkEle = channelEle->FirstChildElement("link");
        rssItem.link = linkEle->GetText(); 

        /* description */
        XMLElement* descEle = channelEle->FirstChildElement("description");
        rssItem.description = descEle->GetText();

        /* content */
        /* XMLElement* contentEle = channelEle->FirstChildElement("content"); */
        /* rssItem.content = contentEle->GetText(); */

        cout << rssItem.title << endl;
        cout << rssItem.link << endl;
        cout << rssItem.description << endl;
        cout << rssItem.content << endl;
        cout << "-------------" << endl;
        _rss.push_back(rssItem); 
        channelEle = channelEle->NextSiblingElement("channel");
    }

    cout << "====== end ======" << endl;

}

int main() {
    RssReader().parseRss();
    return 0;
}
