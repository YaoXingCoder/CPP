/*************************************************************************
    > File Name: 01_Computer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月15日 星期四 09时31分09秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "01_Computer.hh"
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


/* 构造函数 */
Computer::Computer() 
    : _brand(new char[10]())
    , _price(0.0)
{
    cout << "Computer()" << endl;
}

Computer::Computer(const char* brand, double price) 
    : _brand(new char[strlen(brand) + 1])
    , _price(price)  { 
        cout << "Comuputer(char, double)" << endl;
        strcpy(_brand, brand); 
    };

/* 拷贝构造函数 */
/* Computer::Computer(const Computer& rhs) */
/*     :_brand(rhs._brand) */
/*     ,_price(rhs._price) */
/* { */
/*     cout << "Computer(const Computer& rhs)" << endl; */
/* } */
Computer::Computer(const Computer& rhs)
    : _brand(new char[strlen(rhs._brand) + 1])
    , _price(rhs._price)
{
    strcpy(_brand, rhs._brand);
    cout << "Computer(const Computer& rhs)" << endl;
}

/* 析构函数 */
Computer::~Computer() {
    cout << "~Computer()" << endl;
    if ( _brand ) {
        delete[] _brand;
        _brand = nullptr;    
    }
}

/* 普通函数 */
void Computer::print() { 
    cout << "(" << _brand << "," << _price << ")" << endl;
};

void Computer::setBrand(const char* brand){
    strcpy(_brand, brand);
}

void Computer::setPirce(double price) {
    _price = price;
}


