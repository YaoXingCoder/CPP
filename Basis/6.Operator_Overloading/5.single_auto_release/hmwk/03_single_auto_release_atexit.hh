#ifndef __SINGLETO__H
#define __SINGLETO__H

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

    Singleton(const Singleton&) = delete;
    Singleton &operator=(const Singleton&) = delete;
private:
    int _ix;
    int _iy;
    static Singleton* _pInstance;
};

#endif
