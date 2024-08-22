/*************************************************************************
    > File Name: 01_Complex_friend_t.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 11时45分03秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 输入输出流 << >>
    > Content:
    >   1.会修改操作符的值, 使用成员函数
    >   2.输出 << 
    >   3.但该形式输出的表达式为 cx1 << cout, 与平常使用相违背, 所以需要再多一个参数接收 cout
    >   4.因此只能使用友元函数形式
 ************************************************************************/

#include <iostream>
#include <string>
#include <ostream>
#include <limits>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ostream;
using std::istream;

void inputInt(istream& is, int& num);

class Complex {
public:
    Complex(int real = 9, int image = 9)  : _real(real) , _image(image)
    { cout << "Complex(int x, int y) 构造" << endl; }

    void print() const{ cout << _real << " + " << _image << "i" << endl; }

    /*  <<  
     *  效果只能是 cx1 << cout
     *  与内置类型的使用不一致
     *  因为 << 为两个操作个数
     *  如果再接收 cout 则变为三个（成员函数 自带 this指针操作数）, 破坏了 << 的规则
     *  所以只能友元函数
     *  */
    /* ostream& operator<<(ostream& os) { */
    /*     os << _real << " + " << _image << " i "; */
    /*     return os; */
    /* } */
    friend ostream& operator<<(ostream& os, const Complex& rhs);

    /* >> 运算符, 表达式形式: cin >> cx1 */
    friend istream& operator>>(istream& os, Complex& rhs);
private:
    int _real;
    int _image;
};

/* << 输出运算符 */
ostream& operator<<(ostream& os, const Complex& rhs) {
    os << rhs._real << " + " << rhs._image << " i ";
    return os;
}

/* >> 输入运算符 */
istream& operator>>(istream& is, Complex& rhs){
    /* cout << "请输入实部:" << endl; */
    /* is >> rhs._real; */
    inputInt(is, rhs._real);
    /* cout << "请输入虚部:" << endl; */
    /* is >> rhs._image; */
    inputInt(is, rhs._image);

    /* 链式输入, 无法处理输入错误的情况
     * 例如:
     * 第一次输入错误, 紧接着就是输入第二次, 中间没有余力处理第一次的出错
     * C++ 11 cin 的描述
     * If extraction fails, zero is written to value and failbit is set. 
     * If extraction results in the value too large or too small to fit in value
     * 若释出失败，则写入零到 value 并设置 failbit 
     * 若释出结果对于 value 过大或过小，则写入 std::numeric_limits::max() 或 std::numeric_limits::min() 并设置 failbit 标志。
     * */
    /* is >> rhs._real >> rhs._image; */
    return is;
}

void inputInt(istream& is, int& num) {
    cout << "please enter data of type int :> ";
    cout.flush();
    while( is >> num, !is.eof() ) {
        if( is.bad() ) {
            cout << "istream has broken!" << endl;
            return;
        }else if ( is.fail() ) {
            is.clear(std::ios::goodbit); /* 清除所有的错误的状态标志 */
            is.ignore( std::numeric_limits<std::streamsize>::max(), '\n'); /* 读且取走并舍弃字符，直至发现给定字符 */
            cout << "enter error, please again :> ";
        }else if ( is.good() ) {
            break;
        }
    }
}

/* ================= 测试 ==================== */

/* <<  */
void test01() {
    Complex cx1(1, 2);
    cx1.print();

    /* 成员函数形式 */
    /* cx1 << cout << endl; */
    /* cx1.operator<<(cout); /1* 本质 *1/ */

    /* 友元函数形式 */
    cout << cx1 << endl;
    /* operator<<(cout, cx1) << endl; /1* 本质 *1/ */
}

/* >> */
void test02() {
    Complex cx1(1, 2);
    cx1.print();

    /* 若采用链式输入, 第一次输入错误后直接被写入0, 紧接着第二次的输入不会执行 
     * 所以结果为 0 + 2i;
     */
    cin >> cx1;
    cout << cx1;

    /* 如果 cin 输入出错, num 的值会被写入0 */
    /* int num = 10; */
    /* cin >> num; */
    /* cout << num << endl; */
}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
