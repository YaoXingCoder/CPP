/*************************************************************************
    > File Name: main.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月15日 星期四 23时28分17秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "02_student.hh"
#include <iostream>
using std::cout;
using std::endl;

void test01 () {
    Student stu1;
    stu1.setSID(1);
    stu1.setAge(12);
    stu1.setName("Tom");

    Student stu2(2, "Jack", 13);
    /* Student stu3(3, "Mary", 14); */

    Student stu3 = Student(3, "Mary", 14);
    /* Student stu4 = stu3; */ 

    stu1.print();
    stu2.print();
    stu3.print();
    /* stu4.print(); */
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
