#ifndef __STDUETN_H
#define __STDUETN_H

class Student {
public:
    /* 构造函数 */
    Student();
    Student(const int sid, const char* name, const int age);

    /* 拷贝构造函数 */
    Student(const Student& rhs);

    /* 赋值运算符函数 */
    Student & operator=(const Student& rhs);

    /* 析构函数 */
    ~Student();

    /* 普通函数 */
    void setSID(int sid);
    void setAge(int age);
    void setName(const char* name);
    void print();

private:
    int _sid;
    /* char _name[32]; */
    char* _name;
    int _age;
};

#endif
