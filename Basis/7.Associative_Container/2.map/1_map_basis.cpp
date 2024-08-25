/*************************************************************************
    > File Name: 2_map_basis.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月24日 星期六 11时33分00秒
    > Mail: JiaZiChunQiu@163.com
    > Title: map 使用
    > Content:
    >   1.map 的构造使用
    >   2.map 的遍历
    >   3.map 的单插 和 多插
    >   4.取下标
 ************************************************************************/

#include <iostream>
#include <map>
#include <string>
#include <utility>
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;

/* =============== test =============== */
void test0() {
    cout << endl << "===== test0 =====" << endl;
    pair<int, string> pa1(1, "hello");
    pair<int, string> pa2(2, "world");
    pair<int, string> pa3(3, "test");

    map<int, string> map_pa1 = { pa1, pa2, pa3 };

    cout << endl << "===== start =====" << endl;

    map<int, string>::iterator map_it1 = map_pa1.begin();
    while(map_it1 != map_pa1.end()) {
        cout << "key : "  << map_it1->first << ", value : " << map_it1->second <<endl;
        ++map_it1;
    }

    cout << "--- for ---" << endl;
    for ( pair<int ,string> pa : map_pa1 ){
        cout << "key : "  << pa.first << ", value : " << pa.second <<endl;
    }

    cout << endl << "===== end =====" << endl;
}

/* 单个插入 */
void test1() {
    cout << endl << "===== test1 =====" << endl;
    pair<int, string> pa1(4, "fuluolida");
	map<int, string> m1 = {
        {1,"hello"},
        {2,"world"},
        {3,"wangdao"},
    }; 
    pair<map<int, string>::iterator, bool> p_map1 = m1.insert(pa1);
    m1.insert(pair<int, string>(5, "lshanki"));

    cout << endl << "===== start =====" << endl;
    
    cout << (*(p_map1.first)).first << " " << p_map1.first->second << endl;
    cout << p_map1.second << endl;

    for(pair<int, string> pa : m1) {
        cout << "key : "  << pa.first << ", value : " << pa.second <<endl;
    }

    cout << endl << "===== end =====" << endl;
}

/* 多个插入 */
void test2() {
    cout << endl << "===== test2 =====" << endl;
	map<int, string> m1 = {
        {1,"hello"},
        {2,"world"},
        {3,"wangdao"},
    }; 

    map<int, string> m2 = { {4, "freedom"}, {5, "amazing"} };
    m1.insert(m2.begin(), m2.end());

    m1.insert({{6, "timeover"}, {7, "lucky"}});

    cout << endl << "===== start =====" << endl;
    for(pair<int, string> pa : m1) {
        cout << "key : "  << pa.first << ", value : " << pa.second <<endl;
    }
    cout << endl << "===== end =====" << endl;
}

/* 取下标 */
void test3() {
    cout << endl << "===== test3 =====" << endl;
	map<int, string> m1 = {
        {1,"hello"},
        {2,"world"},
        {3,"wangdao"},
    }; 

    m1.insert({{6, "timeover"}, {7, "lucky"}, {1, "hi"}});

    map<int, string> m2 = { {4, "freedom"}, {5, "amazing"} };
    m1.insert(m2.begin(), m2.end());

    m1[1] = "hi";
    cout << endl << "===== start =====" << endl;

    cout << m1[1] << endl;

    for(pair<int, string> pa : m1) {
        cout << "key : "  << pa.first << ", value : " << pa.second <<endl;
    }
    cout << endl << "===== end =====" << endl;
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}
