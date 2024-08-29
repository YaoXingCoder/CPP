/*************************************************************************
    > File Name: 01_vector_traversal_method.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 09时20分40秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 读取并统计输出文件中单词
    > Content:
    >   1.文联文件
    >   2.读取文件(每次一行)
    >   3.判断单词并处理
    >   4.加入 vector 中
 ************************************************************************/

#include "01_vector_traversal_method.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/* const int Dictionary::_vecSize = 64; */

Record::Record(const std::string &word, int frequency) : _word(word), _frequency(frequency){
    /* std::cout << "Record(const string, int)" << std::endl; */
}

Dictionary::Dictionary(const int vecSize){
    _dict.reserve(vecSize);
    std::cout << "Dictionary(const int) constructor" << std::endl;
}

Dictionary::~Dictionary() {
    std::cout << "~Dictionary() destructor" << std::endl;
}

static bool operator<(const Record &lhs, const Record &rhs) {
    return lhs._word < rhs._word;
}

void Dictionary::read(const std::string &filename) {
    /* 关联输入文件 */ 
    std::ifstream ifs(filename);
    if ( !ifs ) {
        std::cerr << "ifstream open error" << std::endl;
        return;
    }

    /* 每次读取一行 */
    std::string line;
    while(std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string word;
        /* 循环处理一行中的每个单词 */
        while(iss >> word) {
            /* 处理字符串 */
            dealWord(word);
            /* 判断并存入 vector */
            if( !word.empty()) { pushVec(word); }
        }
    }

    /* 排序 */
    std::sort(_dict.begin(), _dict.end());

    /* 关闭资源 */
    ifs.close();
}

void Dictionary::dealWord(std::string &word) {
    if (word.empty()) { return; }
    std::string::iterator it = word.begin();
    while (it != word.end()) {
        if ( isalpha(*it)) { it++; }
        else { it = word.erase(it); }
    }
}

void Dictionary::pushVec(const std::string& word) {
    std::vector<Record>::iterator it = _dict.begin();
    while( it != _dict.end()) {
        if ( it->_word == word ) {
            ++(it->_frequency);
            return;
        }
        ++it;
    }
    _dict.push_back(Record(word, 1));
    return;
}

void Dictionary::print() const {
    std::cout << "------ start ------" << std::endl;
    for(const Record& rd : _dict) {
        std::cout << rd._word << ", " << rd._frequency << std::endl;
    }
    std::cout << "------ end ------" << std::endl;
    /* std::cout << _dict.size() << std::endl; */
    /* std::cout << _dict.capacity() << std::endl; */
}

void Dictionary::store(const std::string& filename) {
    /* 关联文件 */
    std::ofstream ofs(filename);
    if ( !ofs ) {
        std::cerr << "ofs open file error" << std::endl;
    }

    /* 循环输出到文件 */
    for(Record& rd : _dict) {
        ofs << rd._word << " : " << rd._frequency << std::endl;
    }

    /* 关闭资源 */
    ofs.close();
}
