#include <iostream>
using namespace std;

/***********************************
多态状态下：构造函数调用顺序：先基类，后派生类
析构函数调用顺序：只调用基类的
解决办法：将基类的析构函数声明成虚函数
注意：构造函数不能是虚函数
*************************************/

class CA
{
public:
    CA() { cout << "CA" << endl; }
    virtual ~CA() { cout << "~CA" << endl; }
};

class CC : public CA
{
public:
    CC() { cout << "CC" << endl; }
    ~CC() { cout << "~CC" << endl; }
};

int main(void)
{
    CA* pa = new CC;
    delete pa;
    return 0;
}

/*
虚析构就像给析构函数装了“动态导航”：delete 时会根据对象实际类型找对应析构函数；
非虚析构则是“固定导航”：只认指针的类型，不管实际指向的对象是什么
*/