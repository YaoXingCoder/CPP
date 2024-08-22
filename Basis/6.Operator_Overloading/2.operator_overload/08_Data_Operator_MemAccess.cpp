/*************************************************************************
    > File Name: 08_Data_Operator_MemAccess.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 23时32分41秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 成员访问运算符重载 -> 只能在成员函数定义
    > Content:
    >   1.-> 返回 Data* 即可
    >   2.* 解引用 返回 Data
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Data {
public:
    Data(){}
    ~Data(){}

    int getData() const{ return _data; }
private:
    int _data = 10;
};

class MiddleLayer {
public:
    MiddleLayer(Data * p) : _pdata(p){}

    ~MiddleLayer(){
        if(_pdata){
            delete _pdata;
            _pdata = nullptr;
        }
    }

    /* 以为目的访问 Data 的成员函数, 所以返回类型为 Data*
     * 又因为直接调用的是 ->运算符, 所以不需要参数 
     */
    Data* operator->() {
        return _pdata; /* _pdata就是指向Data的指针 */
    }

    /* 解引用 */
    Data& operator*() {
        return *_pdata;
    }
private:
    Data * _pdata;
};

/* =====================  测试 =================== */

void test01() {
    /* 访问成员中函数方式 原生指针使用 */
   Data* pd = new Data();
   cout << pd->getData() << endl;
   cout << (*pd).getData() << endl;
   /* delete pd; */

   /* 中间层 */
   MiddleLayer ml(pd); /* 因为成员指针指向pd, 所有程序结束后调用析构函数, 释放了指针指向的空间 */
}

void test02() {
    /* 访问成员中函数方式 原生指针使用 */
   /* Data* pd = new Data(); */
   /* cout << pd->getData() << endl; */
   /* cout << (*pd).getData() << endl; */
   /* delete pd; */

   /* 中间层 如果使得 MiddleLayer指向新的则需要上边手动删除*/
   MiddleLayer ml(new Data());
   /* 如果通过封装后的对象去像 Data那用使用 -> 则必须重载 ->运算符 */

   /* 共两个箭头->, 第二个编译器会自动添加上
    * 第一个箭头 ->, 与operator相连作为函数名
    * 第二个箭头 ->, 原生的箭头运算符用法
    */
   cout << ml.operator->()->getData() << endl; /* 箭头本质 */
   cout << ml->getData() << endl;

   cout << (ml.operator*()).getData() << endl; /* 解引用 */
   cout << (*ml).getData() << endl;

}

int main (int argc, char* argv[]) {
    /* test01(); */
    test02();
    return 0;
}
