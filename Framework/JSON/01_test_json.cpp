/*************************************************************************
    > File Name: 01_test_json.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月07日 星期一 21时05分52秒
    > Mail: JiaZiChunQiu@163.com
    > Title: JSON_测试
    > Content:
 ************************************************************************/

#include "nlohmann/json.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    nlohmann::json jsonObject;
    jsonObject["key1"] =
        "value1"; // operator[](string) 把对象看成object，向里面加入一个键值对
    jsonObject["key2"] = 123.45;
    jsonObject["key3"]["hello"] = "world"; // "key3"键对应的值也是一个object类型
    jsonObject["key3"]["world"] = "hello";
    string output;
    output = jsonObject.dump(); // dump方法负责序列化
    cout << "output = " << output << "\n";
    return 0;
}
