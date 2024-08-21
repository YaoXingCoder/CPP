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

    /* +  */
    friend
    Complex operator+(const Complex& c1, const Complex& c2);

    /* - */
    friend
    Complex operator-(const Complex& c1, const Complex& c2);

private:
    int _real;
    int _image;
};

Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1._real + c2._real, c1._image + c2._image);
}

Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex(c1._real - c2._real, c1._image - c2._image);
}

void test01() {
    Complex c1(1, 2);
    Complex c2(3, 4);
    
    (c1 + c2).print();
    (c2 - c1).print();
    /* 本质 */
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
