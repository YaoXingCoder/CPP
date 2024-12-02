#ifndef __SINGLETO__H
#define __SINGLETO__H

class Singleton{
    class AutoRelease{
    public:
        /* AutoRelease(); */
        ~AutoRelease();
    private:
        static AutoRelease _auto;
    };
public:
    static Singleton* getInstance();

    void init(int, int);
    void print() const;

    friend AutoRelease::~AutoRelease(); 
private:
    Singleton() =  default;
    Singleton(int, int);
    ~Singleton();

    Singleton(const Singleton&) = delete;
    Singleton &operator=(const Singleton&) = delete;
private:
    int _ix;
    int _iy;
    static Singleton* _pInstance;
};

#endif
