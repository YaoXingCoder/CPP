/*************************************************************************
    > File Name: 04_dynamic_arr_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月17日 星期六 11时35分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: vector 容器
    > Content:
    >   1.初始化
    >   2.常规操作, 扩容规则
    >
 ************************************************************************/

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/* vector */
void test01() {
    vector<int> nums; /* 创建vector容器 */
    
    vector<int> nums2(10); /* 常见容器 并 初始化10个大小 */

    vector<int> nums3(5, 6); /* 初始化为 5 个 6 */

    vector<int> nums4{1, 2, 3, 4, 5}; /* 初始化为 指定数值 */

    vector<int> nums5(nums4.begin(), nums4.end() - 2); /* 通过迭代器初始化 */

    /* 增强for循环 */
    for( int & ele : nums5 ){
        cout << ele << " ";
    }
    cout << endl;
}

/* vector 常规操作 */
void test02() {
    vector<int> nums(1); 
    cout << "nums.size() is " << nums.size() << endl; /* 元素个数 */
    cout << "sizeof(nums) is " << sizeof(nums) << endl; /* vector 由三个指针 _start _finish _end_of_storage */
    cout << "nums.capacity() is " << nums.capacity() << endl; /* 代表容量, 最多能够存放多少元素 */
    for(int & element : nums) {
        cout << element << " ";
    }
    cout << endl;

    nums.push_back(1); /* 会进行动态的扩容, 扩容的规则是每次是上一次容量的2倍*/
    nums.push_back(1); /* 会进行动态的扩容, 扩容的规则是每次是上一次容量的2倍*/
    cout << "nums.size() is " << nums.size() << endl;
    cout << "nums.capacity() is " << nums.capacity() << endl; /* 代表容量, 最多能够存放多少元素 */

    for(int & element : nums) {
        cout << element << " ";
    }
    cout << endl;
}

int main (int argc, char* argv[]) {
    test01();
    test02();
    return 0;
}
