# C++ 语言基础

本文介绍 C++ 的基本使用，包括控制语句、标准库的常用数据结构等，以便快速上手刷题
¶
## 标准输出

C++ 的标准输出是 `cout`，用 `<<` 运算符把需要打印的内容传递给 `cout`，`endl` 是换行符
```cpp
int a = 10;

// 输出：10
cout << a << endl;

// 可以串联输出
// 输出：Hello, World!
cout << "Hello" << ", " << "World!" << endl;

string s = "abc";
// 输出：abc 10
cout << s << " " << a << endl;
```
当然，C 语言的 `printf` 函数也可以用，但是 `cout` 更加方便，所以我们一般用 `cout`
¶
## 控制语句

编程语言的控制语句一般都比较简单，最常见的无非就是条件判断和循环，下面简单介绍一下
¶
### 条件判断 if else
```cpp
int a = 10;

if (a > 5) {
    cout << "a > 5" << endl;
} else if (a == 5) {
    cout << "a == 5" << endl;
} else {
    cout << "a < 5" << endl;
}
// 输出：a > 5
```
¶
### 循环 for/while

for 和 while 都可以用来做循环，for 循环一般用于已知循环次数的情况，while 循环一般用于未知循环次数的情况。
```cpp
// 0 1 2 3 4
for (int i = 0; i < 5; i++) {
    cout << i << " ";
}

int num = 100;
// 100 50 25 12 6 3 1
while (num > 0) {
    cout << num << " ";
    num /= 2;
}
```
¶
## 基本数据结构

对于标准库的常用数据结构，力扣平台都会默认导入。也就是说，你在写算法题是，可以直接使用 `vector`、`set`、`map` 等关键字创建数据结构。

¶
### 动态数组 `vector`

`vector` 是 C++ 标准库的动态数组

学 C 语言的时候肯定学过 `malloc, int[n]` 等方式来创建静态数组，但是这种方式非常麻烦，而且容易出错。我们做算法题的时候一般使用动态数组 `vector`，而且题目给的输入一般也是 vector 类型。

关于动态数组和静态数组的区别，会在后文 实现动态数组 的章节中详细介绍。

`vector` 的初始化方法如下：
```cpp
#include <vector>

int n = 7, m = 8;

// 初始化一个 int 型的空数组 nums
vector<int> nums;

// 初始化一个大小为 n 的数组 nums，数组中的值默认都为 0
vector<int> nums(n);

// 初始化一个元素为 1, 3, 5 的数组 nums
vector<int> nums{1, 3, 5};

// 初始化一个大小为 n 的数组 nums，其值全都为 2
vector<int> nums(n, 2);

// 初始化一个二维 int 数组 dp
vector<vector<int>> dp;

// 初始化一个大小为 m行* n列 的布尔数组 dp，
// 其中的值都初始化为 true
vector<vector<bool>> dp(m, vector<bool>(n, true));
// 外层：m 表示这个二维数组有 m 行；
// 内层：vector<bool>(n, true) 表示每一行是一个长度为 n 的一维布尔向量，且这个一维向量的 所有 n 个元素都初始化为 true。
```
`vector` 的常用操作：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 10;
    // 数组大小为 10，元素值都为 0
    vector<int> nums(n);
    // 输出 0 (false)
    cout << nums.empty() << endl;
    // 输出：10
    cout << nums.size() << endl;

    // 在数组尾部插入一个元素 20
    nums.push_back(20);
    // 输出：11
    cout << nums.size() << endl;

    // 得到数组最后一个元素的引用
    // 输出：20
    cout << nums.back() << endl;

    // 删除数组的最后一个元素（无返回值）
    nums.pop_back();
    // 输出：10
    cout << nums.size() << endl;

    // 可以通过方括号直接取值或修改
    nums[0] = 11;
    // 输出：11
    cout << nums[0] << endl;

    // 在索引 3 处插入一个元素 99
    nums.insert(nums.begin() + 3, 99);

    // 删除索引 2 处的元素
    nums.erase(nums.begin() + 2);

    // 交换 nums[0] 和 nums[1]
    swap(nums[0], nums[1]);

    // 遍历数组
    // 0 11 99 0 0 0 0 0 0 0
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}
```
以上就是 C++ vector 常用方法，无非就是用索引取元素以及
push_back, pop_back 方法，就刷算法题而言，这些就够了

因为根据「数组」的特性，利用索引访问元素很高效，从尾部增删元素也是很高效的；
而从中间或头部增删元素要涉及搬移数据，很低效。具体的原因会在后文数组基础 中详细介绍
¶

### 双链表 `list`

`list` 是 C++ 标准库中的双向链表容器

初始化方法：
```cpp
#include <list>

int n = 7;

// 初始化一个空的双向链表 lst
std::list<int> lst;

// 初始化一个大小为 n 的链表 lst，链表中的值默认都为 0
std::list<int> lst(n);

// 初始化一个包含元素 1, 3, 5 的链表 lst
std::list<int> lst{1, 3, 5};

