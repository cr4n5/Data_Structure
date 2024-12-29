#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;            //声明函数类型名
typedef  char TElemType;  //声明结点元素值得类型
typedef  struct BiTNode {  //定义二叉链表结点类型 
    TElemType  		data;
    struct BiTNode  *lchild, *rchild; 	//指向左右孩子结点的指针
} BiTNode, *BiTree;

/*
2. 二叉树基本操作函数的实现

根据定义的二叉链表结构，编写下列基本操作函数的C/C++源代码：

（1）CreateBiTree(BiTree &T)——根据先序遍历的字符序列，创建一棵按二叉链表结构存储的二叉树，指针变量T指向二叉树的根结点。

（2）PreOrderTraverse(BiTree T)——递归先序遍历二叉树T，输出访问的结点字符序列;

（3）InOrderTraverse(BiTree T)——递归中序遍历二叉树T，输出访问的结点字符序列;

（4）PostOrderTraverse(BiTree T)——递归后序序遍历二叉树T，输出访问的结点字符序列;

3. 应用函数的实现
应用实例1：编一个函数TNodes(BiTree T，int d)，返回二叉树T度分别为0,1,2的结点数，其中d为结点度数，如TNodes(T,0)返回度为0（即叶子结点）的结点数;
应用实例2：编一个函数High(BiTree T)，求二叉树T的高度;
应用实例3：编一个函数CreateBST(BiTree &T, const char *chars)，要求根据给定的字符序列（字符不重复），生成一棵二叉树。在二叉树中，左子树所有结点的字符小于根结点的字符，右子树所有结点的字符大于根结点。左右子树也满足这个条件。

4. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：

（1）调用CreateBiTree(T)函数生成一棵二叉树T。
（2）分别调用先序遍历、中序遍历和后序遍历的递归函数输出相应的遍历结果；
（3）调用TNodes(T)函数，输出二叉树T度分别为0、1、2的结点数。
（4）调用CreateBST(T1,"DBFCAEG")，CreateBST(T2,"ABCDEFG")，创建两棵二叉树，对它们进行中序遍历，并调用High()函数输出其高度。分析比较其结果。
*/


/*
2. 二叉树基本操作函数的实现

根据定义的二叉链表结构，编写下列基本操作函数的C/C++源代码：
*/

// CreateBiTree(BiTree &T)——根据先序遍历的字符序列，创建一棵按二叉链表结构存储的二叉树，指针变量T指向二叉树的根结点。
Status CreateBiTree(BiTree &T) {
    char ch;
    scanf(" %c", &ch);// 输入结点值
    if (ch == '#') {
        T = NULL;
    } else {
        T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);// 递归创建左子树
        CreateBiTree(T->rchild);// 递归创建右子树
    }
    return OK;
}

// PreOrderTraverse(BiTree T)——递归先序遍历二叉树T，输出访问的结点字符序列;
Status PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%c ", T->data);
        PreOrderTraverse(T->lchild);// 递归遍历左子树
        PreOrderTraverse(T->rchild);// 递归遍历右子树
    }else{
        printf("# ");
    }
    return OK;
}

// InOrderTraverse(BiTree T)——递归中序遍历二叉树T，输出访问的结点字符序列;
Status InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild);// 递归遍历左子树
        printf("%c ", T->data);
        InOrderTraverse(T->rchild);// 递归遍历右子树
    }else{
        printf("# ");
    }
    return OK;
}

// PostOrderTraverse(BiTree T)——递归后序序遍历二叉树T，输出访问的结点字符序列;
Status PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild);// 递归遍历左子树
        PostOrderTraverse(T->rchild);// 递归遍历右子树
        printf("%c ", T->data);
    }else{
        printf("# ");
    }
    return OK;
}


/*
3. 应用函数的实现
*/

// 应用实例1：编一个函数TNodes(BiTree T，int d)，返回二叉树T度分别为0,1,2的结点数，其中d为结点度数，如TNodes(T,0)返回度为0（即叶子结点）的结点数;
int TNodes(BiTree T, int d) {
    if (!T) return 0;// 空树
    int NodeCount = 0; // 度为d的结点数
    
    // 计算当前结点的度
    int degree = 0;
    if (T->lchild) degree++;
    if (T->rchild) degree++;

    // 如果当前结点的度等于d，则计数加1
    if (degree == d) NodeCount = 1;

    // 递归计算左子树和右子树中度为d的结点数
    return NodeCount + TNodes(T->lchild, d) + TNodes(T->rchild, d);
}

// 应用实例2：编一个函数High(BiTree T)，求二叉树T的高度;
int High(BiTree T) {
    if (!T) return 0;// 空树
    int lhigh = High(T->lchild);// 左子树高度
    int rhigh = High(T->rchild);// 右子树高度
    return lhigh > rhigh ? lhigh + 1 : rhigh + 1;
}

// 应用实例3：编一个函数CreateBST(BiTree &T, const char *chars)，要求根据给定的字符序列（字符不重复），生成一棵二叉树。在二叉树中，左子树所有结点的字符小于根结点的字符，右子树所有结点的字符大于根结点。左右子树也满足这个条件。
Status CreateBST(BiTree &T, const char *chars) {
    if (chars == NULL) return ERROR; // 空字符序列
    T = (BiTree)malloc(sizeof(BiTNode)); // 创建根结点
    if (!T) exit(OVERFLOW); // 内存分配失败
    T->data = chars[0]; // 根结点赋值
    T->lchild = NULL;
    T->rchild = NULL;
    for (int i = 1; i < strlen(chars); i++) {
        BiTree p = T;
        BiTree q = (BiTree)malloc(sizeof(BiTNode));// 创建新结点
        if (!q) exit(OVERFLOW);
        q->data = chars[i];
        q->lchild = NULL;
        q->rchild = NULL;
        while (1) { // 插入结点
            if (q->data < p->data) {// 插入左子树
                if (p->lchild == NULL) {
                    p->lchild = q;
                    break;
                } else {
                    p = p->lchild;
                }
            } else {// 插入右子树
                if (p->rchild == NULL) {
                    p->rchild = q;
                    break;
                } else {
                    p = p->rchild;
                }
            }
        }
    }
    return OK;
}


int main(){
    BiTree T;
    printf("请输入结点值(以#结束): ");
    CreateBiTree(T);

    printf("先序遍历结果: ");
    PreOrderTraverse(T);
    printf("\n");

    printf("中序遍历结果: ");
    InOrderTraverse(T);
    printf("\n");

    printf("后序遍历结果: ");
    PostOrderTraverse(T);
    printf("\n");

    printf("度为0的结点数: %d\n", TNodes(T, 0));
    printf("度为1的结点数: %d\n", TNodes(T, 1));
    printf("度为2的结点数: %d\n", TNodes(T, 2));

    printf("树的高度: %d\n", High(T));
    
    BiTree T1;
    CreateBST(T1, "DBFCAEG");
    printf("DBFCAEG中序遍历结果: ");
    InOrderTraverse(T1);
    printf("\n");
    printf("树的高度: %d\n", High(T1));

    BiTree T2;
    CreateBST(T2, "ABCDEFG");
    printf("ABCDEFG中序遍历结果: ");
    InOrderTraverse(T2);
    printf("\n");
    printf("树的高度: %d\n", High(T2));

    return 0;
}

// test data
// A B D # F # # # C E # # #
//       A
//      / \
//     B   C
//    /   /
//   D   E
//    \
//     F