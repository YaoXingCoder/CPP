/*************************************************************************
    > File Name: 02_answer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 21时21分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 从标准输入读取 string 序列，存入一个 deque 中。编写一个循环，用迭代器打印 deque 中的元素。
    > Content:
    >   1.熟悉deque的基本函数的使用方式
 ************************************************************************/
#include<iostream>
#include<deque>
#include<string>
#include<cstring>

using namespace std;

int main() {
	deque<string> dq;
	string word;
	while (cin >> word) {
		dq.push_back(word);
	}
	for (auto it = dq.cbegin(); it != dq.cend(); ++it){
		cout << *it << endl;
	}

	return 0;
}
