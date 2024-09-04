/*************************************************************************
    > File Name: String.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 17时55分41秒
    > Mail: JiaZiChunQiu@163.com
    > Title: CowString 写时复制实现
    > Content:
 ************************************************************************/

#include "String.hh"
#include <cstring>

/* 分配空间 */
char* CowString::malloc(const char* pstr) {
    if ( pstr ) { return new char[std::strlen(pstr) + 1 + kRefcountLength]() + kRefcountLength; }
    else { return new char[kRefcountLength + 1]() + kRefcountLength; }
}

/* 初始化计数器 */
void CowString::initRefcount() {
    /* *(static_cast<int*>(static_cast<void*>(_pstr - kRefcountLength))) = 1; */
    *(reinterpret_cast<int*>(_pstr - kRefcountLength)) = 1;
}
/* 计数器+1 */
void  CowString::increaseRefcount() {
    ++(*(reinterpret_cast<int*>(_pstr - kRefcountLength)));
}
/* 计数器-1 */
void CowString::decreaseRefcount() {
    --(*(reinterpret_cast<int*>(_pstr - kRefcountLength)));
}

/* 获取计数器 */
int CowString::use_count() const {
    return *(reinterpret_cast<int*>(_pstr - kRefcountLength));
}

/* 销毁 */
void CowString::release() {
    decreaseRefcount();
    if ( use_count() == 0 ) {
        delete[] (_pstr - kRefcountLength);
        std::cout << "release heap space" << std::endl;
    }
    _pstr = nullptr;
}

/* 获取字符长度 */
std::size_t CowString::size() const {
    return std::strlen(_pstr);
}

/* 获取指针 */
char* CowString::c_str() {
    return _pstr;
}

/* 默认无参 */
CowString::CowString() :_pstr(malloc()) {
    initRefcount();
    std::cout << "CowString() 无参构造" << std::endl;
}

/* 有参构造 */
CowString::CowString(const char* pstr) : _pstr(malloc(pstr)) {
    initRefcount();
    std::strcpy(_pstr, pstr);
    std::cout << "CowString(const char* pstr) 有参构造" << std::endl;
}

/* 拷贝 */
CowString::CowString(const CowString & other) : _pstr(other._pstr) {
    increaseRefcount();
    std::cout << "CowString(const CowString &) 拷贝" << std::endl;
}

/* 移动构造 */
CowString::CowString(CowString&& other) :_pstr(other._pstr){
    increaseRefcount();
    std::cout << "CowString(CowString&&) 移动构造" << std::endl;
}

/* 析构 */
CowString::~CowString() {
    release();
    std::cout << "~CowString() 析构" << std::endl;
}

/* 赋值重载 */
CowString & CowString::operator=(const CowString & other) {
    if ( this != &other ) {
        release();
        _pstr = other._pstr;
        increaseRefcount();
    }
    return *this;
}

/* 赋值移动 */
CowString & CowString::operator=( CowString && other ) {
    if ( this != &other ) {
        release();
        _pstr = other._pstr;
        increaseRefcount();
    }
    return *this;
}

/* 成员访问重载, 使用代理模式 */
CowString::CharProxy CowString::operator[]( std::size_t idx ) {
    return CharProxy(*this, idx);
}

/* 输出运算符重载 */
std::ostream & operator<<(std::ostream & os, const CowString & obj) {
    return os << obj._pstr;
}

/* ------------------- CharProxy ------------------------ */
/* 有参构造 */
CowString::CharProxy::CharProxy(CowString & self, std::size_t idx) :_self(self), _idx(idx) {
    std::cout << "CharProxy() 有参" << std::endl;
}

/* 特殊赋值重载 */
char CowString::CharProxy::operator=(char ch) {
    if ( _idx < _self.size() ) {
        if ( _self.use_count() > 1 ) {
            _self.decreaseRefcount();
            /* 深拷贝 */
            char * tmp = new char[_self.size() + 1]();
            std::strcpy(tmp, _self._pstr);
            _self._pstr = tmp;
            /* 更新引用计数 */
            _self.initRefcount();
        }
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    } else { 
        std::cout << "out of range" << std::endl;
        static char tmp = '\0';
        return tmp;
    }
}

/* 赋值重载 */
char CowString::CharProxy::operator=(const CowString::CharProxy & other) {
    _self._pstr[_idx] = other._self._pstr[other._idx];
    return _self._pstr[_idx];
}

/* 类型转换 */
CowString::CharProxy::operator char() {
    return _self._pstr[_idx];
}
