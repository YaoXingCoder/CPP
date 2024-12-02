#ifndef __MYSTRING_H
#define __MYSTRING_H

#include <iostream>

class CowString{
public:
    class CharProxy{
        public:
            CharProxy(CowString &, std::size_t);
            char operator=(char ch); // 赋值重载 str[idx] = 'x';
            char operator=(const CharProxy &); // 连续赋值 str[idx] = str2[idx];
            operator char(); // 类型转换, 用于 char ch = str[idx];
        private:
            CowString & _self;
            std::size_t _idx;
    };
public: 
    CowString();
    CowString(const char*);
    CowString(const CowString &);
    CowString(CowString&&);
    ~CowString();

    CowString & operator=(const CowString &);
    CowString & operator=(CowString &&); 

    CharProxy operator[]( std::size_t );

    std::size_t size() const;
    char* c_str();
    int use_count() const;

    friend std::ostream & operator<<(std::ostream &, const CowString &);
private:
    char* malloc(const char* pstr = nullptr);
    void release();
    void initRefcount();
    void increaseRefcount();
    void decreaseRefcount();
private:
    static const int kRefcountLength = 4;
    char *_pstr;
};

#endif
