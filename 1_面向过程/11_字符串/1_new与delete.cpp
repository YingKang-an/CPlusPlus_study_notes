/*********************************************
 * new 与 delete
----------------------------------------------
 * new 申请单个变量空间         delete 释放单个变量空间
 * new[] 申请数组空间          delete  释放数组空间
 * 
 * 本身是运算符
 * 
 * new 返回申请空间首地址
 * delete 释放操作数也是首地址
 * 
 * 也就是 无名空间 | 学名 堆空间 自由空间
***********************************************/

#include <iostream>

int main (void)
{
    //基本数据类型 int long double char
    // int a1;
    // int* p1 = &a1
    int* p2 = new int;      // 自由空间
    *p2 = 12;
    std::cout << *p2 << std::endl;
    delete p2;              // 释放

    //数组类型
    // int a3[5];
    // int* p3 = a3;
    int* p4 = new int[5];
    delete[] p4;

    // int a5[2][3];
    // int(*p5)[3] = a5;
    int(*p6)[3] = new int[2][3];
    delete[] p6;








}