// 初始化一个大小为 n 的链表 lst，其中值都为 2
std::list<int> lst(n, 2);
```

`list` 的常用方法：
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    // 初始化链表
    list<int> lst{1, 2, 3, 4, 5};

    // 检查链表是否为空，输出：false
    cout << lst.empty() << endl;

    // 获取链表的大小，输出：5
    cout << lst.size() << endl;

    // 在链表头部插入元素 0
    lst.push_front(0);
    // 在链表尾部插入元素 6
    lst.push_back(6);

    // 获取链表头部和尾部元素，输出：0 6
    cout << lst.front() << " " << lst.back() << endl;

    // 删除链表头部元素
    lst.pop_front();
    // 删除链表尾部元素
    lst.pop_back();

    // 在链表中插入元素
    auto it = lst.begin();  // 迭代器
    // 移动到第三个位置
    advance(it, 2);
    // 在第三个位置插入 99
    lst.insert(it, 99);

    // 删除链表中某个元素
    it = lst.begin();
    // 移动到第二个位置
    advance(it, 1);
    // 删除第二个位置的元素
    lst.erase(it);

    // 遍历链表
    // 输出：1 99 3 4 5
    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
```
一般来说，想在头部增删元素时会使用`双链表`，因为它在头部增删元素的效率比 `vector` 高
但通过索引访问元素，这种场景下我们会使用 `vector`

链表的特点，以及它和动态数组 vector 的适用场景，会在
动手实现链表 介绍，这里就介绍一下它的常用 API
¶
### 队列 `queue`

`queue` 是 C++ 标准库中的队列容器，基于先进先出（FIFO）的原则。队列适用于只允许从一端（队尾）添加元素、从另一端（队头）移除元素的场景

关于队列的实现原理和使用场景，后面的章节会介绍，这里只介绍一下它的常用 API
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // 初始化一个空的整型队列 q
    queue<int> q;

    // 在队尾添加元素
    q.push(10);
    q.push(20);
    q.push(30);

    // 检查队列是否为空，输出：false
    cout << q.empty() << endl;

    // 获取队列的大小，输出：3
    cout << q.size() << endl;

    // 获取队列的队头和队尾元素，输出：10 和 30
    cout << q.front() << " " << q.back() << endl;

    // 删除队头元素
    q.pop();

    // 输出新的队头元素：20
    cout << q.front() << endl;

    return 0;
}
```
¶
### 栈 `stack`

栈是一种后进先出（LIFO）的数据结构，栈适用于只允许在一端（栈顶）添加或移除元素的场景

`stack` 是 C++ 标准库中的栈容器，关于栈的实现原理和使用场景，后面的章节会介绍，这里只介绍一下它的常用 API
```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {

    // 初始化一个空的整型栈 s
    stack<int> s;

    // 向栈顶添加元素
    s.push(10);
    s.push(20);
    s.push(30);

    // 检查栈是否为空，输出：false
    cout << s.empty() << endl;

    // 获取栈的大小，输出：3
    cout << s.size() << endl;

    // 获取栈顶元素，输出：30
    cout << s.top() << endl;

    // 删除栈顶元素
    s.pop();

    // 输出新的栈顶元素：20
    cout << s.top() << endl;

    return 0;
}
```
¶
### 哈希表 `unordered_map`

`unordered_map` 是 C++ 标准库中的一种哈希表实现，它提供了基于键值对（key-value）的存储，提供了常数时间复杂度的查找、插入和删除键值对的操作

哈希表是非常经典的数据结构，它的实现原理和代码实现，会在哈希表原理和基础 介绍，
这里只介绍一下它的常用 API
```cpp
初始化方法：

#include <unordered_map>
using namespace std;

// 初始化一个空的哈希表 map
unordered_map<int, string> hashmap;

// 初始化一个包含一些键值对的哈希表 map
unordered_map<int, string> hashmap{{1, "one"}, {2, "two"}, {3, "three"}};
```
`unordered_map` 的常用方法如下。

>`!`特别注意：`访问不存在的 键 会自动插入 键值对`
>在 C++ 的哈希表中，如果你访问一个不存在的键，它会自动创建这个键，对应的值是默认构造的值。
>这一点和其他语言不同，需要格外注意。记住访问值之前要先判断键是否存在，否则可能会意外地创建新键，导致算法出错。详见下面的示例
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    // 初始化哈希表
    unordered_map<int, string> hashmap{{1, "one"}, {2, "two"}, {3, "three"}};

    // 检查哈希表是否为空，输出：0 (false)
    cout << hashmap.empty() << endl;

    // 获取哈希表的大小，输出：3
    cout << hashmap.size() << endl;

    // 查找指定键是否存在
    // 注意 contains 方法是 C++20 新增的
    // 输出：Key 2 -> two
    if (hashmap.contains(2)) {
        cout << "Key 2 -> " << hashmap[2] << endl;
    } else {
        cout << "Key 2 not found." << endl;
    }

    // 获取指定键对应的值，若不存在会返回默认构造的值
    // 输出空字符串
    cout << hashmap[4] << endl;

    // 插入一个新的键值对
    hashmap[4] = "four";

    // 获取新插入的值，输出：four
    cout << hashmap[4] << endl;

    // 删除键值对
    hashmap.erase(3);

    // 检查删除后键 3 是否存在
    // 输出：Key 3 not found.
    if (hashmap.contains(3)) {
        cout << "Key 3 -> " << hashmap[3] << endl;
    } else {
        cout << "Key 3 not found." << endl;
    }

    // 遍历哈希表
    // 输出（顺序可能不同）：
    // 4 -> four
    // 2 -> two
    // 1 -> one
    for (const auto &pair: hashmap) {
        cout << pair.first << " -> " << pair.second << endl;
    }

    // 特别注意，访问不存在的键会自动创建这个键
    unordered_map<int, string> hashmap2;

    // 键值对的数量是 0
    cout << hashmap2.size() << endl; // 0

    // 访问不存在的键，会自动创建这个键，对应的值是默认构造的值
    cout << hashmap2[1] << endl; // empty string
    cout << hashmap2[2] << endl; // empty string

    // 现在键值对的数量是 2
    cout << hashmap2.size() << endl; // 2

    return 0;
}
```
¶
### 哈希集合 `unordered_set`

