/*************************************************************************
    > File Name: Count_Words_Frequency_traversal.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 21时17分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 使用 map
    > Content:  
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
/* #include <algorithm> */
using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

/* 计算时间 */
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::seconds;
using std::chrono::duration;

/* 每一个 vector 元素的存储结构 */
/* struct Record { */
/*     Record(const string & word,int frequency) : _word(word) , _frequency(frequency) {} */

/* 	string _word; */
/* 	int _frequency; */
/* }; */

/* 比较器 */
/* bool operator<(const Record & lhs,const Record & rhs){ */
/*     return lhs._word < rhs._word; */
/* } */

/* 字典类 */
class Dictionary {
public:
    /* 1.字典初始化 
     *  改为 map 后, 不再需要初始化 */
    /* Dictionary(int capacity){ _dict.reserve(capacity);} */
    Dictionary(){};

    /* 2.从文件读取, 处理单词 */
    void read(const string &filename){
        /* 2.1 关联文件 */
        ifstream ifs(filename);
        if(!ifs){
            cerr << "ifstream open file failed" << endl;
            return;
        }

        /* 2.2 读取单词 */
        string line;
        while(std::getline(ifs,line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                /* 2.3 处理单词 */
                dealWord(word);

                /* 2.4 尝试插入到vector中 */
                /* 2.4 使用 map, 直接插入 */
                if ( !word.empty() ) { 
                    ++_dict[word];
                }
            }
        }

        /* 2.5 将 vector 中所有的元素进行排序 
         *  如果是 map, 会自动排序 */
        /* sort(_dict.begin(),_dict.end()); */

        /* 关闭关联 */
        ifs.close();
    }

    /* 2.3 处理单词 */
    void dealWord(string & data){
        auto it = data.begin();
        while(it != data.end()){
            if(isalpha(*it)){ it++;}
            else{ it = data.erase(it); }
        }
    }

    /* 2.4 插入 vector 中
     *  使用 map,  不再需要插入 */
    /* void insert(const string & data){ */
    /*     if(data == string()){ return; } */

    /*     size_t idx = 0; */
    /*     /1* 遍历, 更新单词的 frequency *1/ */
    /*     for(; idx < _dict.size(); ++idx){ */
    /*         if(data == _dict[idx]._word){ */
    /*             ++_dict[idx]._frequency; */
    /*             break; */
    /*         } */
    /*     } */

    /*     /1* 新单词, 插入最后 *1/ */
    /*     if(idx == _dict.size()){ */
    /*         _dict.push_back(Record(data,1)); */
    /*     } */
    /* } */

    /* 3 存储 */
    void store(const string &filename){
        /* 3.1 关联输出文件 */
        ofstream ofs(filename);
        if(!ofs){ cerr << "ofstream open file failed" << endl; return; }

        /* 3.2 遍历 vector, 并存入到文件 */
        /* for(auto & ele : _dict){ */
        /*     ofs << ele._word << "  " << ele._frequency << endl; */
        /* } */

        /* 3.2 使用 map, 遍历方式并存入 */
        map<string, int>::iterator it_map = _dict.begin();
        for(; it_map != _dict.end(); ++it_map) {
            ofs << it_map->first << " " << it_map->second << endl;
        }

        /* 关闭关联容器 */
        ofs.close();
    }
    
private: /* 私有 成员变量 */
    /* vector<Record> _dict; */
    map<string, int> _dict;
};

/* ====================  test ================= */
void test0() {

    /* 记录开始时间 */
    auto start = high_resolution_clock::now();

    cout << "====== start ======" << endl;
    /* Dictionary dic(10000); */
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("dict.dat");
    cout << "====== end ======" << endl;

    /* 记录结束时间 */
    auto end = high_resolution_clock::now();

    /* 计算时间差 */
    duration<double> duration  = end - start;

    /* 输出时间 */
    cout << "Program fan for " << duration.count() << " seconds" << endl;
}

int main(void){
    test0();
    return 0;
}

