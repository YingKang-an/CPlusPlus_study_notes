#include <iostream>
using namespace std;

class Car
{
private:
    int a = 1;
protected:
    int b = 2;
public:
    int c = 3;
};

class KaCar : public Car   // 公有继承Car
{
public:
    void Print()
    {
        //报错，基类 peivate 只能在[基类]直接使用
        // cout << a << endl;

        //成功，基类 protected 可以在[基类/派生类]直接使用
        cout << b << endl;

        //成功，基类 public 可以在[基类/派生类/类外]直接使用
        cout << c << endl;
    }
};

int main(void)
{
    KaCar kc;

    //报错，基类 peivate 只能在[基类]直接使用
    //cout << kc.a << endl;

    //报错，基类 protected 可以在[基类/派生类]直接使用
    //cout << kc.b << endl;

    //成功，基类 public 可以在[基类/派生类/类外]直接使用
    cout << kc.c << endl;
    
    return 0;
}
