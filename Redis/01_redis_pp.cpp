/*************************************************************************
    > File Name: 01_redis_pp.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月24日 星期二 21时46分33秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <sw/redis++/redis++.h>
#include <iostream>

using namespace std;
using namespace sw::redis;

int main() {
    auto redis = Redis("tcp://127.0.0.1:6379");

    redis.set("key", "val");
    auto val = redis.get("key");   
    if (val) {
        std::cout << *val << std::endl;
    }
  
    std::vector<std::string> vec = {"a", "b", "c"};
    redis.rpush("list", vec.begin(), vec.end());
    redis.rpush("list", {"a", "b", "c"});

    vec.clear();
    redis.lrange("list", 0, -1, std::back_inserter(vec));
    
    return 0;
}
