/*************************************************************************
    > File Name: 01_cow_string.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 16时15分25秒
    > Mail: JiaZiChunQiu@163.com
    > Title: Cow 实现 string
    > Content:
 ************************************************************************/

#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

/* ================================  类声明 ================================= */

class CowString{
    class CharProxy{

    };
public:
    CowString();
    CowString(const char* pstr);
    ~CowString();
    CowString(const CowString& rhs);
    CowString& operator=(const CowString& rhs);

    /* 字符串长度 */
    int size() const{ return strlen(_pstr); }
    /* 获取计数器 */
    int get_count() const { return *(int*)(_pstr - kRefcoutnLength); }

    /* 返回 char* 类型指针 */
    const char* c_str() const{ return _pstr; }
    /* << 友元输出运算符 */ 
    friend ostream& operator<< (ostream& os, const CowString& rhs);

    /* [] 下标访问 */
    char& operator[](size_t idx);
    /* [] 下标访问 优化 
     * 返回不是引用 */
    /* CharProxy operator[](size_t idx); */
private:
    /* 空间开辟 */
    char* malloc(const char* pstr = nullptr) {
        if ( pstr ) { return new char[strlen(pstr) + 1 + kRefcoutnLength]() + kRefcoutnLength; }
        else { return new char[kRefcoutnLength + 1]() + kRefcoutnLength;}
    }

    /* 回收空间 */
    void release() {
        decreaseRefcount();
        if (get_count() == 0) {
            delete[] (_pstr - kRefcoutnLength);
            cout << "release delete[]" << endl;
        }
        cout << "release" << endl;
        _pstr = nullptr;
    }

    /* 计数器 */
    void initRefcout(){ *(int*)(_pstr - kRefcoutnLength) = 1; }
    void increaseRefcount() { ++*(int*)(_pstr - kRefcoutnLength); }
    void decreaseRefcount() { --*(int*)(_pstr - kRefcoutnLength); }

    /* 成员变量 */
    static const int kRefcoutnLength = 4; /* 替换魔法变量 */
    char* _pstr;
};
/* ================================  类定义 ================================= */

/* 无参 */
CowString::CowString() : _pstr(malloc()) {
    initRefcout();
    cout << "CowString() 无参" << endl;
};

/* 有参 */
CowString::CowString(const char* pstr) : _pstr(malloc(pstr)) { 
    strcpy(_pstr, pstr);
    increaseRefcount();
    cout << "CowString(const char* pstr) 有参" << endl;
}

/* 析构 */
CowString::~CowString(){
    cout << "~CowString 析构" << endl;
    release();
}

/* 拷贝 */
CowString::CowString(const CowString& rhs) : _pstr(rhs._pstr) {
    increaseRefcount();
    cout << "CowString(const CowString& rhs) 拷贝" << endl;
}

/* 赋值 */
CowString& CowString::operator=(const CowString& rhs){
    /* 自复制 判断 */
    if ( this != &rhs ) {
        release(); /* 尝试回收 */
        _pstr = rhs._pstr; /* 浅拷贝 */
        increaseRefcount(); /* 新空间引用计数 + 1 */
    }
    cout << "operator= 赋值" << endl;
    return *this;
}

/* << 输出运算符 */
ostream& operator<<(ostream& os, const CowString& rhs) {  return os << rhs._pstr; }

/* [] 成员访问运算符
 * TODO 成员访问时, 如果计数器 > 1, 不管有没有修改都会深拷贝, 需要优化
 * */
#if 1
char& CowString::operator[](size_t idx){
    if ( -1 < idx < size() ) { 
        if ( get_count() > 1 ) {
            decreaseRefcount();
            /* 深拷贝 */
            char* tmp = malloc(_pstr);
            strcpy(tmp, _pstr);
            _pstr = tmp; /* 重定向指向 */
            /* 初始化 计数器 */
            initRefcout();
        }
        return _pstr[idx];
    }
    else {
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}
#endif

/* ================================  类测试 ================================= */

void test0() {
    CowString str1;

    cout << endl << "===== start =====" << endl;
    cout << "str1 : " << str1 << endl;
    cout << "str1 get_count : " << str1.get_count() << endl;

    cout << endl  << "====== str 1 2 ========" << endl;
    CowString str2 = str1;
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str1 get_count : " << str1.get_count() << endl;
    cout << "str2 get_count : " << str2.get_count() << endl;

    cout << endl << "====== str 3 4 ========" << endl;
    CowString str3 = "hello";
    CowString str4 = str3;
    cout << "str3 : " << str3 << endl;
    cout << "str4 : " << str4 << endl;
    cout << "str3 get_count : " << str3.get_count() << endl;
    cout << "str4 get_count : " << str4.get_count() << endl;

    cout << endl << "====== str 1 2 3 4 ========" << endl;
    str2 = str3;
    str1 = str2;
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str3 : " << str3 << endl;
    cout << "str4 : " << str4 << endl;
    cout << "str1 get_count : " << str1.get_count() << endl;
    cout << "str2 get_count : " << str2.get_count() << endl;
    cout << "str3 get_count : " << str3.get_count() << endl;
    cout << "str4 get_count : " << str4.get_count() << endl;

    cout << endl << "====== end =====" << endl;
}

void test1() {
    CowString str1("world");

    cout << endl << "===== start =====" << endl;
    cout << str1 << endl;
    cout << str1[0] << endl;
    str1[0] = 'W';
    cout << str1 << endl;

    cout << endl << "====== end =====" << endl;
}

int main (int argc, char* argv[]) {
    /* test0(); */
    test1();
    return 0;
}
