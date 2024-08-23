/*************************************************************************
    > File Name: 08_Data_Operator_MemAccess.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月22日 星期四 23时32分41秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 成员访问运算符重载 -> 只能在成员函数定义
    > Content:
    >   1.-> 返回 Data* 即可
    >   2.* 解引用 返回 Data
    >   3.多层
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Data {
public:
    Data(){
        cout << "Data() 无参" << endl;
    }
    ~Data(){
        cout << "~Data() 析构" << endl;
    }

    int getData() const{ return _data; }
private:
    int _data = 10;
};

class MiddleLayer {
public:
    MiddleLayer(Data * p) : _pdata(p){
        cout << "MiddleLayer(Data*) 有参" << endl;
    }

    ~MiddleLayer(){
        cout << "~MiddleLayer(Data*) 析构 start" << endl;
        if(_pdata){
            delete _pdata;
            _pdata = nullptr;
        }
        cout << "~MiddleLayer(Data*) 析构 end" << endl;
    }

    /* 以为目的访问 Data 的成员函数, 所以返回类型为 Data*
     * 又因为直接调用的是 ->运算符, 所以不需要参数 
     */
    Data* operator->() { return _pdata; } /* _pdata就是指向Data的指针 */

    /* 解引用 */
    Data& operator*() { return *_pdata; }

    /* 添加友元, 使得 ThirdLayer 能够访问私有成员 */
    friend class ThirdLayer;
private:
    Data * _pdata;
};

/* 第三层封装 */
class ThirdLayer {
public:
    ThirdLayer(MiddleLayer* pml) : _pml(pml)
    { cout << "ThirdLayer(MiddleLayer*) 有参" << endl; }

    ~ThirdLayer(){
        cout << "~ThirdLayer(MiddleLayer*) 析构 start" << endl;
        if(_pml){
            delete _pml;
            _pml = nullptr;
        }
        cout << "~ThirdLayer(MiddleLayer*) 析构 end" << endl;
    }

    /* -> 运算符重载 
     * 需要返回地址 不然会是临时变量 */
    MiddleLayer& operator->(){ return  *_pml; }

    /* * 解引用运算符重载
     * 返回值是 MiddleLayer */
    /* MiddleLayer& operator*(){ return *_pml; } */
    Data& operator*() { 
        /* return (*(*_pml)); */ 
        return (*(*_pml)._pdata); /* 这种方式需要访问 MiddleLayer 中的私有成员 */
    } /* 一步到胃 */
private:
    MiddleLayer* _pml;
};

/* =====================  测试 =================== */
void test01() {
    /* 访问成员中函数方式 原生指针使用 */
   /* Data* pd = new Data(); */
   /* cout << pd->getData() << endl; */
   /* cout << (*pd).getData() << endl; */
   /* delete pd; */

   /* 中间层 如果使得 MiddleLayer指向新的则需要上边手动删除*/
   MiddleLayer ml(new Data());
   /* MiddleLayer* pml = new MiddleLayer(new Data()); */

   /* 如果通过封装后的对象去像 Data那用使用 -> 则必须重载 ->运算符 */

   /* 共两个箭头->, 第二个编译器会自动添加上
    * 第一个箭头 ->, 与operator相连作为函数名
    * 第二个箭头 ->, 原生的箭头运算符用法 */
   cout << ml.operator->()->getData() << endl; /* 箭头本质 */
   cout << ml->getData() << endl;

   cout << (ml.operator*()).getData() << endl; /* 解引用 */
   cout << (*ml).getData() << endl;
}

void test02() {
    /* 这里是栈中的 MiddleLayer */
    /* MiddleLayer ml(new Data()); */
    /* 这时 ThirdLayer 中的指针指向的是栈中的 MiddleLayer 对象 */
    /* ThirdLayer tl(&ml); /1* ERROR *1/ */

    /* 正常  不需要手动释放, 依层次会自动调用析构 */
    MiddleLayer* pml  = new MiddleLayer(new Data());
    ThirdLayer tl(pml);
}

void test03() {
    cout << endl << "----- test03 -----" << endl;
    /* ThirdLayer* ptl = new ThirdLayer(new MiddleLayer(new Data())); */
    ThirdLayer tl(new MiddleLayer(new Data()));

    cout << endl << "----- start -----" << endl;
    /* 因为 MiddleLayer 类中已经重载了 箭头作为铺垫
     * 所以 ThirdLayer 重载获取到 MiddleLayer 类后 可以直接访问使用 ->Data类中的成员 */
    cout << tl->getData()  << endl;

    /* 第一个 operator-> 是 ThirdLayer 的成员函数
     * 第二个 operator-> 是 MiddleLayer 的成员函数
     * 最后一个为编译器加上的, 原生箭头的用法 */
    cout << ((tl.operator->()).operator->())->getData() << endl; /* 完全的本质形式 */

    /* 1. 因为 MiddleLayer 类中已经重载 *解引用 所以 */
    /* cout << (*(*tl)).getData() << endl; /1* 一步步解引用获得 *1/ */
    cout << (*tl).getData() << endl; /* 一步到胃 */
    
    cout << endl << "----- end -----" << endl;
}

int main (int argc, char* argv[]) {
    /* test01(); */
    /* test02(); */
    test03();
    return 0;
}
