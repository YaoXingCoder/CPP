/*************************************************************************
    > File Name: default_arguments_06.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月13日 星期二 20时23分34秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 缺省参数
    > Content:
 ************************************************************************/

#include <iostream>
using namespace std;

void func (int x = 0, int y = 0);

void func (int x);

void test0 (){
    func (24,30);
    func (100); /* 不知道调用哪个func */
    func ();
}

int main (int argc, char* argv[]) {
    test0();
    return 0;
}

void func ( int x ) {
    cout << x << endl;
}

void func (int x, int y) {
    cout << "x = " << x << ' ';
	cout << "y = " << y << endl;
}
