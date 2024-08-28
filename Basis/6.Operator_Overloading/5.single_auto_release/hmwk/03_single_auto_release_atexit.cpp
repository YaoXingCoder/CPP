/*************************************************************************
    > File Name: 01_single_auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 17时50分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式的自动释放
    > Content:
    >   1.使用atexit函数结合静态destroy函数，实现单例模式的自动释放
    >       atexit: 参数的函数必须是 static
    >   缺点: 不是线程安全的, 如果多个线程同时访问, 会注册多个销毁函数, 最终导致double free
    >       1. 懒汉式 缺点: 多线程风险
    >       2. 饱汉式 缺点: 内存忧虑
    >       只解决程序第一次启动时,但都没解决, 如果静态对象销毁后, 再次创建时的问题
 ************************************************************************/
#include "03_single_auto_release_atexit.hh"
#include <iostream>

/* ================ Singleton ================== */
Singleton* Singleton::_pInstance = nullptr;

Singleton::Singleton(int x, int y) : _ix(x), _iy(y) { 
    std::cout << "Singleton(int, int) 有参" << std::endl; 
}

Singleton::~Singleton() { 
    std::cout << "~Singleton() 析构" << std::endl; 
}

Singleton* Singleton::getInstance() {
    if ( !_pInstance ) {
        atexit(destroy);
        _pInstance = new Singleton(1, 2);
    }
    return _pInstance;
}

void Singleton::init(int x, int y) {
    _ix = x;
    _iy = y;
}

void Singleton::destroy() {
    std::cout << "destroy() 销毁" << std::endl;
    if ( _pInstance ) {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

void Singleton::print() const {
    std::cout << "( " << _ix << ", " << _iy << " )" << std::endl;
}

