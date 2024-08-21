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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

/* 计算时间 */
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::seconds;
using std::chrono::duration;

/* #define FILENAME_IN "abc.txt" */
#define FILENAME_IN "The_Holy_Bible.txt"
#define FILENAME_OUT "dict.txt"
#define VECTOR_SIZE_DEFAULT 1024 * 1024 * 8
/* #define VECTOR_SIZE_DEFAULT 32 */
#define LOAD_FACTOR 0.75


/* ============================== 结构体|类 ================================== */

/* vector 每个元素的结构体 */
struct Record{
public:
    Record() : _word(""), _frequency(0) { /* cout << "无参构造" << endl; */ }
    Record(const string& word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {}

    Record& operator=(const Record& rhs) {
        _word = rhs._word;
        _frequency = rhs._frequency;
        /* cout << "Record 赋值运算" << endl; */
        return *this;
    }

    string _word; /* 单词 */
    int _frequency; /* 词频 */
};

/* 字典类 */
class Dictionary {
public:
    /* 默认初始化 1024 * 8 空间大小 */
    Dictionary(int capacity = VECTOR_SIZE_DEFAULT) 
    :_dict(capacity)
    {
        /* _dict.reserve(capacity); /1* 只扩容不初始化 *1/ */
    }

    void read(const string & filename); /* 读取文件内容 */
    void store(const string & filename); /* 处理后输出 */
private:
    void pushVec(const string& word);
    /* void resize_vec(int capacity); */
private:
    vector<Record> _dict;
};

/* ================================= 函数定义 ============================== */

/* 判断单词时候符合要求 */
bool checkWord(const string & str);
bool dealWord(string& word);
int hashFunc(const string & str, int capacity);
void addVec(vector<Record>& dict, int index, const string& word);

/* ============================== 类实现 ================================== */

bool operator<(const Record& lhs, const Record& rhs) {
    return lhs._word < rhs._word;
}

/* 读取文件内容 */
void Dictionary::read(const string & filename) {
    /* 关联文件 */
    ifstream ifs(filename);
    if ( !ifs ) { 
        cerr << "ifs is failed." << endl;
        return;
    }

    /* 循环读取文件中数据, 并存入数据结构中 
     * 使用行读取, 减少与终端的交互
     * */
    string line;
    while( std::getline(ifs, line) ) {
        /* cout << line << endl; */
        /* 处理每一行中的单词 */
        string word;
        istringstream iss(line);
        while( iss >> word ) { 
            /* 处理判断单词 合法则存入  */
            /* cout << word << endl; */
            if ( dealWord(word) ) { pushVec(word); }
        }
    }

    /* 对结构中内容进行排序 */
     sort(_dict.begin(), _dict.end()); 

    /* 关闭资源 */
    ifs.close();
}

/* 将 vector 中的结构存入 文件中 */
void Dictionary::store(const string& filename) {
    /* 关联文件 */
    ofstream ofs(filename);
    if ( !ofs ) {
        cerr << "ofstream open file failed" << endl;
        return;
    }

    /* 循环写入文件 
     * 增强for循环是以 size作为结束条件
     * 而用hash后 应该以容量的capacity大小作为结束条件
     * 初始化时, 一堆所有的Record进行初始化, 所以 size = capacity
     * */
    /* for (Record& record : _dict) { */
    /*     ofs << record._word << "\t\t" << record._frequency << endl; */
    /* } */
    for(int i = 0; i < _dict.capacity(); ++i) {
        if( !_dict[i]._word.empty() ){
            ofs << _dict[i]._word << "\t\t" << _dict[i]._frequency << endl;
        }
    }

    ofs.close();
}

/* 通过 hashfunc 获取到 下标, 存入 vector 中 
 * 如果产生哈希冲突, 采用线性探测法
 * */
void Dictionary::pushVec(const string& word) {
    int index = hashFunc(word, _dict.capacity());

    /* 添加 */
    addVec(_dict, index, word);

    /* 每次结束后判断负载 */
    /* if ( static_cast<double>(_dict.size()) / static_cast<double>(_dict.capacity()) >= LOAD_FACTOR ) { */
    /*     int new_capacity = _dict.capacity() << 1; */
    /*     resize_vec(new_capacity); */
    /* } */
}

/* 插入数据 */
void addVec(vector<Record>& dict, int index, const string& word) {
    /* 判断是否产生冲突 线性探测 */
    while( !dict[index]._word.empty() ){
        if (dict[index]._word == word) { 
            dict[index]._frequency++; 
            return;
        } else {
            index = (index + 1) % dict.capacity();
        }
    }

    /* 添加数据 */
    dict[index] = Record(word, 1); /* 赋值运算 */
    /* dict[index] = {"word", 1}; */
}

/* 扩容 
 * 重新计算还行遍历插入
 * */
/* void Dictionary::resize_vec(int capacity) { */
/*     cout << "======= start" << endl; */
/*     vector<Record> new_dict; */
/*     new_dict.reserve(capacity); */
/*     cout << "new _dict'size  is " << new_dict.size() << endl; */
/*     cout << "new _dict'capacity is " << new_dict.capacity() << endl; */
/*     cout << "======== end"  << endl; */

/*     /1* 循环遍历旧vector, 再哈希放入新的 vector *1/ */
/*     for(int i = 0; i < _dict.capacity(); ++i) { */
/*         if ( !_dict[i]._word.empty() ) { */
/*             int index = hashFunc(_dict[i]._word, capacity); */
/*             addVec(new_dict, index, _dict[i]._word); */ 
/*         } */
/*     } */
    
/*     _dict.clear(); */
/*     _dict.reserve(capacity); */
/*     _dict = std::move(new_dict); */
/*     cout << "dict's size is: " << _dict.size() << endl; */
/*     cout << "dict's capacity is: " << _dict.capacity() << endl; */
/* } */

/* 运用 hashFunc 计算出单词应存储到 vector 中的下标, 便于快速查找 
 * */
int hashFunc(const string & str, int capacity) {
    int hash = 0;
    int prime = 31; /* 哈希因子 */

    /* 每一个字母都会影响哈希值 */
    for(char ch : str) {
        hash = (hash * prime + ch) % capacity;
    }

    return hash;
}

/* 判断单词时候符合要求 */
bool checkWord(const string & str) {
    if ( str.empty() ) { return false; }
    for( char ch : str ) {
        if ( !std::isalpha(ch) ) { return false; }
    }
    return true;
}

/* 先处理单词, 处理结束后判断是否合法
 * 处理:
 *      1.单词中含有其他的字符, 去除
 *      2.空字符
 *判断处理后的:
 *      1.合法: true
 *      2.不合法: false
 * */
bool dealWord(string& word) {
    /* 处理单词 */
    string::iterator it = word.begin();
    while ( it != word.end() ) {
        if ( isalpha(*it) ) { it++; }
        else { it = word.erase(it); } /* 丢弃该不是字母的字符 */
    }

    /* 判断 */
    if( checkWord(word) ) { return true; }
    else { return false; }
}


/* ============================== 测试 ================================== */
void test01() {

    /* 记录开始时间 */
    auto start = high_resolution_clock::now();

    cout << "start" << endl;
    Dictionary dic;
    dic.read(FILENAME_IN);
    dic.store(FILENAME_OUT);
    cout << "end" << endl;

    /* 记录结束时间 */
    auto end = high_resolution_clock::now();

    /* 计算时间差 */
    duration<double> duration  = end - start;

    /* 输出时间 */
    cout << "Program fan for " << duration.count() << " seconds" << endl;
}

int main() {
    test01();
    return 0;
}
