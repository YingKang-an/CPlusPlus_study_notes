#include <iostream>
using namespace std;

/*************************************************
 * 构造函数重载
 * 
 * 构造函数可以存在多个，创建对象时，只调用其中之一
 * 多个构造函数之间是重载关系，即参数列表不一样
 * 对象定义时，根据所传参数调用相应的构造函数
 * 
 *******************************************************/

class Test
{
private:
    int   a = 0;
    float f = 0.0f;
public:
    Test(int aa, float ff){a = aa, f = ff;}
    Test(float ff, int aa){a = aa, f = ff;}
    Test( )               { }
    Test(int aa)          {a = aa;}
    Test(float ff)        {f = ff;}
    
    void Print()          {cout << a << ' ' << f << endl;}
};

int main()
{
    Test t1;  // 无参数就不写小括号
    t1.Print();                    // 0  0.0
    Test t2(2.5f, 2);
    t2.Print();                    // 2  2.5
    Test t3(3, 4.5f);
    t3.Print();                    // 3  4.5
    Test t4(2);                   
    t4.Print();                    // 2  0.0
    Test t5(5.6f);
    t5.Print();                    // 0  6.5

    return 0;
}