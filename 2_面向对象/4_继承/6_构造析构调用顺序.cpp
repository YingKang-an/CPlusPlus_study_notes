#include <iostream>
using namespace std;

/***********************************
* 构造函数调用顺序：由父到子
* 析构函数调用顺序：由子到父
***********************************/
class CA
{
public:
    CA() { cout << "爷爷" << endl; }
    ~CA() { cout << "~爷爷" << endl; }
};

class CC : public CA
{
public:
    CC() { cout << "父亲" << endl; }
    ~CC() { cout << "~父亲" << endl; }
};

class CD : public CC
{
public:
    CD() { cout << "儿子" << endl; }
    ~CD() { cout << "~儿子" << endl; }
};

int main(void)
{
    CD d; //定义儿子对象
    return 0;
}

/***************************************
* 构造：爷爷 父亲 儿子
* 析构：~儿子 ~父亲 ~爷爷
****************************************/
