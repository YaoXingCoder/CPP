/*************************************************************************
    > File Name: SSOString.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 19时58分28秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 短字符串优化
    > Content:
 ************************************************************************/

#include "SSOString.hh"
#include <iostream>

/* 无参 */
SSOString::SSOString() : _size(0), _isSSO(true) {
    std::memset(_local, 0, sizeof(_local));
}

/* 有参 */
SSOString::SSOString(const char* pstr) :_size(std::strlen(pstr)), _isSSO(_size < SSO_BUFFER_SIZE) {
    std::memset(_local, 0, sizeof(_local));
    if (_isSSO) {
        strcpy(_local, pstr);
    } else {
       _pstr = new char[_size + 1]();
       strcpy(_pstr, pstr);
    }
    std::cout << "SSOString() 有参" << std::endl;
}

/* 移动 */
SSOString::SSOString(SSOString&& other) :_size(other._size), _isSSO(other.size()) {
    if ( _isSSO ) {
        std::memset(_local, 0, sizeof(_local));
        strcpy(_local, other._local);
    } else {
         _pstr = other._pstr;
         other._pstr = nullptr;
    }
    other._size = 0;
    other._isSSO = true;
    std::memset(other._local, 0, sizeof(other._local));
    std::cout << "SSOString() 移动" << std::endl;
}

/* 拷贝 */
SSOString::SSOString(const SSOString& other) : _size(other._size), _isSSO(other._isSSO){
    if ( _isSSO ) {
        std::memset(_local, 0, sizeof(_local));
        std::strcpy(_local, other._local);
    } else {
        _pstr = other._pstr;
    }
    std::cout << "SSOString() 拷贝" << std::endl;
}

/* 赋值 */
SSOString & SSOString::operator=(const SSOString & other) {
    if ( this != &other ) {
        if (!_isSSO && _pstr) { 
            delete[] _pstr;
            _pstr = nullptr;
        }

        _isSSO = other._isSSO;
        _size = other._size;
        if ( _isSSO ) {
            std::memset(_local, 0, sizeof(_local));
            std::strcpy(_local, other._local);
        } else {
            _pstr = new char[other._size + 1]();
            std::strcpy(_pstr, other._pstr);
        }
    }
    return *this;
}

/* 移动赋值 */
SSOString & SSOString::operator=(SSOString && other) {
    if ( this != &other ) {
        if ( !_isSSO && _pstr ) {
            delete[] _pstr;
            _pstr = nullptr;
        }

        _isSSO = other._isSSO;
        _size = other._size;

        if ( _isSSO ) {
            std::memset(_local, 0, sizeof(_local));
            std::strcpy(_local, other._local);
        } else {
            _pstr = other._pstr;
            other._pstr = nullptr;
        }

        other._size = 0;
        other._isSSO = true;
        std::memset(other._local, 0, sizeof(other._local));
    }
    std::cout << "SSOString& operator= 移动赋值" << std::endl;
    return *this;
}

/* 析构 */
SSOString::~SSOString() {
    if ( !_isSSO && _pstr ) {
        delete[] _pstr;
        _pstr = nullptr;
    }
    std::cout << "~SSOString()" << std::endl;
}

/* 返回字符串长度 */
std::size_t SSOString::size() {
    return _size;
}

/* 返回字符指针 */
const char* SSOString::c_str() const {
    return _isSSO ? _local : _pstr;
}


/* << 输出操作符重载 */
std::ostream & operator<<(std::ostream & os, const SSOString& rhs) {
    if ( rhs._isSSO ) {
        os << rhs._local;
    } else {
        os << rhs._pstr;
    }
    return os;
}
