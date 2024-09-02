/*************************************************************************
    > File Name: 01_auto_ptr.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 22时54分15秒
    > Mail: JiaZiChunQiu@163.com
    > Title: auto_ptr
    > Content:
 ************************************************************************/
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::auto_ptr;

void test0(){
    int * p = new int(20);
    auto_ptr<int> ap(p);
    cout << p << endl;
    cout << ap.get() << endl;
    cout << *ap << endl;

    /* auto_ptr<int> ap2 = ap; */
    auto_ptr<int> ap2(ap);
    cout << ap2.get() << endl;
    cout << *ap2 << endl;

    // auto_ptr提供了拷贝构造
    // 但是拷贝构造底层实际是移交管理权的处理方式
    cout << *ap << endl;
}

int main(void){
    test0();
    return 0;
}
