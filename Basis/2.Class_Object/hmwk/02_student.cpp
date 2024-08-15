/*************************************************************************
    > File Name: 02_student.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月15日 星期四 23时17分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 学生类实现
    > Content:
 ************************************************************************/

#include "02_student.hh"
#include <string.h>
#include <iostream>
using namespace std;

/* 构造函数 */
Student::Student()
    : _sid(0)
    , _age(0)
{
    _name[0] = { '\0' };
}

Student::Student(const int sid, const char* name, const int age)
    : _sid(sid)
    , _age(age)
{
    strcpy(_name, name);
}

/* 赋值运算符函数 */
Student & Student::operator=(const Student& rhs){
    if ( this != &rhs ) {
        this->_sid = rhs._sid;
        this->_age = rhs._age;
        strcpy(this->_name, rhs._name);
    }    

    return *this;
}

/* 析构函数 */
Student::~Student() {
    std::cout << "~Student()" << endl;
}


/* 普通函数 */
void Student:: setSID(const int sid){
    this->_sid = sid;
}
void Student::setAge(const int age) {
    _age = age;
}
void Student::setName(const char* name) {
    strcpy(_name, name);
}
void Student::print() {
    std::cout << "(" << _sid << "," <<  _name << "," << _age << ")" << endl;
}

