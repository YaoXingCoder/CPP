/*************************************************************************
    > File Name: 06_CharArray_bracket.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 09时01分37秒
    > Mail: JiaZiChunQiu@163.com
    > Title: []运算符重载
    > Content:
    >   1.定义CharArray类, char数组
 ************************************************************************/

#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class CharArray{
public:
    CharArray(const char* pstr)
    : _capacity(strlen(pstr) + 1)
    , _data(new char[_capacity]())
    {
        strcpy(_data, pstr);
        cout << "CharArray(const char* pstr)" << endl;
    }

    ~CharArray() {
        if (_data) {
            delete[] _data;
            _data = nullptr;
        }
    }

    /* [] 运算符重载 */
    char& operator[](size_t idx) {
        cout << "operator[] 运算符重载" << endl;
        if ( -1 < idx < _capacity - 1 ) { return _data[idx]; }
        else {
            cout << "out of range" << endl;
            static char nullchar = '\0'; /* 延长生命周期 */
            return nullchar;
        }
    } 
    
    /* 第一个const 是const的引用, 不能对返回的值进行修改
     * 第二个const 是将函数设置为const成员函数
     *  1.const对象 可以使用这个函数
     *  2.在函数体中不能修改对象的数据成员
     */
    const char& operator[](size_t idx) const{
        if ( -1 < idx < _capacity - 1 ) { return _data[idx]; }
        else {
            cout << "out of range" << endl;
            static char nullchar = '\0'; /* 延长生命周期 */
            return nullchar;
        }
        /* _data[idx] = 'H'; /1* 这里仍能修改, 只能认为的避免 *1/ */
    } 

    void print() const {
        cout << _data << endl;
    }

private:
    size_t _capacity;
    char* _data;
};

void test01() {
    /* 普通的字符数组 */
    /* char arr[] = "hello"; */
    /* cout << arr << endl; */
    /* arr[0] = 'H'; */
    /* cout << arr << endl; */

    /* 能够读取和修改 */
    CharArray ca1("hello");
    cout << ca1[0] << endl;
    ca1[0] = 'H';
    /* ca1.operator[](1) = 'E'; /1* 本质 *1/ */
    cout << ca1[0] << endl;

    /* 如果 const接收 应该限制其修改 只能读取 */
    /* const 对象只能调用 const 成员函数 */
    const CharArray ca2("word");
    /* ca2.operator[](0); /1* 本质 *1/ */
    cout << ca2[0] << endl; 
    /* ca2[0] = 'W'; /1* 只能读 不能修改 *1/ */

}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
