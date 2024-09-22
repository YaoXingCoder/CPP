/*************************************************************************
    > File Name: Task.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月15日 星期日 10时19分48秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include "Task.hh"

#include <iostream>
#include <cstdlib>
#include <ctime>

Task::~Task() {}

void MyTask::process(){
    ::srand(::clock());
    int number = ::rand() % 100;
    std::cout << ">> MyTask number = " << number << std::endl;
};
