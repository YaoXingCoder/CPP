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

    friend
    Complex add(const Complex& lhs, const Complex& rhs);
private:
    int _real;
    int _image;
};

Complex add(const Complex& lhs, const Complex & rhs) {
    return Complex(lhs._real + rhs._real, lhs._image + rhs._image );
}

void test01() {
    add(Complex(1, 2), Complex(3, 4)).print();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
