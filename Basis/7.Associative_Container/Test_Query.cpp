/*************************************************************************
    > File Name: Test_Query.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 09时59分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 文本查询
    > Content:
    >   该程序将读取用户指定的任意文本文件
    >   然后允许用户从该文件中查找单词。查询的结果是该单词出现的次数，并列
    >   出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行
    >   一次。行号按升序显示。
    >   示例：
    >  使用提供的文件内容，然后查找单词 "element"。输出的前几行为：
    >  ---------------------------------------------
    >  element occurs 125 times.
    >  (line 62) element with a given key.
    >  (line 64) second element with the same key.
    >  (line 153) element |==| operator.
    >  (line 250) the element type.
    >  (line 398) corresponding element.
    >  ---------------------------------------------
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::map;
using std::set;
using std::string;
using std::ifstream;
using std::istringstream;

class TextQuery{
/* 类初始化 */
public:
    TextQuery(const int vector_size = 107) {
        _lines.reserve(vector_size);
    }
/* 方式实现 */
public:
    /* 1 读取文件 */
    void readFile(const string & filename){
        /* 1.1 关联文件 */
        ifstream ifs(filename);
        if ( !ifs ) { cerr << "associate filename failded" << endl; return; }

        /* 1.2 读取每一行并处理 */
        string line;
        int lineNumber = 1;
        while(std::getline(ifs, line)) {
            /* 1.2.1 将一行的原始信息, 存入vecotr */
            _lines.push_back(line);

            /* 1.2.2 读取一行的内容并处理多余字符 */
            dealLine(line);

            /* 1.2.3 从处理后的行处理单词 */
            istringstream iss(line);
            string word;
            while(iss >> word) {
                /* 统计单词和次数 */
                ++_dict[word];

                /* 根据单词, 记录行号 */
                _wordNumbers[word].insert(lineNumber);
            }
            /* 每统计完行, 行号 + 1 */
            ++lineNumber;
        }
        
        ifs.close();
    }

    /* 1.2.2 处理行内容 */
    void dealLine(string& line) {
        /* 单词包含字符和数字就用空格代替 */
        for( char& ch : line ) { 
            if (!isalpha(ch)) { ch = ' '; }
            else if (isupper(ch)) { ch = tolower(ch); }
        }
    }

    /* 2 查找单词 */
    void query(const string & word) {
        cout << "-----------------------------" << endl;
        int count = _dict[word];
        cout << word << " coccursi " << count << " times " << endl;
        
        set<int> lineNumbers = _wordNumbers[word];
        for( int num : lineNumbers ) {
            cout << "( line " << num << " ) " << _lines[num - 1] << endl;
        }
        cout << "-----------------------------" << endl;
    }

/* 成员变量 */
private:
    vector<string> _lines; /* 记录一行的数据 */
    map<string, set<int>> _wordNumbers; /* 记录行, 行号 */
    map<string, int> _dict; /* 记录单词个数 */
};

/* =============== test =============== */
void test0() {
    string queryWord("the");
    TextQuery tq;
    tq.readFile("test.dat");
    tq.query(queryWord);
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    test0();
    return 0;
}
