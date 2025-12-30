#include <iostream>
using namespace std;

class Test         //class 关键字，Test 类名，一般首字母大写
{
private:           //私有访问权限
    int a = 12;
public:            //公共访问权限
    void Print()            //输出数据
    {
        cout << a << endl;
    }
    int Get()               //外界获取数据
    {
        return a;
    }
};

int main(void)
{
    Test t;

    t.Print(); //自带输出

    // cout << t.a << endl;   //  不行，a是私有的
    // ‘int Test::a’ is private within this context

    int n = t.Get(); //获取对象数据
    cout << n << endl;
    
    return 0;
}
