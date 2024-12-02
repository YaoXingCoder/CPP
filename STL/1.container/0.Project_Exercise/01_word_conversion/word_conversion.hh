#ifndef __WORD_CONVERSION_H
#define __WORD_CONVERSION_H

#include <string>
#include <map>
#include <vector>

#define FILENAME_RULE "map.txt"
#define FILENAME_TXT "file.txt"
#define FILENAME_OUT "file_out.txt"

class Conver {
public:
    Conver(const int capacity = vec_size);
    ~Conver();
    void readRule(const char *);
    void parseWord(const char *);
    void dump(const char *);
private:
    std::map<std::string, std::string> _rule;
    std::vector<std::string> _str;
    static const int vec_size = 32;
};

#endif
