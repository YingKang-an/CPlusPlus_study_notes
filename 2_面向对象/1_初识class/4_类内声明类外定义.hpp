#ifndef DECLARATION_INSIDE_THE_CLASS_DEFINE_OUTSIDE_THE_CLASS_H
#define DECLARATION_INSIDE_THE_CLASS_DEFINE_OUTSIDE_THE_CLASS_H

class Test //放头文件就行
{
private:
    int a = 23;
public:
    void Print(); //类内声明
    void Fun(int c = 7, int d = 3); // 默认参数 在声明指定
};

#endif
// ^   结束 如果判断