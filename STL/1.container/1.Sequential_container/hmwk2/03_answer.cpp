/*************************************************************************
    > File Name: 03_answer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 21时39分30秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 从一个 list 拷贝元素到两个 deque 中。值为偶数的所有元素都拷贝到一个 deque 中，而奇数值元素都拷贝到另一个 deque 中。
    > Content:
    >   1.熟悉list容器与deque容器的基本操作，包括初始化、遍历、插入等等
 ************************************************************************/

#include<iostream>
#include<deque>
#include<list>
#include<string>
using namespace std;

int main() {
	list<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8 };
	deque<int> oddDq, evenDq;

	for (auto iter = lst.begin(); iter != lst.end();iter++){
		if (*iter & 1){
			oddDq.push_back(*iter);
		}
		else{
			evenDq.push_back(*iter);
		}
	}
	for (auto iter = oddDq.cbegin(); iter != oddDq.cend(); iter++){
		cout << *iter << " ";
	}
	cout << endl;
	for (auto iter = evenDq.cbegin(); iter != evenDq.cend(); iter++){
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}
