/*************************************************************************
    > File Name: 03_average_score.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月02日 星期一 20时59分13秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 有五名选手ABCDE，10个评委打分，去掉最高分和最低分，求出每个选手的平均分。
    > Content:
    >   1.创建Person类，定义name，score成员属性；创建五名选手存放到vector容器中；
    >   2.遍历vector容器，首先10个评委的打分存放到deque容器中，sort算法对分数排序，去掉最高最低分；
    >   3.deque容器遍历，进行剩余分数的累加，求平均；
    >   4.输出每个选手的姓名，成绩
    >   提示：还是容器vector与deque的基本使用
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>

#define NAME_SIZE 64

class Person {
public:
    Person() :_score(-1) { memset(_name, 0, sizeof(_name)); }
    Person(const char* pstr, int score) : _score(score) {
        if (std::strlen(pstr) > NAME_SIZE) { std::cerr << "name is too long" << std::endl;}
        std::strcpy(_name, pstr);
    }

    void setScore(double score) {
        _score = score;
    }

    void print() const {
        std::cout << _name << " : " <<  _score << std::endl;
    }

    ~Person() {}
private:
    char _name[NAME_SIZE];
    double _score;
};

bool customCompare(int a, int b) {
    return a > b; // a > b 表示降序
}

/* =============== test =============== */
void test0() {
    std::vector<Person> vec_Per{Person("hello", 0.0), Person("word", 0.0), Person("abc", 0.0), Person("123", 0.0), Person("time", 0.0)};
    std::deque<double> dq_judge(10);

    /* 生成随机数 */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(60.0, 100.0);

    /* 模式是个评委 */
    for ( Person person : vec_Per ) {
        std::cout << std::endl << "-------------------------" << std::endl;
        double sum_score = 0.0;
        /* 产生随机值 */
        for ( double& d_judge : dq_judge ) {
            d_judge = distrib(gen);
            sum_score += d_judge;
        }
        /* 排序 */
        /* std::sort(dq_judge.begin(), dq_judge.end(), customCompare); */
        std::sort(dq_judge.begin(), dq_judge.end());
        for( double& d_judge : dq_judge ) {
            std::cout << d_judge << " ";
        }
        std::cout << std::endl;
        sum_score -= dq_judge[0];
        sum_score -= dq_judge[dq_judge.size() - 1];

        /* 求平均值存入Person */
        person.setScore( sum_score / (double)(dq_judge.size() - 2));
        person.print();
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
