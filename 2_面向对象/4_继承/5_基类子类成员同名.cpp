#include <iostream>
using namespace std;

// 基类子类成员名相同

class CA //基类
{
public:
    int e = 3;
};

class CC : public CA
{
public:
    int e = 4;  // 专业名词：重写
    void Fun()
    //子类成员与父类重名，子类内名字覆盖父类
    {
    cout << e << endl; //使用的是派生类 CC 的 e
    cout << CA::e << endl; //使用的是基类 CA 的 e
    }
};

int main(void)
{
    CC c; //定义派生类对象
    c.Fun();
    cout << c.e << endl; //使用的是派生类 CC 的 e
    cout << c.CA::e << endl; //使用的是基类 CA 的 e

    return 0;
}
