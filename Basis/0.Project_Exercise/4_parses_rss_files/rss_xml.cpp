/*************************************************************************
    > File Name: rss_parse.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 22时59分38秒
    > Mail: JiaZiChunQiu@163.com
    > Title: RSS文件解析
    > Content:
 ************************************************************************/

#include "tinyxml2.h"
#include "rss_xml.hh"
#include <iostream>
#include <regex>
#include <string>
using std::cout;
using std::endl;
using std::regex;
using std::ofstream;
using std::string;
using std::regex_replace;
using namespace tinyxml2;

RssReader::RssReader(const int capacity)
{ _rss.reserve(capacity);}

void RssReader::parseRss() {
    /* 关联文件 */
    XMLDocument doc;
    XMLError error = doc.LoadFile(FILENAME_XML);
    if (error != XMLError::XML_SUCCESS) {
        std::cout << "Error: " << doc.ErrorStr() << std::endl;
		return;
    }

    /* 正则表达式 */
    regex reg("<[^>]+>");

    /* 关联输出文件 */
    XMLDocument doc_out;
    XMLElement* root = doc_out.NewElement("doc");
    doc_out.InsertFirstChild(root);

    /* docid */
    int docid_count = 1;
    XMLElement* docid = doc_out.NewElement("docid");
    docid->SetText(docid_count);
    root->InsertEndChild(docid);

    /* 先处理 channel */
    XMLElement* channelEle = doc.RootElement()->FirstChildElement("channel");

    /* title */
    XMLElement* titleEle = channelEle->FirstChildElement("title");
    XMLElement* title_out = doc_out.NewElement("title");
    title_out->SetText(titleEle->GetText());
    root->InsertEndChild(title_out);

    /* link */
    XMLElement* linkEle = channelEle->FirstChildElement("link");
    XMLElement* link_out = doc_out.NewElement("link");
    link_out->SetText(linkEle->GetText());
    root->InsertEndChild(link_out);

    /* description */
    XMLElement* descEle = channelEle->FirstChildElement("description");
    XMLElement* desp_out = doc_out.NewElement("description");
    desp_out->SetText(regex_replace(descEle->GetText(), reg, "").c_str());;
    root->InsertEndChild(desp_out);

    /* content */
    XMLElement* content_out = doc_out.NewElement("content");

    /* item 的树形结构 */
    XMLElement* itemEle = channelEle->FirstChildElement("item");
    XMLElement* contentEle;

    /* 处理item */
    while(itemEle != nullptr ) { 
        /* cout << endl <<  "====== start ======" << endl; */
        /* 添加根节点 */
        root = doc_out.NewElement("doc");
        doc_out.InsertEndChild(root);

        /* docid */
        ++docid_count;
        docid = doc_out.NewElement("docid");
        docid->SetText(docid_count);
        root->InsertEndChild(docid);

        /* title */
        titleEle = itemEle->FirstChildElement("title");
        title_out = doc_out.NewElement("title");
        title_out->SetText(titleEle->GetText());
        root->InsertEndChild(title_out);

        /* link */
        linkEle = itemEle->FirstChildElement("link");
        link_out = doc_out.NewElement("link");
        link_out->SetText(linkEle->GetText());
        root->InsertEndChild(link_out);

        /* description */
        descEle = itemEle->FirstChildElement("description");
        desp_out = doc_out.NewElement("description");
        /* desp_out->SetText(descEle->GetText()); */
        desp_out->SetText(regex_replace(descEle->GetText(), reg, "").c_str());;
        root->InsertEndChild(desp_out);

        /* content */
        contentEle = itemEle->FirstChildElement("content:encoded");
        content_out = doc_out.NewElement("content");
        /* content_out->SetText(contentEle->GetText()); */
        content_out->SetText(regex_replace(contentEle->GetText(), reg, "").c_str());;
        root->InsertEndChild(content_out);

        /* cout << endl <<  "====== end ======" << endl; */

        /* 兄弟节点 */
        itemEle = itemEle->NextSiblingElement("item");
    }

    /* 保存到文件 */
    doc_out.SaveFile(FILENAME_OUTPUT);
}
