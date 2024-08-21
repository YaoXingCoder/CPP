/*************************************************************************
    > File Name: hashFunc_t.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 10时53分46秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <time.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define VECTOR_SIZE_DEFAULT 1024 * 8

/* ========================== 测试hash函数 ============================= */
int hashFunc(const string & str) {
    int hash = 0;
    int prime = 31;

    for(char ch : str) {
        hash = (hash * prime + ch) % VECTOR_SIZE_DEFAULT;
    }

    return hash;
}

void test01() {
    string str1 = "world";
    string str2 = "COUTN";
    string str3 = "count";
    int index = hashFunc(str1);
    cout << index << endl;

    index = hashFunc(str2);
    cout << index << endl;

    index = hashFunc(str3);
    cout << index << endl;
}

/* ========================== 测试空字符串 ============================= */

void test02() {
    string str1;

    string str2 = "";

    cout << "str1: " << str1.empty() << endl;
    cout << "str2: " << str2.empty() << endl;

}

/* ========================== 测试时间 ============================= */

#include <chrono>
#include <thread>
using std::chrono::high_resolution_clock;
using std::this_thread::sleep_for;
using std::chrono::seconds;
using std::chrono::duration;

/* 计算时间 */
void test03() {
    auto start = high_resolution_clock::now();
    
    sleep_for(seconds(2));

    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;

    cout << "program ran for " << duration.count() << " seconds." << endl;
}

/* ================== 测试单词处理 ===========================*/

#include <sstream>
using std::istringstream;

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

void test04() {
    /* string line = "1   in the beginning god created the heaven and the earth"; */
    string line = "2   for abc123 abc123abc  true and righteous  are  his judgments  for he hath judged the great whore  which did";
    istringstream iss(line);
    string word;
    while(iss >> word) {
        cout << word << " ";
        cout <<  dealWord(word) << " ";
        cout << word << endl;
    }
}

/* ================= 加入结构体和vcetor 进行测试 ====================== */

/* vector 每个元素的结构体 */
struct Record{
public:
    Record() : _word(""), _frequency(0) {
        cout << "无参构造" << endl;
    }
    Record(const string& word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {
        cout << "有参构造" << endl;
    }
    Record(const Record& rhs)
        :_word(rhs._word)
        ,_frequency(rhs._frequency)
    {
        cout << "拷贝构造" << endl;
    }

    Record& operator=(const Record& rhs) {
        _word = rhs._word;
        _frequency = rhs._frequency;
        cout << "Record 赋值运算函数" << endl;
        return *this;
    }

    string _word; /* 单词 */
    int _frequency; /* 词频 */
};

void test05() {
    Record record1;
    Record record2("hello", 1); 
    Record record3 = {"word", 1};
    Record record4 = Record("hi", 3);
    record1 = Record("123", 1);
}


int main (int argc, char* argv[]) {
    /* test01(); */
    /* test02(); */
    /* test03(); */
    /* test04(); */
    test05();
    return 0;
}
