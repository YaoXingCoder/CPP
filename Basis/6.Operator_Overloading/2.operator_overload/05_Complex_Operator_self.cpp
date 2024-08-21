/*************************************************************************
    > File Name: 01_Complex_friend_t.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 11时45分03秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 自增自减 和 +=|-=
    > Content:
    >   1.会修改操作符的值, 使用成员函数
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Complex {
public:
    Complex(int real = 0, int image = 0) 
        : _real(real)
        , _image(image)
    {
        cout << "Complex(int x, int y) 构造" << endl;
    }

    void print() const{
        cout << _real << " + " << _image << "i" << endl;
    }
    
    /* += */
    Complex& operator+=(const Complex& rhs) {
        _real += rhs._real;
        _image += rhs._image;
        return *this;
    }

    /* -= */
    Complex& operator-=(const Complex& rhs) {
        _real -= rhs._real;
        _image -= rhs._image;
        return *this;
    }

    /* 前置++ */
    Complex& operator++() {
        ++_real;
        ++_image;
        return *this;
    }

    /* 后置++ */
    Complex operator++(int){
        Complex tmp(*this);
        ++_real;
        ++_image;
        return tmp;
    }

    /* 前置-- */
    Complex& operator--() {
        --_real;
        --_image;
        return *this;
    }

    /* 后置-- */
    Complex operator--(int) {
        Complex tmp(*this);
        --_real;
        --_image;
        return tmp;
    }

private:
    int _real;
    int _image;
};

void test01() {
    Complex c1(1, 2);
    Complex c2(3, 4);

    /* (c1 += c2).print(); */
    /* (c1 -= c2).print(); */
    /* 本质 */
    /* c1.operator+=(c2); */
    /* c1.operator-=(c2); */

    (++c1).print();
    /* c1.operator++(); /1* 本质 *1/ */

    (c1++).print();
    /* c1.operator++(10); /1* 本质 10 无作用 *1/ */
    /* c1.print(); */


    (--c1).print();
    /* c1.operator--(); */
    (c1--).print();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
