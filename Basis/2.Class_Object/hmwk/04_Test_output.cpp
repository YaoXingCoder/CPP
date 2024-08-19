/*************************************************************************
    > File Name: 04_Test_output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月17日 星期六 17时51分18秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int i = 1;

class Test
{
public:
    /* 这里初始化的顺序先后 只与 声明时的顺序 有关
     * 与初始化列表的顺序并无关系 */
	Test()
	:_fourth(_third)
	,_second(i++)
	,_third(i++)
	,_first(i++)
	{
		_third = i;
	}
	void print()
	{
		cout << "result : " << _first + _second + _third + _fourth << endl;
        cout << _first << endl; /* 1 */
        cout << _second << endl; /* 2 */
        cout << _third << endl; /* 4 */
        cout << _fourth << endl; /* 4 */
	}
private:
	int _first;
	int _second;
	int _third;
	int &_fourth;
};

void test01() {
    Test test;
    test.print();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
