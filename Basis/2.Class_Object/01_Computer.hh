/*************************************************************************
    > File Name: 01_Computer.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月15日 星期四 09时21分33秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 类与对象
    > Content:
 ************************************************************************/

#ifndef _COMPUTER_HH
#define _COMPUTER_HH

class Computer {

public:
    Computer();
    Computer(const char* brand, double price);

    Computer(const Computer& rhs); 

    void print();
    void setBrand(const char* brand);
    void setPirce(double price);

    ~Computer();

private:
    char* _brand;
    double _price;
};

#endif
