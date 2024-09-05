/*************************************************************************
    > File Name: 01_answer.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月04日 星期三 21时41分03秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <set>

template <typename Container>
void display(Container & con) {
    for ( int i : con ) { std::cout << i << " "; }
    std::cout << std::endl;
}

/* =============== test =============== */
void test0() {
    std::set<int> res;
    int n = 0, m = 0;
    std::cin >> n >> m;
    int tmp;
    while( n > 0 ) {
        std::cin >> tmp;
        res.insert(tmp);
        --n;
    }
    while( m > 0 ) {
        std::cin >> tmp;
        res.insert(tmp);
        --m;
    }
    display(res);
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
