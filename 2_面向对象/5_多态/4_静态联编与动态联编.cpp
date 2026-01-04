#include <iostream>
using namespace std;

/**************************************
动态联编，静态联编
动态联编：程序在运行时确定调用执行的目标
静态联编：程序在编译时确定调用执行的目标
****************************************/

class CA
{
public:
    // 给成员函数加 virtual 关键字：开启动态绑定（运行时决定调用哪个函数）
    virtual void fun() { cout << "CA::funa()" << endl; }
    void fun1() { cout << "CA::fun1()" << endl; }
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
    CA* pa = nullptr; // 如果不在此处声明，pa只在switch作用域中

    int a = 1;
    cin >> a;
    switch(a) // 两个case分支里的CA* pa处于同一作用域（switch内部）
    {
    case 0:
        pa = new CC;
        break;
    case 1:
        pa = new CD;
        break;
    }

    pa->fun(); //动态联编，运行时确定执行代码
    pa->fun1(); //静态联编，编译时确定执行代码

    delete pa;
    return 0;
}