`unordered_set` 是 C++ 标准库中的一种哈希集合实现，用于存储不重复的元素，常见使用场景是对元素进行去重。

本站后面的章节会介绍哈希集合的实现原理和代码实现，这里只介绍一下它的常用 API。

初始化方法：
```cpp
#include <unordered_set>
using namespace std;

// 初始化一个空的哈希集合 set
unordered_set<int> uset;

// 初始化一个包含一些元素的哈希集合 set
unordered_set<int> uset{1, 2, 3, 4};

unordered_set 的常用方法：

#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    // 初始化哈希集合
    unordered_set<int> hashset{1, 2, 3, 4};

    // 检查哈希集合是否为空，输出：0 (false)
    cout << hashset.empty() << endl;

    // 获取哈希集合的大小，输出：4
    cout << hashset.size() << endl;

    // 查找指定元素是否存在
    // 输出：Element 3 found.
    if (hashset.contains(3)) {
        cout << "Element 3 found." << endl;
    } else {
        cout << "Element 3 not found." << endl;
    }

    // 插入一个新的元素
    hashset.insert(5);

    // 删除一个元素
    hashset.erase(2);
    // 输出：Element 2 not found.
    if (hashset.contains(2)) {
        cout << "Element 2 found." << endl;
    } else {
        cout << "Element 2 not found." << endl;
    }

    // 遍历哈希集合
    // 输出（顺序可能不同）：
    // 1
    // 3
    // 4
    // 5
    for (const auto &element : hashset) {
        cout << element << endl;
    }

    return 0;
}
```
¶
## 传值和传引用

在 C++ 中，函数参数的传递方式主要有两种：传值和传引用。理解它们的区别对于编写高效的算法代码至关重要，特别是在处理大量数据或需要修改原始数据时。
¶
### 传值（Pass by Value）

传值是指将函数参数的一个副本传递给函数，在函数内部对该副本的修改不会影响到原始数据。

下面是一个例子：
```cpp
#include <iostream>
using namespace std;

void modifyValue(int x) {
    x = 10;  // 只修改副本，不会影响原始数据
}

int main() {
    int num = 5;
    modifyValue(num);
    // 输出：5
    cout << "After modifyValue, num = " << num << endl;
    return 0;
}
```
在上述代码中，num 的值在调用 modifyValue 后并未改变，因为传入的是 num 的副本，函数内的修改仅影响副本。
¶
### 传引用（Pass by Reference）

传引用是指将实参的地址传递给函数，函数可以直接操作原始数据。这意味着对参数的修改会直接影响原始数据。

下面是一个例子：
```cpp
#include <iostream>
using namespace std;

void modifyReference(int &x) {
    x = 10;  // 修改原始数据
}

int main() {
    int num = 5;
    modifyReference(num);
    // 输出：10
    cout << "After modifyReference, num = " << num << endl;
    return 0;
}
```
在上述代码中，num 的值被修改为 10，因为我们传递的是 num 的引用，函数内对 x 的修改直接影响了 num。
¶

## 做算法题时的选择

- 以经验，如果是传递基本类型，比如 int、bool 等，用传值比较多，因为这类数据一般不需要在函数内部修改，而且复制的开销很小

- 如果是传递容器数据结构，比如 vector、unordered_map 等，用传引用比较多，因为可以避免复制数据副本的开销，而且容器一般需要在函数内部修改

- 特别注意一个可能出现的问题，就是当递归函数的参数中有容器数据结构时，千万别使用传值的方式，否则每次递归都会创建一个数据副本，消耗大量的内存和时间，非常容易导致超时或者超内存的错误
¶
## 总结

上面这些基础知识就够开始刷题了

当然，C++ 还提供很多其他数据结构，它们还有很多其他方法和 API，本文都没有介绍。因为一些高级数据结构会在后面的数据结构章节逐步介绍，而每个结构的 API 也是可以在需要的时候查文档的，没必要一开始就全部记住。

[点击转到 C++ 官方文档地址][地址]

[地址]:https://en.cppreference.com/w/