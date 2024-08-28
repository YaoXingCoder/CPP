/*************************************************************************
    > File Name: 05_Single_Auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 11时31分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例对象的释放, 自动释放
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

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

    static void destroy(){
         if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

    void print() const { cout << "( " << _ix << ", " << _iy << " )" << endl; }

private:
    Singleton() = default;
    Singleton(int x,int y) : _ix(x) , _iy(y)
    { cout << "Singleton(int,int)" << endl; }
    ~Singleton(){ cout << "~Singleton()" << endl; } /* 因为对象在堆中, 程序结束不会调用析构, 需要手动释放堆上的空间 */

    Singleton(const Singleton& rhs) = delete;
    Singleton& operator=(const Singleton & rhs) = delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = nullptr;


/* =============== test ============== */
void test0() {
    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(3, 4);
    Singleton::getInstance()->print();
    /* Singleton::destroy(); /1* 需要手动释放 *1/ */
}

/* =============== main ============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
