/*************************************************************************
    > File Name: 07_single_Computer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 21时13分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 实现单例模式 Computer类 堆中
    > Content:
    >   1.因为在堆中, 所以析构函数可以放入 private
    >   2.不需要拷贝和赋值构造, 构造私有化
    >   3.因为在队中所以需要new函数, 并需要一个静态局部变量能够指向堆中地址, 因为是静态局部变量, 所以多次声明也只会初始化一次
    >   3.提供能够获取实例的静态方法, 该方法中会实例化一个对象, 且该对象唯一, 并返回该对象的引用, 确保是同一个对象
 ************************************************************************/

#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

/* =========================  类声明  ============================ */
class Computer{
public:
    /* 获取的实例 */
    static Computer* getInstance();

    /* 初始化 */
    void init(const char* brand, double price);

    /* 销毁函数 
     * 方便直接通过类名调用, static
     * */
    static void destroy();

    /* 打印函数 */
    void print () const;
private:
    /* 构造 */
    Computer();
    Computer(const char* brand, double price);

    /* 析构 */
    ~Computer();
    
    /* 方便init 和 析构调用 */
    void release();

    /* 使拷贝构造和赋值运算符函数为 delete */
    Computer(const Computer& rhs) = delete;
    Computer& operator=(const Computer& rhs) = delete;
private:
    char* _brand;
    double _price;
    static Computer* _pInstance;
};
/* 初始化静态成员变量 */
Computer* Computer::_pInstance = nullptr;

/* =========================  类定义 ============================ */

inline Computer::Computer()
: _brand(new char[1]())
, _price(0.0)
{
    cout << "Computer() 无参构造" << endl;
}

inline Computer::Computer(const char* brand, double price) 
: _brand(new char[strlen(brand) + 1]())
, _price(price)
{
    strcpy(_brand, brand);
    cout << "Computer(const char*, double) 有参构造" << endl;
}

inline Computer::~Computer() {
    release();
    cout << "~Computer()" << endl;
}

/* 初始化堆空间后, 是静态成员函数指向该空间 */
inline Computer* Computer::getInstance() {
    if ( _pInstance == nullptr ) { _pInstance = new Computer("apple", 2000.00); }
    return _pInstance;
}

/* 释放对象拥有的资源 */
inline void Computer::release() {
    if ( _brand != nullptr ) {
        delete[] _brand;
        _brand = nullptr;
    }
}

/* 初始化前需要先将原先的对象已经有的资源释放 */
inline void Computer::init(const char* brand, double price) {
    release();
    _brand = new char[strlen(brand) + 1]();
    strcpy(_brand, brand);
    _price = price;
    cout << "init() 初始化" << endl;
}

/* 释放堆中对象本身的空间资源 */
inline void Computer::destroy() {
    if (_pInstance != nullptr) {
        delete _pInstance; /* 会自动调用析构函数, 析构函数中会释放对象的资源 */
        _pInstance = nullptr;
    }
    cout << "destory() 销毁函数" << endl;
}

inline void Computer::print() const {
    cout << "( " << _brand << ", " << _price << " )" << endl;
}

/* =========================  测试函数 ============================ */
void test01() {
    Computer::getInstance()->init("xiaomi",6000);
    Computer::getInstance()->print();
    Computer::getInstance()->init("apple",18000);
    Computer::getInstance()->print();
    Computer::destroy();
}

/* =========================  主函数 ============================ */
int main (int argc, char* argv[]) {
    test01();
    return 0;
}
