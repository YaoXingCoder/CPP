/*************************************************************************
    > File Name: 04_answer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 21时41分14秒
    > Mail: JiaZiChunQiu@163.com
    > Title:  学生成绩管理系统
    > Content:
 ************************************************************************/
#include<iostream>
#include <list>
#include <string>

using namespace std;
class Student
{
public:
    Student(string name, int ch, int ma,int e)
    {
                m_Name = name;
		chinese = ch;
		math = ma;
		English = e;
		sum = ch + ma + e;
     }

public:
	string m_Name;  //姓名
	int chinese;   //语文成绩
	int math;   //数学成绩
	int English;//英语成绩
	int sum;//总成绩

};

bool ComparePerson(Student& p1, Student& p2)//定义sort排序从大到小
{
	if (p1.sum == p2.sum)
    {
		return p1.sum < p2.sum;
	}
	else
	{
		return  p1.chinese < p2.chinese;
	}
}

void test()
{

	list<Student> k;

	Student p1("杜雯菲", 88,77,95);
	Student p2("杜蚊分", 67,58,26);
	Student p3("李八八", 95,77,88);
	Student p4("赵二蛋",86,75,68);
	Student p5("王小牛", 86,46,86);
	Student p6("张小哈",89,57,68);

	k.push_back(p1);
	k.push_back(p2);
	k.push_back(p3);
	k.push_back(p4);
	k.push_back(p5);
	k.push_back(p6);

	for (list<Student>::iterator it = k.begin(); it != k.end(); it++)
    {
		cout << "姓名： " << it->m_Name
            << " 语文： " << it->chinese
			<< " 数学： " << it->math
            << " 英语： " << it->English
            << "  总成绩： " << it->sum
            <<  endl;
	}

	cout << "---------------------------------" << endl;
	k.sort(ComparePerson); //排序
	cout << "排序后" << endl;
	for (list<Student>::iterator it = k.begin(); it != k.end(); it++)
    {
		cout << "姓名： " << it->m_Name
            << " 语文： " << it->chinese
			<< " 数学： " << it->math
            << " 英语： " << it->English
            << "  总成绩： " << it->sum << endl;
	}
}

int main()
{
	test();
	return 0;
}
