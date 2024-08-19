/*************************************************************************
    > File Name: 07_B_Output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 10时47分36秒
    > Mail: JiaZiChunQiu@163.com
    > Title: class B output
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class B {
public:
	B() {
        cout << "B()" << endl;
    }

    ~B() {
    	cout << "~B()" << endl;
    }

    B(const B &rhs) {
        cout << "B(const B&)" << endl;
    }

    B &operator=(const B &rhs) {
    	cout << "B &operator=(const B &s)" << endl;
        return  *this;
    }
};

B func(const B &rhs) {
    cout << "B func(const B &)" << endl;
    return rhs;
}

/* 测试 */
void test01(){
	B b1,b2;
    b2=func(b1); //10#    
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
