/*************************************************************************
    > File Name: 04_Stack_Array.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 19时39分26秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 栈的实现
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define DEFAULT_CAPACITY 8

class Stack{
public:
    /* 构造初始化 */
    Stack(int size = DEFAULT_CAPACITY) 
    : _size(0)
    , _capacity(size)
    , _top(-1)
    , _data(new int[_capacity]())
    {
        cout << "Stack() 构造" << endl; 
    }

    /* 析构 */
    ~Stack() {
        if ( _data != nullptr ) {
            delete[] _data;
            _data = nullptr;
        }
        cout << "~Stack() 析构 " << endl;
    }

    /* 判空 */
    bool empty(){ return _size == 0; }

    /* 判满 */
    bool full() { return _size == _capacity; }

    /* 放入 */
    void push(const int & value) {
        if ( full() ) { 
            cout << "the stack is full." << endl;
            return; 
        }
        _data[_size++] = value;
        _top++;
    }
    void pop() {
        if ( empty() ) {
            cout << "the stack is empty" << endl;
            return ;
        }
        _top--;
        _size--;
    }
    int top() {
        if ( empty() ) { 
            cout << "the stack is empty." << endl;
            throw "stack is empty.";
        }else {
            return _data[_top];
        }

    }
private:
    int _capacity; /* 容量大小 */
    int _size; /* 已有元素 */
    int _top; /* 栈顶指针 */
    int* _data; /* 数组指针 */
};

void test0() {
    Stack st(12);
    cout << "栈是不是空的？" << st.empty() << endl;
    st.push(1);
    cout << "栈是不是满的？" << st.full() << endl;


    for(int idx = 2; idx != 15; ++idx) {
        st.push(idx);
    }

    while(!st.empty()) {
        cout << st.top() << endl;
        st.pop();
    }
    /* st.top(); */
    cout << "栈是不是空的？" << st.empty() << endl;
}

int main (int argc, char* argv[]) {
    test0();
    return 0;
}
