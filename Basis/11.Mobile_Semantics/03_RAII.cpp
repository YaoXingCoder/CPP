/*************************************************************************
    > File Name: 03_RAII.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 22时44分13秒
    > Mail: JiaZiChunQiu@163.com
    > Title: RAII 封装
    > Content:
 ************************************************************************/
#include <iostream>
using std::cout;
using std::endl;

class Point {
public:
    Point(int x,int y) : _ix(x) , _iy(y) { /* cout << "Point(int,int)" << endl; */}

    void print() const{
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;
    }

    ~Point(){}
private:
    int _ix;
    int _iy;
};

template <class T>
class RAII {
public:
    RAII(T * data) : _data(data) {
        cout << "RAII(T*)" << endl;
    }

    ~RAII(){
        cout << "~RAII()" << endl;
        if(_data){
            delete _data;
            _data = nullptr;
        }
    }

    T * operator->(){ return _data; }

    T & operator*(){ return *_data; }

    T * get() const{ return _data; }

    void reset(T * data){
        if(_data){
            delete _data;
            _data = nullptr;
        }
        _data = data;
    }

    RAII(const RAII &) = delete;
    RAII & operator=(const RAII &) = delete;
private:
    T * _data;
};

void test0(){
    RAII<Point> ra(new Point(1,3));
    ra->print();

    ra.reset(new Point(5,6));
    (*ra).print();

    cout << endl <<  "--------- int -----------"  << endl;

    RAII<int> ra2(new int(10));
    cout << *ra2 << endl;
    cout << ra2.get() << endl;

    ra2.reset(new int(20));
    cout << *ra2 << endl;
    cout << ra2.get() << endl;

    cout << endl << "----------- end --------------" << endl;
}

int main(void){
    test0();
    return 0;
}
