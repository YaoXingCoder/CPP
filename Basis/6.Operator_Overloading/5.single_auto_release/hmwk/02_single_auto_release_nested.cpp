/*************************************************************************
    > File Name: 01_single_auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 17时50分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式的自动释放
    > Content:
    >   1.使用嵌套类和静态对象的方式，实现单例模式的自动释放
    >       说明: 当实例化Singleton时, 其中的两个静态成员变量, 一个Singleton指针, 和一个AutoRelease对象(直接默认初始化)
    >       因为是静态成员变量, 作用域在类内, 但生命周期与程序一样, 当程序结束时, AutoRelease自动调用析构函数, 释放Singleton的堆中空间
 ************************************************************************/
#include "02_single_auto_release_nested.hh"
#include <iostream>

/* ================ Singleton ================== */
Singleton* Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::AutoRelease::_auto;

Singleton::Singleton(int x, int y) : _ix(x), _iy(y)
{ std::cout << "Singleton(int, int) 有参" << std::endl; }

Singleton::~Singleton() { std::cout << "~Singleton() 析构" << std::endl; }

/* 获取实例 */
Singleton* Singleton::getInstance() {
    if ( !_pInstance ) {
        
        _pInstance = new Singleton(1, 2);
    }
    return _pInstance;
}

void Singleton::init(int x, int y) {
    _ix = x;
    _iy = y;
}

void Singleton::print() const {
    std::cout << "( " << _ix << ", " << _iy << " )" << std::endl;
}

/* ================ AutoRelease ================== */
/* Singleton::AutoRelease::AutoRelease() */ 
/* {  std::cout << "AutoRelease()" << std::endl;  } */

Singleton::AutoRelease::~AutoRelease() { 
    if ( _pInstance ) {
        delete _pInstance; 
        _pInstance = nullptr;
    }
    std::cout << "~AutoRelease() 析构" << std::endl;
}

