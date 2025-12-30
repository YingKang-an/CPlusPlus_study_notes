#include <iostream>
using namespace std;
/*************************************************** 
    三个：

    private //私有的，只能在所在类内调用，只能定义，不能写算法
    protected //受保护的，只能在所在类以及子类中使用，继承部分讲解
    public //公有的，可以在类内外需要的位置调用

    书写格式：
    
    private:
    protected:
    public:

    作用范围：从关键字以下，直到下一个关键字或者类结尾
    最上方不写，默认是private
****************************************************/
class Test
{
    // 最上面不写，默认是 private
    int c; //默认是 private
    int a; //默认是 private
public: //公共访问权限
    void Print() { cout << a << endl; }
    int Get() { return a; }
};

// 数量不限制，顺序不限制，可以用来分类使用
class Test1
{
private: //整型变量
    int c;
    long a;
private: //指针变量                 //成员很多，可以多写
    double* p1;
    float* p2;
public: //公共访问权限
    void Print() { cout << a << endl; }
    int Get() { return a; }
    void Set(int v) { a = v; }
private: //非公共接口函数，类内部逻辑调用
    void Init() {}
    void Free() {}
    void Sort() {}
public: //空格也行
    void Add() {}
    void Del() {}
    void End() {}
};
