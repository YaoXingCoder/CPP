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
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

class String {
public:
    /* 构造 */
	String() :_pstr(new char[1]()) { cout << "String() 默认无参" << endl; }
    String(const char* pstr) :_pstr(new char[strlen(pstr) + 1]()) {
        strcpy(_pstr, pstr);
        cout << "String(const char* pstr) 有参字符指针" << endl;
    }
    /* 拷贝 */
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
    String& operator=(const String & rhs) {
        /* 自复制 判断 */
        if ( this != &rhs ) {
            delete[] _pstr;
            _pstr = nullptr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
            cout << "String& opeartor= (const String&) 赋值重载" << endl;
        }
        return *this;
    }
    /* 赋值 const char* 
     * s1 = "hello" */
    String &operator=(const char* pstr) {
        delete[] _pstr;
        _pstr = nullptr;
        _pstr = new char[strlen(pstr) + 1]();
        strcpy(_pstr, pstr);
        cout << "String& operator= (const char*) 赋值重载" << endl;
        return *this;
    }
    /* String& operator=(const char* pstr) { */
    /*     String tmp(pstr); */
    /*     *this = tmp; */
    /*     cout << "String& operator= (const char*) 赋值重载" << endl; */
    /*     return *this; */
    /* } */

    /* += 赋值 */
    String &operator+=(const String& rhs) {
        char* tmp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
        strcpy(tmp, _pstr);
        strcat(tmp, rhs._pstr);
        delete[] _pstr;
        _pstr = tmp;
        cout << "String &operator+=(const String &)" <<endl;
        return *this;
    }
    String &operator+=(const char* pstr){
        char* tmp = new char[strlen(_pstr) + strlen(pstr) + 1]();
        strcpy(tmp, _pstr);
        strcat(tmp, pstr);
        delete[] _pstr;
        _pstr = tmp;
        /* String tmp(pstr); */
        /* *this += tmp; */
        cout << "String &operator+=(const char* pstr)" <<endl;
        return *this;
    }

    /* [] 成员访问 */
    char &operator[](std::size_t index){
        cout << "char &operator[](std::size_t index)" << endl;
        if ( index < strlen(_pstr)) {
            return *(_pstr + index);
        }else {
            cerr << "index is illegal." << endl;
            static char tmp = '\0';
            return tmp;
        }
    }
    const char &operator[](std::size_t index) const{
        cout << "const char &operator[](std::size_t index) const" << endl;
        if( index < strlen(_pstr) ) { return *(_pstr + index); }
        else { 
            cerr << "index is illegal." << endl;
            static char tmp = '\0';
            return tmp;
        }
    }

    /* 字符数 */
    std::size_t size() const { return strlen(_pstr); }
    /* 字符串 -> 字符指针 */
    const char* c_str() const { return _pstr; }

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

/* 判断 */
bool operator==(const String& lhs, const String& rhs) {
    return !strcmp(lhs._pstr, rhs._pstr);
}
bool operator!=(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr);
}

/* 比较 */
bool operator<(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}
bool operator>(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}
bool operator<=(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}
bool operator>=(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

/* 输出 */
std::ostream &operator<<(std::ostream &os, const String & rhs) {
    if ( rhs._pstr ) { os << rhs._pstr; }
    return os;
}
/* 输入 */
std::istream &operator>>(std::istream &is, String & rhs) {
    if ( rhs._pstr ) {
        delete[] rhs._pstr;
        rhs._pstr = nullptr;
    }
    
    /* 循环从输入缓冲区读取 */
    vector<char> buffer;
    char ch;
    while( (ch = is.get()) != '\n' && ch != '\t' && ch != ' '){
        buffer.push_back(ch);
    }

    /* 复制到_pstr */
    rhs._pstr = new char[buffer.size() + 1]();
    strncpy(rhs._pstr, &(*buffer.begin()), buffer.size());
    /* strncpy(rhs._pstr, &buffer[0], buffer.size()); */
    
    return is;
}

/* + 运算符 */
String operator+(const String & lhs, const String & rhs) {
    String tmp(lhs);
    tmp += rhs;
    cout << "String operator+(const String &, const String &)" << endl;
    return tmp;
}
String operator+(const String & lhs, const char * pstr) {
    String tmp(lhs);
    tmp += pstr;
    return tmp;
}
String operator+(const char * pstr, const String & rhs) {
    String tmp(rhs);
    tmp += pstr;
    return tmp;
}

/* =============== test =============== */
void test0() {
    cout << endl << "====== test0  ======" << endl;
    cout << endl << "------ 构造测试 ------" << endl;
    /* 1. 构造测试 */
    String str1; /* 无参 */
    String str2("str2 hello"); /* 有参 */

    /* cout << endl << "------ 拷贝测试 ------" << endl; */
    /* 2. 拷贝测试 */
    /* String str2_1("str2_1 hello"); */
    /* String str2_2(str2_1); */
    /* String str2_3 = "str2_3 hello"; /1* 临时有参 + 拷贝 *1/ */

    /* 3. 赋值运算符测试 */
    String str3("str3 hello");
    /* cout << endl <<  "------- 赋值运算测试 ------" << endl; */
    /* str3 = str3; /1* 自复制 *1/ */
    /* str3 = str2; /1* string对象 *1/ */
    /* str3 = "str3 world"; /1* 字符串 *1/ */

    /* 4. +|-= 测试 */
    /* cout << endl <<  "------- +|- =运算测试 ------" << endl; */
    /* cout << (str2+=str3) << endl; */
    /* cout << (str2 += "timeover123") << endl; */

    /* 5. [] 成员访问测试 */
    /* const String str4("str4 hello"); */
    /* cout << endl <<  "------- [] 成员访问测试 ------" << endl; */
    /* cout << str2[0] << endl; */
    /* str2[0] = 'S'; */
    /* cout << str2 << endl; */
    /* cout << str4[0] << endl; */
    /* str4[0] = 'S'; /1* error, const 对象只能调用 const 类型 *1/ */
    /* cout << str4 << endl; */

    /* 6. == | != 判断操作符测试 */
    /* cout << endl <<  "------- == | != 判断测试 ------" << endl; */
    /* bool b1 = str3 == str3; */
    /* bool b2 = str3 != str3; */
    /* cout << b1 << endl; */
    /* cout << b2 << endl; */

    /* 7. 比较测试 */
    /* cout << endl <<  "------- 比较测试 ------" << endl; */
    /* cout << (str2 < str3) << endl; */

    /* 8. 输出测试 */
    /* cout << endl <<  "------- 输出测试 ------" << endl; */
    /* cout << str3 << endl; */
    /* cin >> str3; */
    /* cout << str3 << endl; */

    /* 9. + 操作符测试 */
    /* cout << endl << "------ + 操作符测试 -------" << endl; */
    
    /* cout << (str2 + str3) << endl; */ 
    /* cout << (str3 + "world") << endl; */

    cout << endl << "====== start ======" << endl;
    /* cout << str3.size() << endl; */
    /* cout << str3.c_str() << endl; */
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
