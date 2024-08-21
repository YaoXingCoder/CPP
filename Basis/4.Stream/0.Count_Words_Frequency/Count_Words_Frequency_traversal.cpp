/*************************************************************************
    > File Name: Count_Words_Frequency_traversal.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 21时17分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cerr;
using std::cout;
using std::endl;
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

struct Record
{
    Record(const string & word,int frequency)
    : _word(word)
    , _frequency(frequency)
    {}

	string _word;
	int _frequency;
};

bool operator<(const Record & lhs,const Record & rhs){
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
    Dictionary(int capacity){
        _dict.reserve(capacity);
    }

    void read(const string &filename){
        ifstream ifs(filename);
        
        if(!ifs){
            cerr << "ifstream open file failed" << endl;
            return;
        }

        /* string word; */
        /* while(ifs >> word){ */
        /* } */

        string line;
        while(std::getline(ifs,line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                //处理单词
                dealWord(word);

                //尝试插入到vector中
                insert(word);
            }
        }

        //将vector中所有的元素进行排序
        sort(_dict.begin(),_dict.end());

        ifs.close();
    }

    void dealWord(string & data){
        auto it = data.begin();
        while(it != data.end()){
            if(isalpha(*it)){
                it++;
            }else{
                it = data.erase(it);
            }
        }
    }

    void insert(const string & data){
        if(data == string()){
            return;
        }

        size_t idx = 0;
        for(; idx < _dict.size(); ++idx){
            if(data == _dict[idx]._word){
                ++_dict[idx]._frequency;
                break;
            }
        }

        if(idx == _dict.size()){
            _dict.push_back(Record(data,1));
        }
    }

    void store(const string &filename){
        ofstream ofs(filename);

        if(!ofs){
            cerr << "ofstream open file failed" << endl;
            return;
        }

        for(auto & ele : _dict){
            ofs << ele._word << "  "
                << ele._frequency << endl;
        }

        ofs.close();
    }
private:
    vector<Record> _dict;
};

void test01() {

    /* 记录开始时间 */
    auto start = high_resolution_clock::now();

    cout << "start" << endl;
    Dictionary dic(10000);
    dic.read("The_Holy_Bible.txt");
    dic.store("dict.dat");
    cout << "end" << endl;

    /* 记录结束时间 */
    auto end = high_resolution_clock::now();

    /* 计算时间差 */
    duration<double> duration  = end - start;

    /* 输出时间 */
    cout << "Program fan for " << duration.count() << " seconds" << endl;
}

int main(void){
    test01();
    return 0;
}

