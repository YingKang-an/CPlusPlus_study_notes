#include<iostream>
using namespace std;

/******************************************
 * this 指针
 * 装着当前对象的地址
 * 即每个对象都有自己的地址，我们可以通过 &t1 &t2 ... 获取到各个对象的地
 * 址，C++在类内直接提供了地址，我们就不需要在类外获取了
 *******************************************/

class Test
{
private:
    int a;
    Test* p = this;  // 类内可以直接使用，这里没有什么意义
    //const Test* this        相当于类内有这个，C++自动实现了对其初始化
public:
    Test(/* Test* this,*/ int a)
    {
        //书上说 this 作为函数的隐藏参数，传递给函数，每个成员都有，当然
        //他的实现方法我们不用研究，知道每个成员函数都可以使用即可

        this->a = a; //用处 1：用来区分类成员与局部变量
        // (*this).a = a;
    }

    void Print()
    {
    cout << a << ' ' << this << endl; //用处 2：需要的使用直接用
    }

    Test* GetAddr()
    {
        return this; //用处 3：返回当前对象的地址，外部使用
    }

    Test& GetObject()
    {
        return *this; //用处 4：this 是对象的地址，*this 是对象本身
    }
};


int main(void)
{
    Test t1(56);
    t1.Print();
    cout << &t1 << ' ' << t1.GetAddr() << endl;
    t1.GetObject().Print();

    return 0;
}