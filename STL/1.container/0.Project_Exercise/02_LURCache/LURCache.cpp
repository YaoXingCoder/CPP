/*************************************************************************
    > File Name: LURCache.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月06日 星期五 17时30分00秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
    > Content:
    >   1.LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
    >   2.int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
    >   3.void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value; 
    >   4.如果不存在，则向缓存中插入该组 key-value 。
    >   5.果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
    >   6.函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
    >   提示：
    >   1 <= capacity <= 3000
    >   0 <= key <= 10000
    >   0 <= value <= 105
    >   最多调用 2 * 105 次 get 和 put
 ************************************************************************/

#include "LURCache.hh"

LURCache::LURCache(const int capacity) : _capacity(capacity){}

LURCache::~LURCache() {}

bool LURCache::isFull() const{
    return _lp.size() == _capacity;
}

std::list<std::pair<int, int>> & LURCache::get_lp() {
    return _lp;
}

int LURCache::get( const int key) {
    if ( _map_lp.count(key) == 0 ) { return -1; }
    else {
        _lp.splice(_lp.end(), _lp, _map_lp[key]);
        return _map_lp[key]->second;
    }
}

void LURCache::put(const int key, int value){
    if ( isFull() ) { 
        _map_lp.erase(_lp.front().first);
        _lp.pop_front();
    }
    if (_map_lp.count(key) == 0) {
        _lp.emplace_back(key, value);
        _map_lp[key] = (--_lp.end());
    } else {
        _lp.splice(_lp.end(), _lp, _map_lp[key]);
        _map_lp[key]->second = value;
    }
}


