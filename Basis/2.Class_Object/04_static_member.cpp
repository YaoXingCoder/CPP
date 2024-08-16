/*************************************************************************
    > File Name: 04_static_member.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月16日 星期五 20时58分50秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 静态成员
    > Content:

 ************************************************************************/
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

/* ====================Computer类声明==================== */
class Computer{
public:
    Computer(); /* 无参构造函数 */
    Computer(const char* brand, const double price); /* 有参构造函数 */

    Computer(const Computer& rhs); /* 拷贝构造函数 */

    Computer& operator=(const Computer& rhs); /* 赋值运算符函数 */

    ~Computer(); /* 析构函数 */

    void print(); /* 普通打印函数 */

    static void printTotalPrice();
private:
    char* _brand;
    double _price;
    static double _totalPrice;
};

double Computer::_totalPrice = 0;

/* ====================Computer函数实现==================== */

inline Computer::Computer() : _brand(nullptr), _price(0) {
    _totalPrice += _price;
    cout << "Computer() 无参构造函数" << endl;
}

inline Computer::Computer(const char* brand, const double price) : _brand(new char[strlen(brand) + 1]), _price(price) {
    strcpy(_brand, brand);
    _totalPrice += _price;
    cout << "Computer(const char*, const double) 有参构造函数" << endl;
}

inline Computer::Computer(const Computer& rhs) : _brand(new char[strlen(rhs._brand) + 1]), _price(rhs._price) {
    _totalPrice += _price;
    strcpy(_brand, rhs._brand);
    cout << "Computer(const Computer& rhs) 拷贝构造函数" << endl;
}

/* 赋值运算符函数
 * 先进行判断防自复制 
 * */
inline Computer& Computer::operator=(const Computer& rhs) {
    cout << "Computer & operator(const Computer& rhs) 赋值运算符函数" << endl;
    if ( this != &rhs ) {
        _totalPrice -= _price;
        delete[] _brand; /* 先释放删除原指针指向的堆空间 */
        _brand = new char[strlen(rhs._brand) + 1];
        strcpy(_brand, rhs._brand);
        _price = rhs._price;
        _totalPrice += _price;
    }
    return *this;
}

inline Computer::~Computer() {
    cout << "~Computer() 析构函数" << endl; 
    if ( _brand ) {
        _totalPrice -= _price;
        delete[] _brand;
        _brand = nullptr;
    }
    /* printTotalPrice(); */
}

inline void Computer::print() {
    cout << "brand: " << _brand << endl;
    cout << "price: " << _price << endl;
}

inline void Computer::printTotalPrice() {
    cout << "totalPrice " << _totalPrice << endl;
}

/* ====================测试函数==================== */
void test01() {
    cout << sizeof(Computer) << endl;
    Computer pc1("Apple", 20000);
    Computer pc2("HuaWei", 18000);
    Computer pc3("Xiaomi", 15000);

    Computer::printTotalPrice();
}

/* ====================主函数==================== */
int main (int argc, char* argv[]) {
    test01();
    return 0;
}
