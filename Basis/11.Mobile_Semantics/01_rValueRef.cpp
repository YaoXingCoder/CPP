/*************************************************************************
    > File Name: rValueRef.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 22时23分18秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 右值引用
    > Content:
 ************************************************************************/

#include <iostream>

#include <iostream>
using std::cout;
using std::endl;

void test0(){
    int a = 10;
    cout << &a << endl;
    int && ref = std::move(a);
    cout << &a << endl;
    cout << &ref << endl; // ref本身是左值

    // 通过这个右值引用进行修改操作
    // 本体仍然会进行修改
    ref = 100;
    cout << a << endl;
}


int gNum = 100;
int func1(){
    return gNum;
}

int & func2(){
    return gNum;
}

int && func3(){
    return std::move(gNum);
}


void test1(){
    //func1的返回值是gNum的副本，属于右值
    /* &func1(); */

    //func2的返回值是绑定到gNum的一个匿名的左值引用
    //这个引用变量本身属于左值
    cout << &func2() << endl;
    cout << &gNum << endl;

    //func3的返回值是一个间接绑定到gNum的
    //一个匿名的右值引用
    //这个引用变量本身属于右值
    /* &func3(); */
    int && ref = func3();

    //右值引用本身属于左值还是右值
    //取决于是否有名字
    //有名字的右值引用就是左值
    cout << &ref << endl;
}

//注意以下的问题！
/* int && func4(){ */
/*     int a = 1, b = 2; */
/*     return a + b; */
/* } */

/* void test2(){ */
    //func4的返回值是右值属性的右值引用
    //无法有效地延长对象的生命周期
    //所以func4的返回值实际上是一个悬空引用
    /* int && ref = func4(); */
    /* cout << &ref << endl; */
    /* ref = 100; */
/* } */

/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test2(); */
    test0();
    return 0;
}
