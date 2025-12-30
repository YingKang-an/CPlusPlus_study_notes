#include<iostream>
using namespace std;
/***************************************************
拷贝函数的功能
逐个复制非静态成员，复制的是成员的值，直接赋值
***************************************************/
class Test
{
private:
    int a;
    double d;
    char str[10] = {0};
public:
    Test(int a = 1, double d = 3.0, const char str[] = "qwerty")
    {
        this->a = a;
        this->d = d;
        for (int i = 0; str[i] != 0; i++)
        this->str[i] = str[i];
    }
    // 实际上默认有拷贝构造
    // Test(const Test& t) //参数为当前类的常量引用类型
    // {
    //     this->a = t.a; //不加 this 就行，我只是加上，帮助大家加深一项
    //     this->d = t.d;
    //     for (int i = 0; t.str[i] != 0; i++)
    //     str[i] = t.str[i]; //数组一定要用循环或者库函数
    //     //*this = t; //用这个代替前边的就行
    // }
    void Print()
    {
        cout << a << ' ' << d << ' ' << str << endl;
    }
};

int main(void)
{
    Test t1(34);
    Test t2(t1);
    t2.Print();
    return 0;
}
