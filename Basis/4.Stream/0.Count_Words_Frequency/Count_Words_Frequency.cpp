/*************************************************************************
    > File Name: Count_Words_Frequency.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 23时48分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 统一一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频
    > Content:
    >   输入: 某篇英文文章的绝对路径
    >   输出: 词典文件dict.txt (该词典中的每一行都是 单词 词频)
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

#define FILENAME_IN "The_Holy_Bible.txt"
#define FILENAME_OUT "dict.txt"
#define VECTOR_SIZE 1024

struct Record{
    string _word; /* 单词 */
    int _frequency; /* 词频 */
};

class Dictionary {
public:
    Dictionary() 
    : _dict(VECTOR_SIZE)
    { }

    void read(const std::string & filename); /* 读取文件内容 */
    void store(const std::string & filename); /* 处理后输出 */
private:
    vector<Record> _dict;
};

void Dictionary::read() {

}
