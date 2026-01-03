#include <iostream>
using namespace std;

// 基类的指针(引用)可以指向派生类类型的地址
// 一般来说，指针(引用)只能指向(引用)同类型的对象，继承在这里就不遵循这个

class CA
{
public:
    void fun(){ cout << "CA fun" << endl;}
    CA(){ cout << "CA" << endl;}
    ~CA(){cout <<"~CA" << endl;}
};

class CC : public CA
{
public:
    void fun1(){ cout << "CC fun1" << endl;}
    CC(){ cout << "CC" << endl;}
    ~CC(){cout <<"~CC" << endl;}
};

int main()
{
    // int* p = new double; 

    // int a;
    // double& d = a;
    
    CA* p1 = new CC;
    // CC* p2 = new CA;  不行

    CC c;
    CA& g = c;

    p1->fun();
    // p1->fun1();

    g.fun();
    // g.fun1();

    c.fun();
    c.fun1();
    
    delete p1;
    return 0;
}

