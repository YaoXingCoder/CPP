/*************************************************************************
    > File Name: 07_other_operations.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月03日 星期二 10时57分04秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 其他操作
    > Content:
 ************************************************************************/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <typename Container>
void display(const Container &con) {
    for(auto &elem : con) {
        cout << elem << "  ";
    }
    cout << endl;
}

void printCapacity(const vector<int> &con) {
    cout << "size() = " << con.size() << endl;
    cout << "capacity() = " << con.capacity() << endl;
}

/* =============== test =============== */
/* vector */
void test0() {
    cout << "sizeof(vector<int>) = " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<long>) = " << sizeof(vector<long>) << endl;

    vector<int> number = {1, 4, 6, 8, 9, 10, 5, 7};
    display(number);
    printCapacity(number);

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(22);
    number.push_back(33);
    display(number);
    printCapacity(number);
    number.pop_back();
    display(number);
    printCapacity(number);

    cout << endl << "vector的清空操作" << endl;
    number.clear();
    number.shrink_to_fit(); // 回收多余的空间
    /* number.resize(0); */
    /* cout << number[5] << endl; */
    printCapacity(number);
}

void test1() {

}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
