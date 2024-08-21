/*************************************************************************
    > File Name: 01_Complex_friend_t.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 11时45分03秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 复合函数
    > Content:
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

    int getReal() const { return _real; }

    int getImage() const { return _image; }

private:
    int _real;
    int _image;
};

/* Complex operator+(const Complex& c1, const Complex& c2) { */
/*     return Complex(c1._real + c2._real, c1._image + c2._image ); */
/* } */

/* 普通函数 */
/* 相较于友元函数, 普通函数破坏类的隐藏性更严重 */
Complex operator+ ( const Complex& c1, const Complex& c2 ) {
    return Complex(c1.getReal() + c2.getReal(), c1.getImage() + c2.getImage());
}


void test01() {
    (Complex(1, 2) + Complex(3, 4)).print();
    /* 本质为 */
    operator+( Complex(1, 2), Complex(3, 4) ).print();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
