#include <iostream>
using namespace std;

/** 重 载 赋值函数(= )：只能类内，类外直接报错 **/
/*******************************************************************
* 对象 = 数组
* 对象 = 对象：有默认的赋值函数，单纯的所有成员对应直接赋值
  同拷贝构造相似，涉及申请空间的指针成员时，会导致被赋值的对象内存丢失
  两个对象的指针指向同一块空间，析构释放时导致异常中断
  所以存在深赋值的操作，如果这个情况，则不需要重载对象 = 对象
********************************************************************/

class Arr
{
private:
    int a[5];  //固定 5 个元素，不写过于复杂的
    int* p;    //指针成员，构造函数 new 空间，析构 delete 空间

    friend ostream& operator << (ostream& os, const Arr& pt);

public:
    Arr(int arr[])
    {
        for (int i = 0; i < 5; i++)
            this->a[i] = arr[i];
        p = new int[10];
    }
    ~Arr()
    {
        delete[] p;
    }
    Arr& operator = (int arr[])
    {
        for (int i = 0; i < 5; i++)
            this->a[i] = arr[i];
        return *this;
    }

    //对象=对象，浅赋值，默认存在函数
    /*
    Arr& operator=(const Arr& tp) 
    {
        for (int i = 0; i < 5; i++)
            a[i] = tp.a[i];  //  使a[5]赋值
        p = tp.p;            //  使得两个 p 指向同一块空间
        return *this;
    }
    */                       //深浅不能同时存在   不然参数都一样

    //默认左操作数是对象：对象 = 数组
    //返回值可以实现连续赋值
    Arr& operator = (const Arr& tp)
    {
        for (int i = 0; i < 5; i++)
            this->a[i] = tp.a[i];
        for (int i = 0; i < 5; i++)
            p[i] = tp.p[i];
        return *this;
    }
};

ostream& operator << (ostream& os, const Arr& pt)
{
    for (int i = 0; i < 5; i++)
        os << pt.a[i] << " ";
    return os;
}

int main()
{
    int a[5] = {1,2,3,4,5};
    int c[5] = {2,4,6,8,0};
    Arr AA(a); Arr CC(c);
    AA = CC;
    cout << AA << endl;

    return 0;
}