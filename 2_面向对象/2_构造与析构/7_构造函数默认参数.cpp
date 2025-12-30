#include <iostream>
using namespace std;

/*******************************************************
 * 
 * 默认参数的构造函数 
 * 
 *******************************************************/

class Test
{
private:
    int   a = 0;
    float f = 0.0f;
public:
    Test(int aa = 0, double ff = 0.0f)
    {
        a = aa;
        f = ff;
    }
    
    void Print()          {cout << a << ' ' << f << endl;}
};

 /*******************************************************
 
- 此时，不可以写 Test(){ }  否则调用 Test t1; 时 产生二义性。
- 原因：编译器无法区分是调用无参构造 Test() 
       还是使用默认参数的 Test(0, 0.0f)。

- 不可以写 Test(int aa){ }  否则调用 Test t5(5.6f); 时 产生二义性。
- 原因：float 可以隐式转换为 int，编译器无法区分是调用 Test(int) 还是 
       Test(int, double)（第二个参数用默认值）

*******************************************************/
int main()
{
    Test t1;  // 无参数就不写小括号
    t1.Print();                    // 0  0.0
    Test t2(1);
    t2.Print();                    // 1  0.0
    Test t3(2, 3.4f);
    t3.Print();                    // 2  3.4
    
    return 0;
}