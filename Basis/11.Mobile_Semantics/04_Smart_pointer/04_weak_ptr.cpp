/*************************************************************************
    > File Name: 04_weak_ptr.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月31日 星期六 00时24分45秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

void test0(){
    shared_ptr<int> sp(new int(30));
    /* shared_ptr<int> sp; */
    weak_ptr<int> wp;
    wp = sp;
    weak_ptr<int> wp2(sp);
    weak_ptr<int> wp3(wp);
    /* cout << sp.use_count() << endl; */
    /* cout << wp.use_count() << endl; */
    /* cout << wp2.use_count() << endl; */
    /* cout << wp3.use_count() << endl; */

    /* if(sp){ */
    /*     cout << *sp << endl; */
    /* } */
    /* *wp; */

    shared_ptr<int> sp2 = wp.lock();
    if(sp2){
        cout << "提升成功，存在关联的空间" << endl;
        cout << *sp2 << endl;
    }else{
        cout << "没有关联的空间" << endl;
    }

    cout << sp.use_count() << endl;
    /* *wp; */

    if(!wp.expired()){
        cout << "有关联空间" << endl;
    }else{
        cout << "没有关联空间" << endl;
    }
}

int main(void){
    test0();
    return 0;
}

