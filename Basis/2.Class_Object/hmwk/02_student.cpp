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
using std::cout;
using std::endl;

/* 构造函数 */
Student::Student()
    : _sid(0)
    , _age(0)
    , _name(nullptr)
{
    cout << "Student() 无参构造函数" << endl;
}

/* 有参构造函数 
 * */
Student::Student(const int sid, const char* name, const int age)
    : _sid(sid)
    , _name(new char[strlen(name) + 1]())
    , _age(age)
{
    cout << "Student(const int, const char*, const int)  有参构造器" << endl;
    strcpy(_name, name);
}

/* 拷贝构造函数 */
Student::Student(const Student& rhs) 
    : _sid(rhs._sid)
    , _age(rhs._age)
    , _name(new char[strlen(rhs._name) + 1]())
{
    cout << "Student(const Student& rhs) 拷贝构造函数" << endl;
    strcpy(this->_name, rhs._name);
}

/* 赋值运算符函数 */
Student & Student::operator=(const Student& rhs){
    cout << "operator=(const Student& rhs) 符号运算函数" << endl;
    if ( this != &rhs ) {
        delete[] _name; /* 先删除原指向的空间 */
        _name = new char[strlen(rhs._name) + 1](); /* 重新分配空间大小 */
        strcpy(this->_name, rhs._name); /* 再将值复制到新空间 */

        this->_sid = rhs._sid;
        this->_age = rhs._age;
    }    

    return *this;
}

/* 析构函数 */
Student::~Student() {
    std::cout << "~Student()" << endl;
    if (_name != nullptr) {
        delete[] _name;
        _name = nullptr;
    }
}

/* 普通函数 */
void Student:: setSID(int sid){
    _sid = sid;
}
void Student::setAge(int age) {
    _age = age;
}
void Student::setName(const char* name) {
    if (name == nullptr) { return; }

    /* 防止自复制 */
    char* tmpStr = new char[strlen(name) + 1]();
    strcpy(tmpStr, name);
    delete[] _name;
    _name = new char[strlen(name) + 1] ();
    strcpy(_name, tmpStr);
}
void Student::print() {
    std::cout << "(" << _sid << "," <<  _name << "," << _age << ")" << endl;
}

