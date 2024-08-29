/*************************************************************************
    > File Name: 07_class_template.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月29日 星期四 23时03分04秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 类模板
    > Content:
    >   1.使栈更通用
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <class T = int, int kCapacity = 10>
class Stack {
public:
    Stack() : _top(-1) , _data(new T[kCapacity]()) {
        cout << "Stack()" << endl;
    }
    ~Stack() {
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
        cout << "~Stack()" << endl;
    }
    bool empty() const {
        return _top == -1;
    }
    bool full() const {
        return _top == kCapacity - 1;
    }
    void push(const T &t) {
        if ( !full() ) {
            _data[++_top] = t;
        }else {
            cout << "full" << endl;
        }
    }
    void pop() {
        if ( !empty() ) {
            cout << _data[_top--] << endl;
        } else {
            cout << "empty" << endl;
        }
    }
    T top() {
        if( !empty() ) {
            return _data[_top];
        } else {
            throw "stack is empty";
        }
    }
private:
    int _top;
    T * _data;
};

/* =============== test =============== */
void test0() {
    Stack<string, 20>ss;
    Stack<int> st;
    Stack<> st2;
}

/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
