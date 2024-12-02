#ifndef __TEXTQUERY_H
#define __TEXTQUERY_H

#include <string>
#include <vector>
#include <map>
#include <set>

#define FILENAME_IN "china_daily.txt"

class TextQuery{
    public:
        TextQuery(const int vecSize =  _vecSize);
        void readFile(const std::string & filename = FILENAME_IN);
        void query(const std::string &);
    private:
        static const int _vecSize = 32;
        std::vector<std::string> _lines; /* 记录每一行的数据, 行号即为vector下标 + 1 */
        std::map<std::string, std::set<int>> _wordNum; /* 记录出现过单词的行号 */
        std::map<std::string, int> _dict; /* 单词词典, 记录单词出现过的次数 */
};

#endif
