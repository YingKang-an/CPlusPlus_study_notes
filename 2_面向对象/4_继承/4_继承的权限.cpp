#include <iostream>
using namespace std;

//继承的权限功能

/********************************************************************
* 公有继承:public
* 1.功能：继承后，一切照常
********************************************************************/
 
/********************************************************************
* 保护继承:protected
* 1.继承后，基类 protected,public 相当于成为了派生类的 protected 成员
    基类的 private 权限不变，还是只能在基类内使用
* 2.不可以通过派生类的对象，访问基类 public 成员
* 3.派生类的子类可以访问，基类 public,protected 成员
********************************************************************/

/********************************************************************
* 私有继承:private
* 1.继承后，基类 protected,public 成员，相当于派生类的 private 成员
    基类的 private 权限不变，还是只能在基类内使用
* 2.不可以通过派生类的对象，访问基类 public 成员
* 3.派生类的子类不可以访问，基类 public,protected 成员
********************************************************************/


class CA //基类
{
private:
    int a = 12;
protected:
    int c = 14;
public:
    int e = 15;
};


class CE : protected CA
{
    void Print()
    {
        cout << c << endl;
        cout << e << endl;
    }
};


class CC : private CA
{
public:
    void Fun()
    //如果子类成员与父类重名，子类内名字覆盖父类
    {
        // cout << a << endl;
        cout << c << endl;
        cout << e << endl; //使用的是派生类 CC 的 e
        cout << CA::e << endl; //使用的是基类 CA 的 e
    }
};

class CD : public CC
{
    void Print()
    {
        //cout << c << endl;
        //cout << e << endl;
    }
};


int main(void)
{
    CE ce;
    // ce.c;
    // ce.e;

    CC c; //定义派生类对象
    c.Fun();
    //c.c;
    //c.e;
    //cout << c.e << endl; //使用的是派生类 CC 的 e
    //cout << c.CA::e << endl; //使用的是基类 CA 的 e

    CA ca;
    //ca.c;
    ca.e;

    return 0;
}
