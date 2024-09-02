/*************************************************************************
  > File Name: 05_deleter.cpp
  > Author: JiaZiChunQiu
  > Created Time: 2024年08月31日 星期六 10时26分51秒
  > Mail: JiaZiChunQiu@163.com
  > Title: 删除器
  > Content:
 ************************************************************************/

#include <iostream>
#include <memory>

template<typename T>
struct FILEclose {
    FILEclose() { std::cout << "FILEclose" << std::endl; }
    void operator()(T * fp) {
        if ( fp ) {
            fclose(fp);
            std::cout << "fclose" << std::endl;
        }
    }
    ~FILEclose() { std::cout << "~FILEclose()" << std::endl; }
};
/* =============== test0 =============== */
void test0() {
    std::string msg = "hello,world\n";
    FILE * fp = std::fopen("res1.txt","a+");
    std::fwrite(msg.c_str(),1,msg.size(),fp);
    /* std::fclose(fp); */
}

/* =============== test1 =============== */
void test1() {
    std::string msg = "hello,world\n";
    std::unique_ptr<FILE, FILEclose<FILE>> up(std::fopen("res2.txt","a+"));
    std::fwrite(msg.c_str(),1,msg.size(),up.get());
    std::cout << up.get() << std::endl;
    /* delete up.get(); */
    /* std::fclose(up.get()); */
    /* delete up.get(); */
    /* std::cout << up.get() << std::endl; */
}


/* =============== test2 =============== */
void test2() {
    std::string msg = "hello,word\n";
    FILEclose<FILE> fc;
    /* std::unique_ptr<std::FILE, FILEclose<FILE>&> up(std::fopen("res3.txt", "a+"), fc); */
    std::shared_ptr<FILE> sp(fopen("res3.txt", "a+"), fc);
    std::cout << sp.get() << std::endl;
    std::fwrite(msg.c_str(), sizeof(char), msg.size(), sp.get());
}


/* =============== main =============== */
int main (int argc, char* argv[]) {
    /* test0(); */
    /* test1(); */
    test2();
    return 0;
}
