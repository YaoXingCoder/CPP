/*************************************************************************
    > File Name: 01_answer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 21时19分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 编写代码：将一个list中的char *指针元素赋值给一个vector中的string。
    > Content:
    >   1.加入list的定义如下，list<char*> lst= { "hello", "world", "!" };如何将list中的内容赋值给vector<string>
 ************************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;
int main() {
	list<const char*> slist = { "hello", "world", "!" };
	/* vector<string> svec { "hello", "hi" }; */
	vector<string> svec { "1", "2", "3" };

	// 容器类型不同，不能直接赋值
	//	svec = slist;
	// 元素类型相容，可采用范围初始化
	svec.assign(slist.begin(), slist.end());

	cout << svec.capacity() << " " << svec.size() << " " <<
		svec[0] << " " << svec[1] << " " << svec[svec.size() - 1] << endl;

	return 0;
}
