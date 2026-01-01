#include <iostream>
using namespace std;

/******************************************************************
* 继承的作用:
* 1.访问控制，通过 protected 等关键字管理成员的访问权限
* 2.代码复用，减少重复编写相同的代码，提升工作效率
* 3.实现多态，允许子类重写父类方法，增强程序的灵活性
* 4.使得代码的拓展与修改更加的方便，更具想象力
* 5.定义接口规范，通过抽象基类强制子类实现特定方法
* 6.支持一些设计模式的实现
*******************************************************************/

//公共类：基类，平时口头也叫父类
//各自类：派生类，平时口头也叫子类

/** 一段继承代码 **/

class Car //基类
{
public:
    void CheLun()
    {
        cout << "我有轮子" << endl;
    }
    void FangXiang()
    {
        cout << "我有方向盘" << endl;
    }
};

class YueYeCar : public Car //公有继承 Car,冒号
{
public:
    void YueYeSys()
    {
        cout << "我有越野控制系统" << endl;
    }
};

class KaCar : public Car //公有继承 Car,冒号
{
public:
    void GaiZhuangSys()
    {
        cout << "我可以改装成多功能工具车" << endl;
    }
};

/******************************************************
* 基类： Car
* 派生类：YueYeCar KaCar
*******************************************************/

int main(void)
{
    //Car 类对象,只能调用 Car 的成员
    Car car;
    car.CheLun();
    car.FangXiang();
    //YueYeCar 类对象，可以调用 Car 类成员，可以调用 YueYeCar 成员
    YueYeCar yycar;
    yycar.CheLun();
    yycar.FangXiang();
    yycar.YueYeSys();
    //KaCar 类对象，可以调用 Car 类成员，可以调用 KaCar 成员
    KaCar kcar;
    kcar.CheLun();
    kcar.FangXiang();
    kcar.GaiZhuangSys();
    //YueYeCar、KaCar 两个子类没有关系，各是各的
    return 0;
}
