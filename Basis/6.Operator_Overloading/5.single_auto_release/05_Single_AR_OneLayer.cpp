/*************************************************************************
    > File Name: 05_Single_Auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 11时31分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例对象的释放, 自动释放
    > Content:
    >   1.方式一: 添加一个AutoRelease对象, 程序结束时, 该对象的析构函数被调用
    >             通过该函数的析构函数, 释放Singleton在堆上的资源
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Singleton;

/* ============== AutoRelease =============== */
class AutoRelease{
public:
    AutoRelease(Singleton* pSingle) : _pSingle(pSingle) {}
    ~AutoRelease();
private:
    Singleton* _pSingle;
};

/* ============== Singleton =============== */
class Singleton {
public:
    static Singleton * getInstance(){
        if(nullptr == _pInstance){ _pInstance = new Singleton(1,2); }
        return _pInstance;
    }

    void init(int x,int y){
        _ix = x;
        _iy = y;
    }

    void print() const { cout << "( " << _ix << ", " << _iy << " )" << endl; }
    
    friend AutoRelease::~AutoRelease();
private:
    Singleton() = default;
    Singleton(int x,int y) : _ix(x) , _iy(y)
    { cout << "Singleton(int,int)" << endl; }
    ~Singleton(){ cout << "~Singleton()" << endl; } /* 因为对象在堆中, 程序结束不会调用析构, 需要手动释放堆上的空间 */

    static void destroy(){
        cout << "Singleton() destroy() start" << endl;
         if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
		}
        cout << "Singleton() destroy() end" << endl;
	}

    Singleton(const Singleton& rhs) = delete;
    Singleton& operator=(const Singleton & rhs) = delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = nullptr;

/* 析构实现 */
AutoRelease:: ~AutoRelease() {
    cout << "~AutoRelease() 析构 start" << endl;
    if ( _pSingle ) {
        _pSingle->destroy();
        _pSingle = nullptr;
    }
    cout  << "~AutoRelease() 析构 end" << endl;
}
/* =============== test ============== */
void test0() {
    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(3, 4);
    Singleton::getInstance()->print();
    /* Singleton::destroy(); /1* 需要手动释放 *1/ */
}

void test1() {
    /* AutoRelease(Singleton::getInstance()->getInstance()); // TODO 不能够使用创建临时对象的方式; */
    /* AutoRelease(Singleton::getInstance()); /1* 报错原因 被理解为: Singleton* AutoRelease(Singleton::getInstance()); *1/ */
    AutoRelease ar(Singleton::getInstance());
    AutoRelease ar2(Singleton::getInstance());
    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();
    /* Singleton::destroy(); */
}

/* =============== main ============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
