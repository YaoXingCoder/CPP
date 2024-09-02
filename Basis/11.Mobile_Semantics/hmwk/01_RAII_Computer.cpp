/*************************************************************************
    > File Name: 01_RAII_Computer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月31日 星期六 09时14分06秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <cstring>

class Computer{
public:
    Computer() :_band(new char[1]()), _price(0){}
    Computer(const char* band, double price) : _band(new char[std::strlen(band) + 1]()), _price(price) {
        strcpy(_band, band);
    }

    ~Computer() {
        if ( _band ) {
            delete[] _band;
            _band = nullptr;
        }
    }

private:
        char* _band;
        double _price;
};

template<typename T>
class RAII{
public:
    RAII(T * data_ptr) : _data_ptr(data_ptr) {}

    ~RAII() {
        if ( _data_ptr ) {
            delete _data_ptr;
            _data_ptr = nullptr;
        }
    }

    RAII(const RAII&) = delete;
    RAII& operator=(const RAII &) = delete;
private:
    T * _data_ptr;
};

/* =============== test =============== */
void test0() {
    RAII<Computer>(new Computer);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
