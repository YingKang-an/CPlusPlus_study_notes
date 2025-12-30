#include <iostream>
using namespace std;

/** 输入输出运算符重载 重要，代替 Print**/
class Arr
{
private:
    int a[5]; //固定 5 个元素，不写过于复杂的
    /****************************************************************
    * friend 友缘关键字
    * 友缘即朋友，此函数即可使用类内私有成员
    ****************************************************************/
    friend ostream& operator<<(ostream& os, const Arr& tp);
    friend istream& operator>>(istream& in, Arr& tp);
public:
    Arr(int arr[])
    {
        for (int i = 0; i < 5; i++)
            a[i] = arr[i];
    }
    void Print() //重载了<< 就不需要这个 print 了
    {
        for (int i = 0; i < 5; i++)
            cout << a[i] << ' ';
        cout << endl;
    }
};

// void operator << (ostream& os, const Arr& tp)
// {
//     for (int i = 0; i < 5; i++)
//         os << tp.a[i] << ' ';
//     cout << endl;
// }

/********************************************************************
* 参数：类外重载，左操作数即左参数，右操作数即右参数
        ostream 是 cout 的类型，cout << 对象，左操作数是 ostream，右是对象
        istream 是 cin 的类型，cin >> 对象，左操作数是 istream，右是对象
* 返回值：返回 ostream 引用，可以实现 cout << 对 1 << 对 2 << 对 3 << endl;
        也可以是 void，但是只能 cout << 对 1; endl 都加不了
* 注意点：此函数是自定义，所以其内代码是任意的，但是不能违背常理
* 由于此函数需要操作类内的私有成员，所以将此函数声明为类的友缘函数
********************************************************************/

ostream& operator<<(ostream& os, const Arr& tp)
{
    for (int i = 0; i < 5; i++)
    os << tp.a[i] << ' ';
    return os; //返回一个 os 对象,可以连续输出
}
istream& operator>>(istream& in, Arr& tp)
{
    for (int i = 0; i < 5; i++)
    in >> tp.a[i] ;
    return in; //返回一个 is 对象,可以连续输入  
}


int main(void)
{
    int a[5] = { 1,2,3,4,5 };
    Arr aa(a); //定义对象初始化，走构造函数
    cout << aa << endl; //走输出重载，功能跟 Print 函数一样，但是更好用
    cin >> aa; //走输入重载
    cout << aa << endl;
    return 0;
}



