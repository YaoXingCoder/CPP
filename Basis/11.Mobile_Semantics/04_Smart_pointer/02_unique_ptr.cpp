/*************************************************************************
    > File Name: 02_unique_ptr.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 23时04分53秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

class Point {
public:
    Point(int x,int y) : _ix(x) , _iy(y) {
        /* cout << "Point(int,int)" << endl; */
    }

    void print() const{
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;
    }

    ~Point(){ /* cout << "~Point()" << endl; */ }
private:
    int _ix;
    int _iy;
};

void test0(){
    unique_ptr<int> up(new int(10));
    /* cout << *up << endl; */
    /* cout << up.get() << endl; */

    unique_ptr<Point> up2(new Point(2,8));
    /* (*up2).print(); */
    /* up2.reset(new Point(3,7)); */
    /* up2->print(); */

    unique_ptr<Point> up3(new Point(6,5));
    /* unique_ptr<Point> up4 = up3; */
    /* up3 = up2; */

    cout << endl << " --------- vctor -------------" << endl;
    vector<unique_ptr<Point>> vec;
    // push_back的参数需要一个右值属性的unique_ptr
    /* vec.push_back(up2); */

    // vector 的元素是利用 unique_ptr 的移动构造
    // 产生的 unique_ptr 临时对象的副本, 移交管理权的副本
    vec.push_back(unique_ptr<Point>(new Point(2,4)));
    vec[0]->print();

    unique_ptr<Point> && rhs = std::move(up2); 
    cout << rhs.get() << endl;
    rhs->print();
    std::cout << "up2 points to: " << up2.get() << std::endl; // Outputs nullptr
    up2->print();

    // 调用 unique_ptr 移动构造
    // 新产生的 unique_ptr 的副本就是 vector 的元素
    // 副本底层的指针接管up2原本的资源
    // 并将rhs底层的指针置空，up2底层的指针也会随之改变（空指针）
    vec.push_back(std::move(up2));
    vec.push_back(std::move(up3));
    vec[1]->print();
    vec[2]->print();

    /* up2.reset(new Point(4,8)); */
    /* up2->print(); */
}

/* Point* p1 = new Point(1, 2); */
void test1() {
Point* p1 = new Point(1, 2);
    unique_ptr<Point> up1(p1);
    /* unique_ptr<Point> up2(p1); */
    /* up2->print(); */
    up1->print();
    p1->print();
}

int main(void){
    /* test0(); */
    test1();
    /* p1->print(); */
    return 0;
}
