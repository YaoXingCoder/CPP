#ifndef __DICITIONARY_H
#define __DICITIONARY_H

#include <string>
#include <vector>

#define FILENAME_IN "The_Holy_Bible.txt"
#define FILENAME_OUT "dict.txt"

struct Record{
    Record(const std::string &, int);
    std::string _word;
    int _frequency;
};

class Dictionary{
public:
    Dictionary(const int vecSize = _vecSize);
    ~Dictionary();

    void read(const std::string &);
    void store(const std::string &);

    void dealWord(std::string &);
    void pushVec(const std::string &);
    void print() const;
 private:
     std::vector<Record> _dict;
     static const int _vecSize = 64; /* 静态成员常量, 运行前初始化 */
};

#endif
