/*************************************************************************
    > File Name: 02_vector_int_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 11时11分19秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建存放“存放int数据的vector”的vector，尝试进行遍历，并体会vector对象和元素的存储位置
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;


void test01() {
    vector<int> v_num1{1, 2, 3};
    /* for( int num : v_num1 ) { */
    /*     cout << num << endl; */
    /* } */

    vector<vector<int>> v_vnum1{v_num1, v_num1};
    /* for( vector<int> v_num : v_vnum1 )  { */
    /*     for ( int num : v_num ) { */
    /*         cout << num << endl; */
    /*     } */
    /* } */

    
    
    vector<vector<int>> v_vnum2{{1,2}, {2,3}, {3,4}};
    /* 增强for循环 */
    /* for( vector<int>& v_num : v_vnum2 )  { */
    /*     for ( int& num : v_num ) { */
    /*         cout << num << endl; */
    /*     } */
    /* } */

    /* 普通遍历 */
    /* for ( int i = 0; i < v_vnum2.size(); ++i ) { */
    /*     for ( int j = 0; j < v_vnum2[i].size(); ++j ) { */
    /*         cout << v_vnum2[i][j] << endl; */
    /*     } */
    /* } */

    /* 迭代器遍历 */
    vector<vector<int>>::iterator it = v_vnum2.begin();
    while( it < v_vnum2.end() ) {
        vector<int>::iterator itt = it->begin();
        while( itt < it->end() ) {
            cout << *itt << endl;
            itt++;
        }
        it++;
    }

    /* vector<vector<int>> v_vnum4(3); */
    /* cout << v_vnum2.size() << endl; */
    /* cout << v_vnum2.capacity() << endl; */
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
