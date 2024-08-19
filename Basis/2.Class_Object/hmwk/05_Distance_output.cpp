/*************************************************************************
    > File Name: 05_Distance_output.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月19日 星期一 09时10分18秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <math.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Point
{
public:
    Point(int xx = 0, int yy = 0)
	{
		X = xx;
		Y = yy;
		cout << "point构造函数被调用" << endl;
	}


   	Point(Point &p);

   	int GetX()
   	{
   		return X;
   	}

   	int GetY()
   	{
   		return Y;
   	}

private:
    int X;
    int Y;
};

Point::Point(Point &p)
{
	X = p.X;
	Y = p.Y;
	cout << "X = " << X << " Y=" << Y << " Point拷贝构造函数被调用" << endl;
}

class Distance
{
public:
	Distance(Point xp1, Point xp2);
	double GetDis()
	{
		return dist;
	}
private:
	Point p1;
    Point p2;
	double dist;
};

Distance::Distance( Point xp1, Point xp2)
: p1(xp1)
, p2(xp2)
{
	cout << "Distance构造函数被调用" << endl;
	double x = double(p1.GetX() - p2.GetX());
	double y = double(p1.GetY() - p2.GetY());
	dist = sqrt(x * x + y * y);
}

void test01() {
    Point myp1(1,1), myp2(4,5);
	Distance myd(myp1, myp2);
	cout << "The distance is:" ;
	cout << myd.GetDis() << endl;
}


int main (int argc, char* argv[]) {
    test01();
    return 0;
}
