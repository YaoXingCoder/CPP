/*************************************************************************
    > File Name: 03_shared_ptr.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 23时11分29秒
    > Mail: JiaZiChunQiu@163.com
    > Title: shared_ptr
    > Content:
 ************************************************************************/
#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

void test0(){
    shared_ptr<int> sp(new int(20));
    shared_ptr<int> sp2(sp);
    cout << *sp << endl;
    cout << *sp2 << endl;
    cout << sp.get() << endl;
    cout << sp2.get() << endl;
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;

    cout << endl;
    shared_ptr<int> sp3(new int(10));
    sp = sp3;
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;
    cout << sp3.use_count() << endl;

    cout << endl;
    vector<shared_ptr<int>> vec;
    vec.push_back(sp); // 发生复制, 不是移动
    cout << sp.use_count() << endl;
    vec.push_back(std::move(sp));
    vec.push_back(std::move(sp2));
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;
    /* cout << *sp2 << endl; */
}

int main(void){
    test0();
    return 0;
}


