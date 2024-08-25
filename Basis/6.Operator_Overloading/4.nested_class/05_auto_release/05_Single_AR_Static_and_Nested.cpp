/*************************************************************************
    > File Name: 05_Single_Auto_release.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 11时31分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 单例对象的释放, 自动释放
    > Content:
    >   1.思想: 静态数据成员可以保持唯一性, 不会每个对象都创建一个
                静态成员能够初始化后, 在程序结束后能够自动释放
    >           成员对象, 若创建后能够保证程序结束后, 自动调用其析构函数, 且能够直接访问外部类的成员
    >   2.实现: 静态对象成员, 静态成员 + 对象成员
    >   3.好处: 不用显示创建 AutoRelease 对象
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Singleton {
    class AutoRelease {
    public:
        AutoRelease() { cout << "AutoRelease() 构造" << endl; }
        ~AutoRelease() { 
            cout << "~AutoRelease() 析构" << endl;
            if (_pInstance ) {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
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
    ~Singleton(){ cout << "~Singleton() 析构" << endl; } /* 因为对象在堆中, 程序结束不会调用析构, 需要手动释放堆上的空间 */

    Singleton(const Singleton& rhs) = delete;
    Singleton& operator=(const Singleton & rhs) = delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
    static AutoRelease _ar;
};
Singleton * Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar;


/* =============== test ============== */
void test0() {
    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(3, 4);
    Singleton::getInstance()->print();
    Singleton::destroy();
}

/* =============== main ============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
