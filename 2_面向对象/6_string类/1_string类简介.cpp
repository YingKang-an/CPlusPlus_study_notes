// string类，专门处理字符串的

#include <iostream>
#include <string>

//C 语言里是 string.h

using namespace std;
//string 的名字空间也是 std


/** 构造函数 *******************************************************
* string();
* 字符参数
* string(size_type count, value_type ch);
* 字符串参数
* string(const value_type* s);
* string(const value_type* s, size_type count);
* string(const value_type* s, size_type pos, size_type count);
* string 对象参数
* string(const string& other);
* string(const string& other, size_type pos);
* string(const string& other, size_type pos, size_type count);
* string(string&& other);//(string)"erty" string("qwe")
*******************************************************************/
