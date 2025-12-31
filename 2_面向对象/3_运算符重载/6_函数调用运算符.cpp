#include <iostream>
using namespace std;


/** 函数调用运算符() **/
class Arr
{
private:
    int a[5]; //固定 5 个元素，不写过于复杂的
    friend ostream& operator<<(ostream& os, const Arr& tp);

public:
    Arr(int arr[])
    {
        for (int i = 0; i < 5; i++)
            a[i] = arr[i];
    }

    /** 函数调用运算符重载 **/
    /************************************************
    * 内可以是输出对象成员的数据，同 << 或者 Print
    * 内可以是输出对象的成员布局，如下
    * 返回值可有可无
    *************************************************/
    void operator()( )
    {
        cout << "int a[5];" << endl;
        cout << "Arr(int arr[])" << endl;
        cout << "void operator()()" << endl;
        cout << "friend ostream& operator<<(ostream& os, const Arr& tp)" << endl;
    }

    /** 函数调用运算符重载：带参数 **/
    /************************************************
    * 参数可以是对成员重新赋值
    * 参数个数，类型随意，功能随意
    * 返回值随意,带返回值 Arr&,就可以直接 cout <<
    *************************************************/
    Arr& operator()(int aa[], double d = 12.3)  // 还带了默认参数
    {
        for (int i = 0; i < 5; i++)
            a[i] = aa[i];
        return *this;
    }
};  

ostream& operator<<(ostream& os, const Arr& tp)
{
    for (int i = 0; i < 5; i++)
        os << tp.a[i] << ' ';
    return os; //返回一个 os 对象,可以连续输出
}

int main(void)
{
    int a[5] = { 1,2,3,4,5 };
    int c[5] = { 6,7,8,9,0 };

    Arr aa(a); //定义对象初始化，走构造函数

    aa(); //函数重载运算符，对象调用

    //带参数的函数调用运算符重载，有返回值 Arr&，便可以直接输出
    cout << aa(c, 5.3) << endl;

    //如返回值为 void,则如下
    aa(c, 5.3); //单独调用

    cout << aa << endl; //再输出

    return 0;
}
