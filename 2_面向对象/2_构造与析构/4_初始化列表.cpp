#include <iostream>
using namespace std;

/*****************************************************
 * 初始化列表
 * 引用成员，const成员必须使用初始化
******************************************************/

class Test
{
private:
    int a = 23;
    float f;
public:
    Test(int aa, float ff) : a(aa), f(ff)
    //冒号，多个用逗号隔开，aa 给 a 初始化,ff 给 f 初始化 不是赋值！
    {
    }
    void Print() { cout << a << ' ' << f << endl; }
};

int main(void)
{
    Test t(12, 2.3f); //构造有参数，必须得传参数，不然报错
    t.Print(); //输出 12，2.3
    return 0;
}


/*


类外定义位置：

class Test
{
private:
    int a = 23;
    float f;
public:
    Test(int aa, float ff); //声明不放初始化列表
    void Print() { cout << a << ' ' << f << endl; }
};


Test::Test(int aa, float ff) : a(aa), f(ff) //放定义处
{
}


*/