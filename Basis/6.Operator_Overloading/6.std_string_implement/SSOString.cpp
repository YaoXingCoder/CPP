/*************************************************************************
    > File Name: 01_diff_storage_union_string.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月28日 星期三 21时46分13秒
    > Mail: JiaZiChunQiu@163.com
    > Title: SSO字符串的特点（即现行的std::string），针对不同长度的字符串内容会采取不同的存储方式。
    > Content: 请了解一下union的用法，验证长字符串和短字符串的不同存储方式。
 ************************************************************************/
/* #include <string.h> */
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

/* 短字符串优化 简单实现验证 */
class SSOString{
private:
    static const std::size_t SSO_BUFFER_SIZE = 15; /* 设定短字符串长度为 15 */
    union{
        char _localBuffer[SSO_BUFFER_SIZE + 1]; /* +1 用于null */
        char *_heapBuffer;
    };
    std::size_t _size; /* 当前字符串长度 */
    bool _isSSO;
public:
    /* 无参 */
    SSOString() : _size(0), _isSSO(true) {
        _localBuffer[0] = '\0';
    }

    /* 有参 */
    SSOString(const char* pstr) : _size(std::strlen(pstr)), _isSSO(_size <= SSO_BUFFER_SIZE) {
        if (_isSSO) {
            std::strcpy(_localBuffer, pstr);
        } else {
            _heapBuffer = new char[_size + 1]();
            std::strcpy(_heapBuffer, pstr);
        }
    }

    /* 拷贝 */
    SSOString(const SSOString& other) :_size(other._size), _isSSO(other._isSSO) {
        if (_isSSO) {
            std::strcpy(_localBuffer, other._localBuffer);
        } else {
            _heapBuffer = new char[_size + 1]();
            std::strcpy(_heapBuffer, other._heapBuffer);
        }
    }

    /* 赋值 
     * 自复制
     * */
    /* SSOString& operator=(const SSOString& other) { */
    /*     if ( this != &other ) { */
    /*         if(other._isSSO) { */
    /*             if ( _isSSO ) { */
    /*                 std::memset(_localBuffer, 0, _size); */
    /*             } else { */
    /*                 delete[] _heapBuffer; */
    /*                 _heapBuffer = nullptr; */
    /*             } */
    /*             std::strcpy(_localBuffer, other._localBuffer); */
    /*             _size = other._size; */
    /*             _isSSO = other._isSSO; */
    /*         } else { */
    /*             if ( _isSSO ) { */
    /*                 std::memset(_localBuffer, 0, _size); */
    /*             } else { */
    /*                 delete[] _heapBuffer; */
    /*                 _heapBuffer = nullptr; */
    /*             } */
    /*             std::strcpy(_heapBuffer, other._heapBuffer); */
    /*             _size = other._size; */
    /*             _isSSO = other._isSSO; */
    /*         } */
    /*     } */
    /*     return *this; */
    /* } */

    SSOString& operator=(const SSOString& other) {
        if (this != &other) {
            if (!_isSSO && _heapBuffer) {
                delete[] _heapBuffer;
            }

            _size = other._size;
            _isSSO = other._isSSO;

            if (_isSSO) {
                std::strcpy(_localBuffer, other._localBuffer);
            } else {
                _heapBuffer = new char[_size + 1];
                std::strcpy(_heapBuffer, other._heapBuffer);
            }
        }
        return *this;
    }

    SSOString& operator=(const char* pstr) {
        if ( !_isSSO && _heapBuffer ) { delete[] _heapBuffer; }

        _size = std::strlen(pstr);
        _isSSO = _size <= SSO_BUFFER_SIZE;

        if ( _isSSO ) {
            std::strcpy(_localBuffer, pstr);
        } else {
            _heapBuffer = new char[_size + 1]();
            std::strcpy(_heapBuffer, pstr);
        }
        return *this;
    }

    ~SSOString() {
        if ( !_isSSO && _heapBuffer ) {
            delete[] _heapBuffer;
        }
    }

    const char* c_str() const {
        return _isSSO ? _localBuffer : _heapBuffer;
    }

    std::size_t size() const {
        return _size;
    }

};

/* =============== test =============== */
void test0() {
    SSOString shortStr("Short");
    SSOString longStr("This is a very long string that exceeds the SSO limit");

    std::cout << "Short string: " << shortStr.c_str() << ", size: " << shortStr.size() << std::endl;
    printf("%p\n", shortStr.c_str());
    std::cout << "Long string: " << longStr.c_str() << ", size: " << longStr.size() << std::endl;
    printf("%p\n", longStr.c_str());
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
