/*************************************************************************
    > File Name: 03_String_class.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 17时05分01秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 实现一个自定义的String类
    > Content:
    >   1.保证main函数对正确执行。实现时，记得采用增量编写的方式，逐一测试
 ************************************************************************/

#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class String {
public:
    /* 构造 */
    String()
    :_pstr(new char[1]())
    {
        cout << "String() 无参" << endl;
    }
    String(const char* pstr)
    : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
        cout << "String() 有参" << endl;
    }
    /* 拷贝 */
    String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String &rhs) 拷贝" << endl;
    }
    /* 析构 */
    ~String(){
        if ( _pstr != nullptr ) {
            delete[] _pstr;
            _pstr = nullptr;
            cout << "~String() 析构" << endl;
        }
        cout << "~String() 析构 nullptr" << endl;
    }

    /* 赋值运算符函数 */
    String& operator=(const String& rhs) {
        if ( this != &rhs ) {
            if ( _pstr != nullptr ) {
                delete[] _pstr;
                _pstr = nullptr;
            }
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        cout << "String& operator=(const String& rhs) 赋值运算符" << endl;
        return *this;
    }


    /* 打印 */
    void print() {
        if ( _pstr != nullptr ) {
            cout << _pstr << endl;
        } else {
            cout << endl;
        }
    }
    /* 长度 */
    size_t length() const{
        size_t len = 0;
        if ( _pstr != nullptr ) {
            len = strlen(_pstr);    
        }
        return len;
    }
    /* 返回首地址 char* */
    const char* c_str() const{
        if ( _pstr != nullptr ) {
            return _pstr;
        } else {
            return nullptr;
        }
    }

private:
    char* _pstr;
};

void test01() {
    String str1;
    str1.print();

    String str2 = "hello,world";
    str2.print();

    String str3("wangdao");
    str3.print();

    String str4 = str3;
    str4.print();

    str4 = str2;
    str4.print();

    cout << str4.length() << endl;
    printf("%s\n", str2.c_str());
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
