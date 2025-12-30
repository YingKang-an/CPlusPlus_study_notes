#include <iostream>
using namespace std;
/****************************************************
默认构造函数
当我们不写构造函数时，系统会默认有一个构造函数，叫默认构造函数

其为：
Test() //无参数，无代码，手写构造函数后，就没有默认构造了
{
}
****************************************************/


// 有参数的构造函数

class Test
{
private:
    int a = 23;
public:
    Test(int aa) //无返回值，名字是类名
    {
        a = aa; //用参数对其赋值
        cout << "构造函数" << endl;
    }
    void Print() { cout << a << endl; }
};

int main(void)
{

    Test t(12); //构造有参数，必须得传参数，不然报错
    t.Print();  //输出 12

    Test* p;    // 指针对象传递参数
    p = new Test(34);
    p->Print();

    return 0;
}