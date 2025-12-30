#include <iostream>
using namespace std;

/*

深、浅拷贝
上面这种单纯的值复制，叫浅拷贝，对应的有深拷贝
深拷贝针对指针成员，并且有申请空间与释放空间的操作，需要专门写处理

*/

class Test
{
private:
    int a;
    int* p;
public:
    Test(int a)
    {
        this->a = a;
        p = new int[10]{1,2,3,4,5,6,7,8,9,0};
    }
    Test(const Test& t)  // 默认的拷贝构造是浅拷贝 表面工作
    {
        a = t.a;
        // p = t.p;      // 浅拷贝只会让t2的p也指向t1的p

        p = new int[10];     //  对于指针成员，需要申请空间时候，必须手写深拷贝构造
        for (int i = 0; i < 10; i++)
            p[i] = t.p[i];   //  深拷贝 申请空间与释放空间并填写数据

        cout << "拷贝构造" << endl;
    }
    ~Test()
    {
        delete p;
        cout << "析构函数" << endl;
    }
};

void Fun(Test& s)   // 其他函数用 引用避免拷贝
{
    ;
}

int main(void)
{
    Test t1(34);
    Test t2(t1);  // 导致 ~Test 函数释放了t1的空间，出现野指针
                  //t2 走拷贝构造，将 t2.p = t1.p; 两个 p 指向同一块空间

    Fun(t1);
                  
    return 0;     //t1t2 调用析构，都 delete p; 释放两次，异常中断
}