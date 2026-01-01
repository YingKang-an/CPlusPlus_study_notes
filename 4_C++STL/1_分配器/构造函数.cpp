#include <iostream>
#include <memory>

using namespace std;

/************************************************************ 

 * 分配器 allocator 模板类
 * 管理容器内存的 类，申请，释放，赋值
 * 构造函数
-------------------------------------------------------------
 * allocator();                          无参数 构造

 * allocator(const allocator& other)；   拷贝   构造

 * template< class U >
   allocator( const allocator<U>& other) 不同类型 拷贝构造

************************************************************/

int main (void)
{
    allocator<int> a;
    allocator<int> c(a);
    allocator<double> d(c);

/**************************************************************

 * 申请释放内存
 --------------------------------------------------------------
 * T* allocator( std::size_t n );           申请一段未初始化的空间 sizeof(T)*n

 * void deallocate( T* p, std::size_t n );  释放

 * size_type max_size();                    返回allocate可申请最大n

 *************************************************************/

    int* p = a.allocate(5);
    cout << a.max_size() << endl;
    a.deallocate(p, 5);

/**************************************************************
 * 空间赋值
 --------------------------------------------------------------
 * template< class U, class... Args >

 * void construct( U* p, Args&&... args );   设置空间数据

 * void destroy( U* p);

***************************************************************/

    // allocator<int>a;
    // int* p = a.allocate(5)
    int i;
    for (i = 0; i < 5; i++)
    {
        a.construct(p + i, 12); // 每个元素赋值 12
    }

    for (i = 0; i < 5; i++)
    {
        cout << p[i] << ' ' << endl;
    }

    for (i = 0; i < 5; i++)
    {
        a.destroy(p + i); // 调用每个对象的析构函数
    }

    a.deallocate(p, 5); // 释放所有空间

    return 0;
}






