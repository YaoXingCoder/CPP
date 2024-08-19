/*************************************************************************
    > File Name: 08_Single_Heap_Point.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 20时30分55秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 堆实现单例模式 Point类
    > Content:
    >   1.构造器私有化, 因为单例所以不需要拷贝构造和赋值运算
    >   2.提供获取实例的方法 getInstance
    >   3.用
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Point {
public:
    /* 因为有静态指针所以，获取该指针也需要静态函数 */
    static Point* getInstance();

    /* 初始化函数 */
    void init(int x, int y);

    /* 销毁函数 
     * 能够直接调用, 不然通过getInstance 调用如果 _pInstance == nullptr 则会再创建一次, 然后再销毁
     * */
    static void destroy();

    /* 普通函数 */
    /* void setX(const int x); */
    /* void setY(const int y); */
    void print () const;

private:
    /* 构造函数 */
    Point();
    Point(const int x, const int y);

    /* 析构函数 */
    ~Point();

private:
    int _ix;
    int _iy;
    static Point* _pInstance;
};
/* 初始化 */
Point* Point::_pInstance = nullptr;

/* =========================  类定义 ============================ */

inline Point::Point() :_ix(0), _iy(0){
    cout << "Point() 无参构造" << endl;
}

inline Point::Point(int x, int y) : _ix(x), _iy(y) {
    cout << "Point(int x, int y) 有参构造" << endl;
}

inline Point::~Point() {
    cout << "~Point() 析构函数" << endl;
}

inline Point*  Point::getInstance() {
    if ( _pInstance == nullptr ) {
        _pInstance = new Point(1, 2);
    }
    return _pInstance;
}

inline void Point::init(int x, int y) {
    cout << "init() 初始化" << endl;
    _ix = x;
    _iy = y;
}

inline void Point::destroy() {
    if ( _pInstance != nullptr ) {
    cout << "destory() 销毁函数" << endl;
        delete _pInstance;
        _pInstance = nullptr;
    }
}

inline void Point::print() const {
    cout << "( " << _ix << ", " << _iy << " )" << endl;
}

/* =========================  测试定义 ============================ */
void test01() {
    Point* p1 = Point::getInstance();
    p1->print();
    Point::getInstance()->print();

    p1->init(1, 2);
    p1->print();
    Point::getInstance()->init(4, 5);
    Point::getInstance()->print();

    p1->destroy();
    p1->destroy();
    Point::destroy();
    /* Point::getInstance()->destroy(); */
}


int main (int argc, char* argv[]) {
    test01();
    return 0;
}
