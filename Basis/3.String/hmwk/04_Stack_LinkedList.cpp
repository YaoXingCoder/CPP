/*************************************************************************
    > File Name: 04_Stack_LinkedList.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月20日 星期二 20时36分27秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 栈 链表实现
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

struct LNode {
public:
    LNode(int val)
    : _val(val)
    , _next(nullptr)
    {
        cout << "LNode 结构体初始化" << endl;
    }

    int _val;
    LNode* _next;
};

class Stack{
public:
    Stack(int capa)
    : _head(nullptr)
    , _tail(nullptr)
    , _size(0)
    , _capacity(capa)
    {
        cout << "Stack() 构造" << endl;
    }

    ~Stack() {
        while( _head != nullptr ) {
            LNode* temp = _head;
            _head = temp->_next;
            delete temp;
        }
        _tail = nullptr;
        cout << "~Stack() 析构" << endl;
    }

    bool empty() const {
        return _size == 0;
    }
    bool full() const{
        return _size == _capacity;
    }

    /* 头插法 */
    void push(const int & value) {
        if ( full() ) { 
            cout << "The Stack is full." << endl; 
            return; 
        }
        LNode* temp = new LNode(value);
        if ( empty() ) {
            _head =  _tail = temp;
        } else {
            temp->_next = _head;
            _head = temp;
        }
        _size++;
    }

    void pop() {
        if ( empty() ) {
            cout << "The Stack is empty." << endl;
            return;
        }
        LNode* temp = _head;
        if( --_size == 0 ) {
            delete temp;
            _head = _tail = nullptr;
        } else {
            _head = temp->_next;
            delete temp;
        }
    }
    int top() {
        if ( empty() ) { 
            cout << "The Stack is empty." << endl;
            throw "Stack is empty.";
        } else {
            return _head->_val;
        }
    }
private:
    LNode* _head;
    LNode* _tail;
    int _size;
    int _capacity;
};

void test01() {
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
    cout << "栈是不是空的？" << st.empty() << endl;
}


int main (int argc, char* argv[]) {
    test01();
    return 0;
}
