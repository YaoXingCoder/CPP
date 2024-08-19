/*************************************************************************
    > File Name: 03_Sample_output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月17日 星期六 17时48分17秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Sample {
public:
      Sample();
      void Display();
private:
      int i;
      static int k;
};

Sample::Sample() {
	i=0;
	k++;
}
void Sample::Display() {
   cout << "i=" << i << ",k=" << k << endl;
}

int Sample::k=0;

void test01() {
    Sample a, b;
    a.Display();
    b.Display();
}

int main (int argc, char* argv[]) {
    test01();
    return 0;
}
