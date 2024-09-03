/*************************************************************************
    > File Name: 04_answer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 21时50分27秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
	vector<char> vc = { 'H', 'E', 'L', 'L', 'O' };
	string s(vc.data(), vc.size());
	/* string s(vc.begin(), vc.end()); */
	cout << s << endl;

	return 0;
}
