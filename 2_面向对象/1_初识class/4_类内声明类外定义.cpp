#include <iostream>
#include"4_类内声明类外定义.hpp"

using namespace std;

void print();

int main(void)
{
    Test t;

    t.Print();
    t.Fun();
    t.Fun(1, 2);

    print();         //   ()是调用运算符

    return 0;
}

void Test::Print() //类外定义 Test:: 类名作用域
{
    cout << a << endl;  // a 是类里面的，可以直接用
}
void Test::Fun(int y, int d) //类外定义
{
    cout << y << ' ' << d << endl;
}
void print()
{
    cout << "调用print!这不是Test::print,这是print!!" << endl;
}

