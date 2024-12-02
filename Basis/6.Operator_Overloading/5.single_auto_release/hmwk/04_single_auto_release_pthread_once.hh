

#ifndef __SINGLETO__H
#define __SINGLETO__H
#include <iostream>

class Singleton{
public:
    static Singleton* getInstance();

    void init(int, int);
    void print() const;
private:
    Singleton() =  default;
    Singleton(int, int);
    ~Singleton();
    static void destroy();

    static void init_routine();

    Singleton(const Singleton&) = delete;
    Singleton &operator=(const Singleton&) = delete;
private:
    int _ix;
    int _iy;
    static Singleton* _pInstance;
    static pthread_once_t _once;
};

#endif
