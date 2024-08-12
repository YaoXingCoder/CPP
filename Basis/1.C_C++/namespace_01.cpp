/*************************************************************************
    > File Name: namespace_01.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月12日 星期一 10时08分10秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 命名空间学习
    > Content:
 ************************************************************************/

#include <iostream>
/* using namespace std; */
using std::cout;
using std::endl;

namespace cpp {
    int number = 100;
}

namespace wd {
    int number = 10;
    void display () {
        cout << "wd:: display ()" << endl;
    }
}

using namespace wd;
void test0 () {
    cout << number << endl;
}
/* 改为写入局部位置 */
/* void test0 () { */
/*     using namespace wd; */
/*     cout << number << endl; */
/* } */

/* using namespace cpp; */
/* void test1() { */
/*     cout << cpp::number << endl; */
/* } */

void test1() {
    using cpp::number;
    cout << number << endl;
}


/* ============================================================== */

// namespace wd {
// 	int num = 100;
// 	void func () {
// 	    cout << "func" << endl;
// 	}
// 
// 	namespace cpp {
// 		int num = 200;
// 		void func (){
// 		    cout << "cpp:: func" << endl;
// 		}
// 	} // end of namespace cpp
// } // end of namespace wd
// 
// // 方式一，使用作用域限定精确访问实体
// void test0 () {
//     cout << wd::cpp:: num << endl;
//     wd::cpp:: func ();
// }
// 
// //方式二，using 编译指令一次性引入 cpp 的实体
// void test1 (){
//     using namespace wd:: cpp;
//     cout << num << endl;
//     func ();
// }
// 
// //方式三，using 声明语句
// void test2 (){
//     using wd::num;
//     /* using wd::cpp::num; */
//     using wd::cpp:: func;
//     cout << num << endl;
//     func ();
// }

/* ======================================================================= */

// int val = 100;
// void func (){
//     cout << "g_func ()" << endl;
// }
// 
// namespace {
// 	int val = 10;
// 	void func (){
// 	    cout << "func ()" << endl;
// 	}
// } // end of anonymous namespace
// 
// void test0 (){
//     /* cout << val << endl; //冲突 */
//     cout << ::val << endl; //全局的 val
//     /* func (); //冲突 */
//     ::func (); //全局的 func
// }


/* ==================================命名空间跨模块调用===================================== */

/* namespace wd { */
/*     extern int val; */
/*     extern void display(); */
/* } */



/* 命名空间的作用域冲突 */
int main (int argc, char* argv[]) {
    
    /* test0(); */
    /* test1(); */

    /* test0(); */
    /* test1(); */

    /* cout << wd::val << endl; */
    /* wd::display; */

    cout << "hello,world" << endl; /* "" + 1 的结果是指向字符串第二个字符的指针（在这个例子中是字符串的空终止符 \0） */
    return 0;
}
