/*************************************************************************
    > File Name: 01_single_auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 17时50分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式的自动释放
    > Content:
    >   1.定义全局类 AutoRelease, 实现单例模式的自动释放
 ************************************************************************/
#include "01_single_auto_release.hh"
#include <iostream>

/* ================ Singleton ================== */
Singleton* Singleton::_pInstance = nullptr;

Singleton::Singleton(int x, int y) : _ix(x), _iy(y)
{ std::cout << "Singleton(int, int) 有参" << std::endl; }

Singleton::~Singleton() { std::cout << "~Singleton() 析构" << std::endl; }

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

void Singleton::destroy() {
    std::cout << "destroy()" << std::endl;
    if ( _pInstance ) {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

void Singleton::print() const {
    std::cout << "( " << _ix << ", " << _iy << " )" << std::endl;
}


/* ================ AutoRelease ================== */
AutoRelease::AutoRelease(Singleton* pSingle) 
:_pSingle(pSingle)
{ 
    std::cout << "AutoRelease() 有参" << std::endl; 
}

AutoRelease::~AutoRelease() { 
    if ( _pSingle ) {
        _pSingle->destroy(); 
        _pSingle = nullptr;
    }
    std::cout << "~AutoRelease() 析构" << std::endl;
}

