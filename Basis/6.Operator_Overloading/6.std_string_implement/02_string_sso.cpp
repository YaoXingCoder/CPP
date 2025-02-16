/*************************************************************************
    > File Name: 02_string_sso.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月23日 星期五 17时48分57秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 短字符优化
    > Content:
 ************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

class string {
public:
private:
	union Buffer{
		char * _pointer;
		char _local[16];
	};

	size_t _size;
	size_t _capacity;
    Buffer _buffer;
};

void test0() {

}

int main (int argc, char* argv[]) {

    return 0;
}
