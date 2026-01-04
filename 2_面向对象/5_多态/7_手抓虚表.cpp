#include <iostream>
using namespace std;

/********************************************************************
* 手抓虚表
* 虚表是一个指针数组，由于该数组成员是不固定的函数地址类型，所以，
  无法像整型数组那样直接取，但是，可确定一点，数组元素为 4/8 字节大小
//yinkangan@lubuntu:~$ uname -m
//x86_64
* 步骤
* 1、取数组首地址，数组名字，因为要取 8 字节，所以用 long long 取
  CA* pa = new CC;
  long long addr = ((long long*)pa)[0];//x64 环境，强取前 8 字节
  //int addr = ((int*)pa)[0]; //x86 环境，强取前 4 字节
* 2、数组地址转换
  addr 变量里装的是数组地址，要把该地址转成 long long*型，可一次取 8 个
  long long* faddr = (long long*)addr;
  * 3、取数组元素地址，数组元素就是虚函数地址
  faddr + 0;
  faddr + 1;
  faddr + 2; //依次为各元素地址
* 4、取数组元素，数组元素就是各函数地址
*(faddr + 0),*(faddr + 1),*(faddr + 2),*(faddr + 3),
  即 faddr[0],faddr[1],faddr[2],faddr[3],
  fun1(基) fun2(基) fun3(基) fun4(基)
  fun1(基) fun2(派) fun3(派) fun4(基) fun5(派)
* 5、将地址换成相应的虚函数类型，函数什么类型转成什么类型
  void (*f1)() = (void (*)())faddr[0];
  void (*f2)() = (void (*)())faddr[1];
  void (*f3)() = (void (*)())faddr[2];
  void (*f4)() = (void (*)())faddr[3];
* 6、函数调用
  f1();
  f2();
  f3();
  f4();
********************************************************************/

class CA
{
public:
    virtual void fun1() { cout << "基类:fun1" << endl; }
    virtual void fun2() { cout << "基类:fun2" << endl; }
    virtual void fun3() { cout << "基类:fun3" << endl; }
    virtual void fun4() { cout << "基类:fun4" << endl; }
    void fun7() { cout << "基类:fun4" << endl; }
};
class CC : public CA
{
public:
    virtual void fun2() { cout << "派生类:fun2" << endl; }
    virtual void fun3() { cout << "派生类:fun3" << endl; }
    virtual void fun5() { cout << "派生类:fun5" << endl; }
    void fun6() { cout << "派生类:fun6" << endl; }
};

int main()
{
    // 取数组首地址，数组名字，因为要取 8 字节，所以用 long long 取
    CA* p = new CC;
    // long long ：无论 32/64 位系统，大小固定为 8 字节（C++ 标准强制要求）
    long long add = *(long long*)p;   // p[0] == *p

    // addr 变量里装的是数组地址，要把该地址转成 long long*型
    long long* faddr = (long long*)add;

    //  取数组元素地址，数组元素就是虚函数地址
    // faddr + 0;
    // faddr + 1;
    // faddr + 2; //依次为各元素地址

    // 取数组元素，数组元素就是各函数地址
    // faddr[0];
    // faddr[1];
    // faddr[2];
    // faddr[3];
    // faddr[4];

    // 将地址换成相应的虚函数类型，函数什么类型转成什么类型
    void (*f0)() = (void (*)())faddr[0];
    void (*f1)() = (void (*)())faddr[1];
    void (*f2)() = (void (*)())faddr[2];
    void (*f3)() = (void (*)())faddr[3];
    void (*f4)() = (void (*)())faddr[4];

    f0();f1();f2();f3();f4();

    delete p;
}

/*

基类:fun1
派生类:fun2
派生类:fun3
基类:fun4
派生类:fun5


[1] + Done
*/