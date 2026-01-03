#include <iostream>
using namespace std;


// 单继承中，基类构造有参数，通过初始化列表传递
class CA
{
public:
    CA(int a) { cout << "CA" << a << endl; }
    ~CA( )    { cout << "~CA" << endl;}
};

class CC : public CA
{
public:
    // CC():CA(12) { cout << "CC" << endl;}
    CC(int a):CA(a) { cout << "CC" << a << endl;}
    ~CC()           {cout << "~CC" << endl;}
};

int main()
{
    CC c(12);
}


/*

// 多继承中，多个基类构造有参数，通过初始化列表传递
class CA
{
public:
    CA(int a) { cout << "CA" << endl; }
    ~CA() { cout << "~CA" << endl; }
};

class CC
{
public:
    CC(int a) { cout << "CC" << endl; }
    ~CC() { cout << "~CC" << endl; }
};

class CD : public CC, CA //多继承，顺序影响基类构造析构的顺序
{
public:
    CD(int a) : CA(a), CC(a) { cout << "CD" << endl; }
    ~CD() { cout << "~CD" << endl; }
};

// 多个基类的构造顺序与析构顺序，由继承的顺序决定
// 即先调用 CC 的构造与析构，后调用 CA 的

*/