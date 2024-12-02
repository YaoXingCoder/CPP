#ifndef __TEXTQUERY_H
#define __TEXTQUERY_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>

#define FILENAME_IN "china_daily.txt"

class QueryResult; // 前向声明

class TextQuery{
    public:
        using line_no = std::vector<std::string>::size_type; // size_type 起别名, set集合的存储数据类型
        TextQuery(std::ifstream &); // 输入流, 构造时完成文件读取, 存储
        QueryResult query(const std::string &) const; // 查询抽象类, 多态
        void display_map(); // debug : print the map
    private:
        std::shared_ptr<std::vector<std::string>> _file; /* 记录每一行的数据, 行号即为vector下标 + 1 */
        std::map<std::string, std::shared_ptr<std::set<line_no>>> wm; /* 记录出现过单词的行号 */
        static std::string deal_str(const std::string &); // 处理单词, 将所有单词转换为小写
};

#endif
