/*************************************************************************
    > File Name: 04_student_achievement_management_system.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 20时23分26秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 学生管理系统
    > Content:
    >   1 .制作一个学生成绩单管理系统
    >   2 .将student自定义数据类型进行排序，student中属性有姓名、年龄、语文成绩，数学成绩，英语成绩
    >   排序规则：按照总成绩sum进行降序，如果总成绩sum相同按照语文成绩进行降序
    >
    >   熟悉list容器的基本操作：包括初始化、遍历、排序等等
 ************************************************************************/

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

class Student {
public:
    Student(const char* name, int age, double chinese, double math, double english)
    : _name(name)
    , _age(age)
    , _chinese(chinese)
    , _math(math)
    , _english(english)
    {}

    ~Student() {}

    const double sum_score() const { return _chinese + _math + _english; }
    const double get_chinese() const { return _chinese; }
    const double get_math() const { return _math; }
    const double get_english() const { return _english; }

    friend  std::ostream & operator<<(std::ostream & os, const Student & obj);
private:
    std::string _name;
    int _age;
    double _chinese;
    double _math;
    double _english;
};

std::ostream & operator<<(std::ostream & os, const Student & obj) {
    char str[128] = { 0 };
    sprintf(str, "name : %s, age : %d, chinese : %.2f, math : %.2f, english : %.2f, sum : %.2f", obj._name.c_str(), obj._age, obj._chinese, obj._math, obj._english, obj.sum_score());
    std::string tmp(str);
    /* std::cout << tmp.size() << std::endl; */
    return os << tmp;
}

template <typename Container>
void display( Container & con  ) {
    for ( Student & stu : con ) { std::cout << stu << std::endl; }
}

struct {
    bool operator()(const Student & lhs, const Student & rhs) {
        if (  lhs.sum_score() != rhs.sum_score() ) {
            return lhs.sum_score() > rhs.sum_score();
        } else {
            return lhs.get_chinese() > rhs.get_chinese();
        }
    }
} Compare;

/* =============== test =============== */
void test0() {
    std::list<Student> ls_st;
    ls_st.emplace_back("1", 10, 88.2, 81.2, 82.2);
    ls_st.emplace_back("2", 11, 87.3, 90.5, 66.1);
    ls_st.emplace_back("3", 12, 81.6, 85.2, 91.5);
    ls_st.emplace_back("4", 13, 73.8, 78.1, 80.3); // 4 , 5 相同, 5 语文 > 4
    ls_st.emplace_back("5", 14, 78.1, 80.3, 73.8);
    ls_st.emplace_back("6", 15, 68.0, 75.8, 88.8);
    ls_st.emplace_back("7", 16, 95.5, 87.9, 91.3);
    ls_st.emplace_back("8", 17, 83.3, 92.2, 91.9);
    
    ls_st.sort(Compare);

    display(ls_st);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
