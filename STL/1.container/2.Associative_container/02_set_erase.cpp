/*************************************************************************
    > File Name: 02_set_erase.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 22时10分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 删除 erase
    > Content:
 ************************************************************************/
#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

template <typename Container>
void display(const Container &con) {
    for(auto &elem : con) { cout << elem << "  "; }
    cout << endl;
}

void test() {
    set<int> number = {1, 3, 4, 2, 5, 6, 9, 6, 8};
    display(number);

    // 将set中的所有奇数删除
    for(auto it = number.begin(); it != number.end(); ++it) {
        if(*it % 2 == 1) {

            /* auto tmp = it; // 方法3 */
            /* ++it; */
            /* number.erase(tmp); */

            /* number.erase(it++); */ // 方法：2

            it = number.erase(it); // 重置迭代器, 否则删除后指向删除位置的迭代器是失效的
        }
    }

    display(number);
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}

