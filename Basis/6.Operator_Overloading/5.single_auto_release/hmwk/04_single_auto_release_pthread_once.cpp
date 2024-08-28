/*************************************************************************
    > File Name: 01_single_auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 17时50分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例模式的自动释放
    > Content:
    >   1.使用pthread_once函数结合destroy函数，实现单例模式的自动释放
 ************************************************************************/
#include "04_single_auto_release_pthread_once.hh"

/* ================ Singleton ================== */
Singleton* Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

Singleton::Singleton(int x, int y) : _ix(x), _iy(y)
{ 
    std::cout << "Singleton(int, int) 有参" << std::endl; 
}

Singleton::~Singleton() { 
    std::cout << "~Singleton() 析构" << std::endl; 
}

Singleton* Singleton::getInstance() {
    pthread_once(&_once, init_routine);
    return _pInstance;
}

void Singleton::init(int x, int y) {
    _ix = x;
    _iy = y;
}

void Singleton::init_routine() {
    _pInstance = new Singleton(1, 2);
    atexit(destroy);
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
