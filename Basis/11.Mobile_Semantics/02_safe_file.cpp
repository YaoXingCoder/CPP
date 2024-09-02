/*************************************************************************
    > File Name: 02_safe_file.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月30日 星期五 22时40分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class SafeFile {
public:
    // 构造函数中接管资源
    SafeFile(FILE * fp) : _fp(fp) {
        cout << "SafeFile(FILE*)" << endl;
    }

    //析构函数中释放资源
    ~SafeFile(){
        cout << "~SafeFile()" << endl;
        if(_fp){
            fclose(_fp);
            _fp = nullptr;
            cout << "fclose(_fp)" << endl;
        }
    }

    // 进行写操作
    void write(const string & msg){
        fwrite(msg.c_str(), sizeof(char), msg.size(), _fp);
    }

private:
    FILE * _fp;
};


void test0(){
    string msg("hello,world");
    FILE * fp = fopen("wd.txt","a+");
    SafeFile sf(fp);
    sf.write(msg);
    /* fclose(fp); */
}

void test1(){
    //推荐的写法
    string msg("hello,world");
    SafeFile sf(fopen("wd.txt","a+"));
    sf.write(msg);
}

int main(void){
    /* test0(); */
    test1();
    return 0;
}

