/*************************************************************************
    > File Name: 05_Single_Auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 11时31分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例对象的释放, 自动释放, 加入线程安全
    > Content:
    >   1.pthread_once 函数可以确保初始化代码只会执行一次
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Singleton {
public:
    static Singleton * getInstance(){
        /* if(nullptr == _pInstance){ */ 
        /*     atexit(destroy); /1* 注册函数 *1/ */
        /*     _pInstance = new Singleton(1,2); */ 
        /* } */
        pthread_once(&_once, init_t);
        return _pInstance;
    }

    void init(int x,int y){
        _ix = x;
        _iy = y;
    }

    void print() const { cout << "( " << _ix << ", " << _iy << " )" << endl; }

private:
    Singleton() = default;
    Singleton(int x,int y) : _ix(x) , _iy(y)
    { cout << "Singleton(int,int)" << endl; }
    ~Singleton(){ cout << "~Singleton()" << endl; } /* 因为对象在堆中, 程序结束不会调用析构, 需要手动释放堆上的空间 */

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    static void init_t(void) {
        atexit(destroy);
        _pInstance = new Singleton(1, 2);
    }

    Singleton(const Singleton& rhs) = delete;
    Singleton& operator=(const Singleton & rhs) = delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
    static pthread_once_t _once;
};
Singleton * Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;


/* =============== test ============== */
void test0() {
    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(3, 4);
    Singleton::getInstance()->print();
}

/* =============== main ============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
