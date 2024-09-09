/*************************************************************************
    > File Name: textQuery.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 14时38分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 文本查询
    > Content:
    >   1.该程序将读取用户指定的任意文本文件【当前目录下的china_daily.txt】，
    >   2.允许用户从该文件中查找单词。查询的结果是该单词出现的次数
    >   3.并列出每次出现所在的行。
    >   4.果某单词在同一行中多次出现，程序将只显示该行一次。
    >   5.行号按升序显示。
    示例:
    ---------------------------------------------
    element occurs 125 times.
    (line 62) element with a given key.
    (line 64) second element with the same key.
    (line 153) element |==| operator.
    (line 250) the element type.
    (line 398) corresponding element.
    ---------------------------------------------
 ************************************************************************/

#include "textQuery.hh"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

static void dealLine(std::string &);
std::string & identified_words(std::string &, const std::string &);

TextQuery::TextQuery(const int vecSize)  {
    _lines.reserve(vecSize);
}

void TextQuery::readFile(const std::string &filename) {
    /* 关联文件 */
    std::ifstream ifs(filename);
    if( !ifs ) {
        std::cerr << "ifs open error" << std::endl;
        return;
    }

    /* 读文件 */
    std::string line;
    int lineNum = 1;
    while(std::getline(ifs, line)) {
        /* 处理每行 */
        _lines.push_back(line); // 先将一行添加到 _lines

        /* 处理一行中的内容 */
        dealLine(line);

        /* 处理单词 */
        std::istringstream iss(line);
        std::string word;
        while(iss >> word) {
            ++_dict[word]; // 没有 word, 自动添加, 如果有则计数器 + 1 
            _wordNum[word].insert(lineNum); // map 没有 word 会自动添加, 如果相同的lineNum, 不会添加
        }
        ++lineNum; // 更新行数
    }
    /* 关闭资源 */
    ifs.close();
}

/* 1.输出单词出现次数
 * 2.单词出现行号 + 该行句子
 */
void TextQuery::query(const std::string & word) {
    std::cout << "----------------------------------------------------" << std::endl;
    std::string word_occurs("element occurs number times.");
    word_occurs.replace(word_occurs.find("element"), std::strlen("element"), word);
    word_occurs.replace(word_occurs.find("number"), std::strlen("number"), std::to_string(_dict[word]));
    std::cout << word_occurs << std::endl;

    for( int num : _wordNum[word]) {
        std::string newLine(_lines[num - 1]);
        std::cout << "( line " << num << " ) " << identified_words(newLine, word)  << std:: endl;
    }
    std::cout << "------------------------------" << std::endl;
}

std::string & identified_words(std::string & line, const std::string & word) {
    std::string::size_type word_idx = 0;
    std::string word_color( "\e[31m" + word + "\e[0m");
    while( (word_idx = line.find(word, word_idx)) != std::string::npos)  {
        if ( line.at(word_idx + word.size()) == ' ' || line.at(word_idx + word.size() == '\0')) {
            line.replace(word_idx, word.size(), word_color);
        }
        word_idx += word_color.size();
    }
    return line;
}

/* 遇到非字符 替换为 空格 
 * 遇到连接字符不替换 */
void dealLine (std::string &line) {
    for(char & ch : line) {
        if ( (!std::isalpha(ch)) && (ch != '-') && (ch != '\'') ) { ch = ' ';}
        /* else if ( isupper(ch) ) { ch = std::tolower(ch); } */
    }
}
