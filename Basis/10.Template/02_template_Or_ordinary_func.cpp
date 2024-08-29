/*************************************************************************
    > File Name: 02_template_Or_ordinary_func.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 21时06分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 模板函数与普通函数选择
    > Content:
    >   1. 优先选择 ordinary func
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

template<class T>
T add(T t1, T t2) {
    cout << "template1" << endl;
    return t1 + t2;
}

template <class T1, class T2>
T1 add(T1 t1, T2 t2) {
    cout << "template2" << endl;
	return t1 + t2;
}

short add(short s1, short s2){
	cout << "add(short, short)" << endl;
	return s1 + s2;
}

/* =============== test =============== */
void test0() {
    short s1 = 1, s2 = 2;
    /* 显示指定后, 则会调用模板函数 */
    cout << add<short>(s1, s2) << endl;
    cout << add<int>(s1, s2) << endl;
    cout << add<short, short>(s1, s2) << endl;
    cout << add(s1, s2) << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
