#ifndef __SSOSTRING_H
#define __SSOSTRING_H

#include <cstring>
#include <iostream>

class SSOString{
public:
    SSOString();
    SSOString(const char *);
    SSOString(const SSOString &);
    SSOString(SSOString &&);
    
    SSOString & operator=(const SSOString &);
    SSOString & operator=(SSOString &&);

    ~SSOString();

    std::size_t size();
    const char* c_str() const;

    friend std::ostream & operator<<(std::ostream &, const SSOString &);
private:
    static const std::size_t SSO_BUFFER_SIZE = 15; /* 设定短字符长度为 15 */
    union{
        char* _pstr;
        char _local[ SSO_BUFFER_SIZE + 1 ];
    };
    std::size_t _size; /* 记录字符串长度 */
    bool _isSSO; /* 是否短字符串 */
};

#endif
