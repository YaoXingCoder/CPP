/*************************************************************************
    > File Name: 07_single_Computer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 21时13分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 实现单例模式 Computer类 栈中
    > Content:
    >   1.因为在栈中, 所以析构函数只能 public
    >   2.不需要拷贝和赋值构造, 构造私有化
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
    /* 拷贝构造 */
    /* Computer(const Computer& rhs); */

    /* 获取的实例 */
    static Computer& getInstance();

    /* 初始化 */
    void init(const char* brand, double price);

    /* 打印函数 */
    void print () const;

    /* 析构 */
    ~Computer();
private:
    /* 构造 */
    Computer();
    Computer(const char* brand, double price);


private:
    char* _brand;
    double _price;
};

/* =========================  类定义 ============================ */

/* inline Computer::Computer(const Computer& rhs) */
/* : _brand(new char[strlen(rhs._brand) + 1]() ) */
/* , _price(rhs._price) */
/* { */
/*     strcpy(_brand, rhs._brand); */
/*     cout << "Computer(const Computer& rhs) 拷贝构造" << endl; */
/* } */

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
    if ( _brand != nullptr ) {
        delete[] _brand;
        _brand = nullptr;
    }
    cout << "~Computer()" << endl;
}

inline Computer& Computer::getInstance() {
    /*
     * 当静态函数多次被调用, 静态的局部对象只会被调用初始化一次
     * 后续的调用中, 静态局部对象已存在, 不会再初始化, 而是直接返回已经初始化的对象实例
     */
    static Computer cp("Apple", 20000.0); /* 改为静态变量, 使其生命周期变为跟程序一样 */
    return cp;
}

inline void Computer::init(const char* brand, double price) {
    if ( _brand != nullptr ) {
        delete[] _brand;
    }
    _brand = new char[strlen(brand) + 1]();
    strcpy(_brand, brand);
    _price = price;
    cout << "init() 初始化" << endl;
}

inline void Computer::print() const {
    cout << "( " << _brand << ", " << _price << " )" << endl;
}

/* =========================  测试函数 ============================ */
void test01() {
    Computer& cp1 = Computer::getInstance();
    cp1.print();
    Computer& cp2 = Computer::getInstance();
    cp2.print();
    printf("%p\n", &cp1);
    printf("%p\n", &cp2);
}

/* 静态对象多次初始化 测试 */
void func() {
    static int x = 0;  // 静态局部变量，只在第一次调用时初始化
    cout << "x = " << x << endl;
    x++;
}

void test02() {
    func();  // 输出: x = 0
    func();  // 输出: x = 1 (x 没有被重新初始化)
    func();  // 输出: x = 2
}

/* =========================  主函数 ============================ */
int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
