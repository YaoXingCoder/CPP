/*************************************************************************
    > File Name: 01_A_B_friend_output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月21日 星期三 22时29分38秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class B {
    int y;
public:
    friend class A;
};

class A { 
    int x;
public:  
    A(int a, B& r, int b)   {
	    x = a; 
	    r.y = b;
    } 
     
    void Display( B & ); 
};

void A::Display(B &r) {
    cout<<x<<" "<<r.y<<endl;
}

int main( ) {
    B Obj2;
    
    A Obj1(33, Obj2, 88);
    
    Obj1.Display(Obj2);

    return 0;
}

