#include <iostream>

/************************************
 构造函数
 对象创建时自动调用的一个函数，用来对对象成员进行赋值等操作
***************************************************/

// 形式：

class Test
{
private:
    int a = 23;
public:
    Test(); //构造函数，无返回值，名字是类名
    // void Print()
    // {
    //     std::cout << "构造函数" << std::endl;
    // }
};

int main(void)
{

    Test t; // 自动调用构造函数Test t;
    // t.Print();

    Test* p;   // 这里不调用，还没有对象构造函数
    p = new Test;  //这里调用构造函数

    return 0;
}

//类内声明，类外定义
Test::Test()
{
    std::cout << "构造函数" << std::endl;
}