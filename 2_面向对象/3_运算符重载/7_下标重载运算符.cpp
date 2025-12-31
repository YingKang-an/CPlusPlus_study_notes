#include <iostream>
#include <assert.h>
using namespace std;

/** 下标运算符重载[]：只能类内 **/
/************************************************
* 下标运算符一般用于数组式连续空间的访问
*************************************************/
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

    /********************************************************
    * 使用形式：对象[下标]
    * 所以有一个整数参数
    * 返回值为 int&，数组时，a[n]是可读可写，可取地址的
    **********************************************************/
    int& operator[](int n)  // 返回值为& 可读可写
    {         //        ^~~~~~之后学n越界处理，抛出一个异常
        assert(n < 5);  // 中断
        
        return a[n];
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
    Arr aa(a); //定义对象初始化，走构造函数
    cout << aa[1] << endl; //输出
    aa[2] = 34; //重新赋值
    cout << aa << endl;
    cin >> aa[3]; //指定元素输入
    cout << aa << endl;

    return 0;
}
