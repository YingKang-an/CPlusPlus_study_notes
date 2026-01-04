#include <iostream>
using namespace std;

/***********************************************
虚函数与多态
多态：一种写法，多种执行状态。函数重载，默认参数，运算符重载
------------------------------------------------
虚函数的多态：
***********************************************/
class CA
{
public:
    virtual void fun() { cout << "CA::funa()" << endl; }
};

class CC : public CA
{
public:
    void fun() { cout << "CC::func()" << endl; }
};

class CD : public CA
{
public:
    void fun() { cout << "CD::func()" << endl; }
};

int main(void)
{
    CA* pa = new CC; //基类指针指向子类空间
    //CA* pa = new CD;
    pa->fun();
    //new CC 执行结果是 CC 的 fun
    //new CD 执行结果是 CD 的 fun
    //一种调用，多种执行状态

    delete pa;
    
    return 0;
}
