/*************************************************************************
    > File Name: 08_emplace_back_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 14时33分15秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Point {
public:
    Point(int ix = 0, int iy = 0) : _ix(ix) , _iy(iy) {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    Point(const Point &rhs) : _ix(rhs._ix) , _iy(rhs._iy) {
        cout << "Point(const Point &)" << endl;
    }

    /* Point(Point &&rhs) */
    /* : _ix(rhs._ix) */
    /* , _iy(rhs._iy) */
    /* { */
    /*     cout << "Point(Point &&)" << endl; */
    /* } */
private:
    int _ix;
    int _iy;
};

void test() {
    vector<Point> vec;
    Point pt(1, 2);
    /* vec.push_back(Point(1, 2)); */
    /* vec.emplace_back(1, 2); */
    vec.push_back(pt);
    vec.emplace_back(pt);

    /* vec.push_back(Point(1, 2)); */
    /* vec.emplace_back(Point(1, 2)); */
}

void test2() {
    vector<int> vec = {1, 2, 3, 4};
    /* vec[4]; */
    /* (void)vec.at(4); */
}

int main(int argc, char *argv[]) {
    test();
    /* test2(); */
    return 0;
}
