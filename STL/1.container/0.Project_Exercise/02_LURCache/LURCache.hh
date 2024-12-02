#ifndef __LUR_CACHE_H
#define __LUR_CACHE_H

#include <unordered_map>
#include <utility>
#include <list>

class LURCache {
public:
    LURCache(const int capacity = vec_size);
    ~LURCache();

    int get(int);
    void put(const int, int);
    bool isFull() const;

    std::list<std::pair<int, int>> & get_lp();

private:
    std::unordered_map< int, std::list<std::pair<int, int>>::iterator> _map_lp; /* 实现 O(1) 的查询和删除 */
    std::list<std::pair< int, int >> _lp; /* 存储节点 */
    const std::size_t _capacity;
    static const int vec_size = 4;
};

#endif
