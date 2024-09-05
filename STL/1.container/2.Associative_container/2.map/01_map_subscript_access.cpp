/*************************************************************************
    > File Name: 03_map_[].cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 22时22分20秒
    > Mail: JiaZiChunQiu@163.com
    > Title: map 成员访问
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>

class Point{
public:
    Point(int x = 0, int y = 0) : _ix(x), _iy(y) {}
    ~Point() {}

    friend std::ostream & operator<<(std::ostream & os , const Point& obj);
private:
    int _ix;
    int _iy;
};

std::ostream & operator<<(std::ostream & os , const Point& obj) {
    return os << obj._ix << ", " << obj._iy;
}

/* =============== test =============== */
void test0() {
    std::map<std::string, Point> points = {
        {"1", Point(1, 2)},
        {"4", Point(3, 4)},
        {"3", Point(4, 4)},
    };
    std::cout << "points[\"1\"] = " << points["1"] << std::endl; // 查找
    std::cout << "points[\"0\"] = " << points["0"] << std::endl; // 插入

    points["4"] = Point(10, 20); // 修改
    std::cout << "points[\"0\"] = " << points["4"] << std::endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
