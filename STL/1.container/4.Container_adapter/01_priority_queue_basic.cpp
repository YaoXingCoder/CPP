/*************************************************************************
    > File Name: 1_priority_queue_basic.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月06日 星期五 20时52分29秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 优先级队列
    > Content:
 ************************************************************************/
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

/* =============== test =============== */
void test0() {
    vector<int> vec = {1, 4, 8, 9, 5, 3};
    /* priority_queue<int> pque(vec.begin(), vec.end()); */
    priority_queue<int> pque;

    for(int i = 0; i != vec.size(); ++i) {
        pque.push(vec[i]);
        cout << "优先依次" << pque.top() << endl;
    }

    while(!pque.empty()) {
        cout << pque.top() << " ";
        /* cout << "优先级依次↓ : " << pque.top() << " "; */
        pque.pop();
    }
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
