// 1.函数指针
#include <iostream>
// 使用std命名空间，避免每次写std::cout
using namespace std;

// 定义加法函数：接收两个int参数，返回它们的和
int add(int a, int b){ return a + b; }
// 定义减法函数：接收两个int参数，返回它们的差
int sub(int a, int b){ return a - b; }

// 全局函数指针变量定义
// 类型：指向“接收两个int参数、返回int的函数”的指针
// 初始化：指向add函数的入口地址
int(*pfunc)(int ,int) = add;

// 使用typedef给函数指针类型起别名
// 别名op代表“int(*)(int, int)”这种函数指针类型
// 【关键知识点】：op是类型别名，不是变量，不能直接赋值或调用
typedef int(*op)(int, int);

// 主函数，程序入口
int main()
{
    // 用op类型别名定义局部函数指针变量pf
    // 赋值：让pf指向sub函数的入口地址
    op pf = sub;
    
    // 调用pf指向的sub函数，计算3-4，输出结果-1
    cout << pf(3, 4) << endl;
    // 调用全局变量pfunc指向的add函数，计算4+2，输出结果6
    cout << pfunc(4, 2) << endl;
    
    return 0;
}


// 2.回调函数的形式
typedef int(*op_callback)(int, int); // 函数指针别名

// 被当作参数传给另一个函数的函数是回调函数
int add(int a, int b){ return a + b; } // 回调函数
int sub(int a, int b){ return a - b; } // 回调函数

// 参数中包括函数指针的函数是回调接收函数
int calc(op_callback callback, int x, int y)
{
    return callback(x, y);
}

int main ()
{
    int a = 3, b = 4;
    cout << calc(add, a, b) << endl;
    cout << calc(sub, a, b) << endl;

    return 0;
}
