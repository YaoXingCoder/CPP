/*************************************************************************
    > File Name: test.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 20时27分33秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Point{
public:
    Point(int x = 0,int y = 0)
    : _ix(x)
    , _iy(y)
    {
        cout << "Point(int,int)" << endl;
    }

    Point(const Point & rhs)
    : _ix(rhs._ix)
    , _iy(rhs._iy)
    {
        cout << "Point(const Point &)" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }

    void print() const{
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test2(){
    Point pt(1,2);
    //缺省调用
    Point pt2(3);
    Point pt3;

    //隐式转换
    //编译器会尝试使用一个int型参数初始化一个匿名的Point对象
    //再通过拷贝构造初始化pt4
    //Point pt4 = Point(3);
    Point pt4 = 3;
    pt4.print();
}

void test0(){
    vector<Point> nums;

    vector<Point> nums2(5);
    for(auto & ele : nums2){
        ele.print();
    }

    cout << endl;
    vector<Point> nums3(3,4);
    for(auto & ele : nums3){
        ele.print();
    }
    
    cout << endl;
    vector<Point> nums4{3,4};
    for(auto & ele : nums4){
        ele.print();
    }

#if 1
    cout << endl;
    vector<Point> nums5{{2,6},{8,9}};
    for(auto & ele : nums5){
        ele.print();
    }
#endif
}

void test1(){
    vector<Point> vec;
    vec.reserve(10);
    vec.push_back(Point(3,5));
    vec.push_back(Point(8,9));
    vec.push_back(Point(6,7));
    vec.push_back(Point(6,7));
}

int main(void){
    test2();
    return 0;
}


