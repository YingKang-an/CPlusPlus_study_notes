#include <iostream>
using namespace std;

//多态的实现原理：虚表 虚函数列表
//多态的具体实现取决于编译器的作者，虚表的实现方式，是其中一种

/********************************************************************
* 虚表：
* 虚表是一个元素为虚函数地址的数组，每个元素都是一个虚函数地址
* 虚表不是成员，他的首地址装对象首部

* 实现过程：
* 1、带虚函数的对象，其对象空间的首(4/8)字节装着虚表的地址
* 2、创建子类对象，会先构造父类的空间，将父类的虚函数依次装入虚表
* 3、再构造子类空间，将子类的虚函数依次装入虚表
* 4、如果有重写父类的虚函数，则在表中替换覆盖掉父类的虚函数地址

* 调用过程：
* 1、父类指针调用的是虚函数
* 2、则在表中找到该函数
* 3、执行该函数
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
    CA* pa = new CC; //定义对象
}
// 先构造父类空间，表 1
// |fun1(基)|fun2(基)|fun3(基)|fun4(基)|
// 在构造子类空间，在表 1 的基础上变化如下，表 2
// |fun1(基)|fun2(派)|fun3(派)|fun4(基)|fun5(派)|
// 此时的虚表即为表 2，(只有一张表 2，俩表展示的是表的变化过程)
// 非虚函数不入表
// pa->虚函数，就是根据名字，到表里找，调用表中的实时函数