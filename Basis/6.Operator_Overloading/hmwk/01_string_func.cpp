/*************************************************************************
    > File Name: 01_string_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 09时25分35秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 自定义一个String类保存字符串内容，实现以下String类的各个函数
    > Content:
 ************************************************************************/

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String {
public:
    /* 构造 */
	String() :_pstr(new char[1]()) { cout << "String() 默认无参" << endl; }
    explicit
    String(const char* pstr) :_pstr(new char[strlen(pstr) + 1]()) {
        strcpy(_pstr, pstr);
        cout << "String(const char* pstr) 有参字符指针" << endl;
    }
    /* 拷贝 */
    explicit
    String(const String& rhs) :_pstr(new char[strlen(rhs._pstr) + 1]()) {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String& rhs) 拷贝构造" << endl;
    }
    /* 析构 */
    ~String() {
        if( _pstr ) {
            delete[] _pstr;
            _pstr = nullptr;
            cout << "~String() delete 析构" << endl;
        }
        cout << "~String() 析构" << endl;
    }

    /* 赋值
     * s1 = s1;
     * s1 = s2;
     * */
    String &operator=(const String & rhs) {
        /* 自复制 判断 */
        if ( this != &rhs ) {
            if ( _pstr ) {
                delete[] _pstr;
                _pstr = nullptr;
            }
            cout << "String& opeartor= (const String&) 赋值重载" << endl;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }
    /* 赋值 const char* */
    String &operator=(const char* pstr) {
        if ( _pstr ) {
            delete[] _pstr;
            _pstr = nullptr;
        }
        _pstr = new char[strlen(pstr) + 1]();
        strcpy(_pstr, pstr);

        cout << "String& operator= (const char*) 赋值重载" << endl;
        return *this;
    }

    /* += 赋值 */
    /* String &operator+=(const String &) { */

    /* } */
    String &operator+=(const char *);

    /* [] 成员访问 */
    char &operator[](std::size_t index);
    const char &operator[](std::size_t index) const;

    /* 字符数 */
    std::size_t size() const;
    /* 字符串 -> 字符指针 */
    const char* c_str() const;

    /* 判断 */
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    /* 比较 */
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    /* 输出 */
    friend std::ostream &operator<<(std::ostream &os, const String& rhs);
    /* 输入 */
    friend std::istream &operator>>(std::istream &is, String &s);

    void print() const{ cout << _pstr << endl; }
private:
    char * _pstr;
};

/* 输出 */
std::ostream& operator<<(std::ostream& os, const String& rhs) {
    if ( rhs._pstr ) { os << rhs._pstr; }
    return os;
}

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

/* =============== test =============== */
void test0() {
    cout << endl << "====== test0  ======" << endl;
    String str1;
    String str2("str2 hello");
    String str2_1(str2); /* 拷贝 */
    /* String str3 = "str3 hello"; /1* 临时有参 + 拷贝 *1/ */
    String str4("str4 hello"); /* 有参 */
    /* String str4 = "str4 hello"; /1* 赋值运算 *1/ */
    str4 = str2;
    str4 = "str4 world";
    str4 = str4;
    /* str4= str3; */
    cout << endl << "====== start ======" << endl;
    /* cout << str1 << endl; */
    /* cout << str2 << endl; */
    /* cout << str3 << endl; */
    cout << str4 << endl;
    cout << endl << "====== end ======" << endl;
}

void test1() {

    cout << endl << "====== test1  ======" << endl;
    cout << endl << "====== start ======" << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
