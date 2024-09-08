/*************************************************************************
    > File Name: word_conversion.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月05日 星期四 23时12分53秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单词转换
    > Content:
    >   1.读取文件内容存入 容器
    >   2.匹配单词并进行修改
    >   3.重新输出到文件
 ************************************************************************/

#include "word_conversion.hh"
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>

Conver::Conver(const int capacity) {
    _str.reserve(capacity);
}

Conver::~Conver() {}

void Conver::readRule(const char * filename) {
    /* 关联文件 */
    std::ifstream ifs(filename);
    if ( !ifs ) { 
        std::cerr << "ifs open error" << std::endl;
        return;
    }

    /* 读取每行并处理存储 */
    std::string line;
    while(std::getline(ifs, line)) {
        std::string::iterator it_first = line.begin();
        while( *it_first != ' ' && it_first != line.end()) { ++it_first; }
        /* std::string str_first(line.begin(), it_first); */
        /* std::string str_behind(it_first, line.end()); */
        /* _rule.insert({str_first, str_behind}); */
        _rule.emplace(std::make_pair(std::string(line.begin(), it_first), std::string(it_first + 1, line.end()))); // 使用原地构造
    }

    /* for( std::pair<const std::string, std::string> & pair_str : _rule ) { */
    /*     std::cout << pair_str.first << ", " << pair_str.second << std::endl; */
    /* } */

    /* std::cout << _rule.count("a") << std::endl; */

    /* 关闭资源 */
    ifs.close();
}

void Conver::parseWord(const char * filename) {
    /* 关联文件 */
    std::ifstream ifs(filename);
    if ( !ifs ) { 
        std::cerr << "parseWord ifs error" << std::endl;
        return;
    }

    /* 循环读取并处理, 并存入 vector 容器中 */
    std::string line;
    while( std::getline(ifs, line) ) {
        std::string new_line;
        std::string word;
        std::istringstream iss(line);
        while( iss >> word ) {
            if ( _rule.count(word) > 0 ) { new_line.append(_rule[word]); }
            else { new_line.append(word); }
            new_line.append(" ");
        }
        _str.emplace_back(new_line);
    }

    /* for (std::string & str : _str) { */
    /*     std::cout << str << std::endl; */
    /* } */

    /* 关闭资源 */
    ifs.close();
}

void Conver::dump(const char * filename) {
    /* 关联文件 */
    std::ofstream ofs(filename);
    if ( !ofs ) {
        std::cerr << "dump ofs error" << std::endl;
        return;
    }

    /* 遍历并输出到文件 */
    for (std::string & str : _str) {
        ofs << str << std::endl;
    }

    /* 关闭 */
    ofs.close();
}

int main() {
    Conver cv;
    cv.readRule(FILENAME_RULE);
    cv.parseWord(FILENAME_TXT);
    cv.dump(FILENAME_OUT);
    return 0;
}
