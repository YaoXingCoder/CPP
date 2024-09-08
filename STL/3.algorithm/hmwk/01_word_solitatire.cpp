/*************************************************************************
    > File Name: 01_word_solitatire.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月08日 星期日 22时41分17秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单词接龙
    > Content:
    >   字典 wordList 中从单词 beginWord 到 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：
    >   1.每一对相邻的单词只差一个字母。
    >   2.对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
    >   3.sk == endWord 给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0 。
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <iterator>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        /* 1.转换为hash, 加快访问 */
        std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
        if ( !wordSet.count(endWord) ) { return 0; }
        wordSet.erase(beginWord);

        /* std::copy(wordSet.begin(), wordSet.end(), std::ostream_iterator<std::string>(std::cout, " ")); */

        /* 2.BFS */
        std::queue<std::string> q; // BFS 队列
        std::unordered_set<std::string> visited; // 记录访问过的节点
        visited.insert(beginWord);
        q.push(beginWord);
        int step = 1; // 记录步骤, 同时是树的深度
        while(!q.empty()) {
            int sz = q.size(); // 获取没层树的数量
            /* std::cout << sz << std::endl; */
            for( int i = 0; i < sz; ++i ) {
                std::string curWord = q.front();
                q.pop();
                /* 穷举每个字符 */
                for ( int j = 0; j < curWord.length(); ++j ) {
                    char originChar = curWord[j]; // 用于恢复原单词
                    for(char c = 'a'; c <= 'z'; ++c) {
                        if ( c == originChar ) { continue; } 
                        /* 构成新单词, 并判断新单词是否在转换列表中, 且是否已构成过 */
                        curWord[j] = c;
                        /* 新构成的单词需要是在列表中, 且没有访问过的, 才能加入队列 */
                        if ( wordSet.count(curWord) && !visited.count(curWord) ) {
                            if( curWord == endWord ) { return step + 1; } // 已构成则返回步数
                            q.push(curWord); // 添加新单词到队列中
                            visited.insert(curWord); // 添加该单词到访问过列表
                        }
                    }
                    curWord[j] = originChar;/* 新构成单词已经添加进列表, 则把单词再变回, 将26个字母穷举完 */ 
                }
            }
            ++step; // 每次重新获取队列, 就是增加树的深度
        }
        return 0;
    }
};

/* =============== test =============== */
void test0() {
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList{"hot","dot","dog","lot","log","cog"};
    std::cout << Solution().ladderLength(beginWord, endWord, wordList) << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
