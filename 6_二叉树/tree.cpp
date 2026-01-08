#include <stdio.h>
struct treeNode
{
    int a;   // 数据成员
    // pFather 操作更灵活
    struct treeNode* dad;  // 对1.2来说,2又有一个指针指向1,相当于双向链表
    struct treeNode* left;
    struct treeNode*right;
};

void look(struct treeNode* root)
{
    if (NULL == root)
    {
        return;
    }
    printf("%d ", root->a);
    look(root->left);   // 递归左子树
    look(root->right);  // 递跪右子树
}

int main()
{
    struct treeNode t1 = { 1 }; // 第一个元素是1,其他初始化为0
    struct treeNode t2 = { 2 };
    struct treeNode t3 = { 3 };
    struct treeNode t4 = { 4 };
    struct treeNode t5 = { 5 };
    struct treeNode t6 = { 6 };
    struct treeNode t7 = { 7 };
    struct treeNode t8 = { 8 };
    struct treeNode t9 = { 9 };
    struct treeNode t10 ={10 }; 

    t1.left = &t2;
    t1.right = &t3;

    t2.left = &t4;
    t2.right = &t5;
    t2.dad = &t1;

    t3.left = &t6;
    t3.right = NULL;
    t3.dad = &t1;

    t4.left = NULL;
    t4.right = NULL;
    t4.dad = &t2;

    t5.left = &t7;
    t5.right = &t8;
    t5.dad = &t2;
    
    t6.left = &t9;
    t6.right = &t10;
    t6.dad = &t3;

    t7.left = NULL;
    t7.right = NULL;
    t7.dad = &t5;

    t8.left = NULL;
    t8.right = NULL;
    t8.dad = &t5;

    t9.left = NULL;
    t9.right = NULL;
    t9.dad = &t6;

    t10.left = NULL;
    t10.right = NULL;
    t10.dad = &t6;
    
    look(&t1);

    return 0;
}