#ifndef __Line_H
#define __Line_H

/* Line.hpp */
class Line{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine() const; /* 打印Line对象的信息 */
private:
    class LineImpl; /* 类的前向声明 */
    LineImpl * _pimpl;
};

#endif
