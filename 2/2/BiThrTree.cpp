#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;
typedef  char TElemType;
typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    int  LTag, RTag;
}BiThrNode,*BiThrTree;  

/*
2.  线索二叉树基本操作与应用函数的实现 

（1） InitBiThrTree(BiThrTree &T)——根据先序遍历的字符序列，创建一棵按线索二叉链表结构存储的尚未线索化的二叉树，在该二叉链表中，若结点有左孩子（即lchild非空），则其LTag=0，否则LTag=1，若二叉树的结点有右孩子（即rchild非空），则其RTag=0，否则RTag=1。指针变量T指向二叉树的根结点。
（2）InOrderThreading(BiThrTree &Thrt, BiThrTree T)——对InitBiThrTree(BiThrTree &T)函数创建的二叉树T按中序遍历进行线索化，线索化后的中序线索二叉树带“头结点”，头结点的data域存放字符'@'，指针Thrt指向该头结点，头结点的左指针指向二叉树的根结点（LTag=0），右指针指向该二叉树中序遍历的最后一个结点（RTag=1）。同时，该二叉树中序遍历第一个结点的左指针指向头结点（LTag=1），中序遍历最后一个结点的右指针也指向头结点（RTag=1）。

线索化过程如下：设p指向当前访问的结点，pre指向p的前驱结点，则：
            (1) 对p所指的结点完成前驱线索化，即：p->LTag=1;   p->lchild=pre;
            (2) 对pre所指的结点完成后继线索化，即：pre->RTag=1;  pre->rchild=p;

建议采用非递归的中序遍历方法实现，pre的初始值为头结点指针Thrt，在中序遍历访问结点的位置（printf()）,做以下操作：

        if (!p->lchild) {p->LTag=1; p->lchild=pre;}
        if (!pre->rchild) {pre->RTag=1; pre->rchild=p;}
        pre=p;

在遍历结束后，还要对最后一个结点线索化

        pre->rchild=Thrt;  pre->RTag=1;
        Thrt->rchild=pre;

（3）InOrderTraverse(BiThrTree T)——按孩子中序遍历线索二叉树（递归），输出每个结点的数据，格式如下：

            | LTag | 左指针所指元素 | 本结点的值 | 右指针所指元素 | RTag |

如：     | 1 | ^ | D | F | 0 |  或   | 1 | @ | D | F | 0 |  

（4）InOrderTraverse_Thr(BiThrTree T)——按线索和孩子中序遍历线索二叉树（非递归），输出每个结点的数据，格式同上。

3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：

（1）调用InitBiThrTree(T)函数，创建一棵按线索二叉链表结构存储的尚未线索化的二叉树；二叉树结构如下：
（2）调用InOrderTraverse(T)函数，输出每个结点的数据。
（3）调用InOrderThreading(Thrt, T)函数，将T线索化成一棵中序线索二叉树；
（4）调用InOrderTraverse(Thrt)函数，输出每个结点的数据。
（5）调用InOrderTraverse_Thr(Thrt)函数，输出每个结点的数据。
*/

// InitBiThrTree(BiThrTree &T)——根据先序遍历的字符序列，创建一棵按线索二叉链表结构存储的尚未线索化的二叉树，在该二叉链表中，若结点有左孩子（即lchild非空），则其LTag=0，否则LTag=1，若二叉树的结点有右孩子（即rchild非空），则其RTag=0，否则RTag=1。指针变量T指向二叉树的根结点。
Status InitBiThrTree(BiThrTree &T) {
    char ch;
    scanf(" %c", &ch);// 输入结点值
    if (ch == '#') {
        T = NULL;
    } else {
        T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (!T) exit(OVERFLOW);
        T->data = ch;
        InitBiThrTree(T->lchild);
        InitBiThrTree(T->rchild);
        T->LTag = (T->lchild != NULL) ? 0 : 1;
        T->RTag = (T->rchild != NULL) ? 0 : 1;
    }
    return OK;
}

// InOrderThreading(BiThrTree &Thrt, BiThrTree T)——对InitBiThrTree(BiThrTree &T)函数创建的二叉树T按中序遍历进行线索化，线索化后的中序线索二叉树带“头结点”，头结点的data域存放字符'@'，指针Thrt指向该头结点，头结点的左指针指向二叉树的根结点（LTag=0），右指针指向该二叉树中序遍历的最后一个结点（RTag=1）。同时，该二叉树中序遍历第一个结点的左指针指向头结点（LTag=1），中序遍历最后一个结点的右指针也指向头结点（RTag=1）。
// 线索化过程如下：设p指向当前访问的结点，pre指向p的前驱结点，则：
BiThrTree pre; // 全局变量，指向当前访问结点的前驱结点
void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild); 
        if (!p->lchild) { // 如果没有左孩子
            p->LTag = 1;
            p->lchild = pre;// 左指针指向前驱
        }
        if (!pre->rchild) {// 如果前驱没有右孩子
            pre->RTag = 1;
            pre->rchild = p;
        }
        pre = p; // pre指向当前结点
        InThreading(p->rchild);
    }
}


Status InOrderThreading(BiThrTree &Thrt, BiThrTree T) {
    if (!T) { 
        Thrt = NULL;
        return OK;
    }
    Thrt = (BiThrTree)malloc(sizeof(BiThrNode)); 
    if (!Thrt) return ERROR;
    Thrt->data = '@';
    Thrt->LTag = 0; Thrt->RTag = 1;// 头结点
    Thrt->rchild = Thrt; // 右指针暂时回指
    if (!T) {// 空树
        Thrt->lchild = Thrt; // 左指针回指
    } else {
        Thrt->lchild = T;// 左指针指向根结点
        pre = Thrt;// pre指向头结点
        InThreading(T);
        pre->rchild = Thrt;// 最后一个结点线索化
        pre->RTag = 1;
        Thrt->rchild = pre;
    }
    return OK;
}

// InOrderTraverse(BiThrTree T)——按孩子中序遍历线索二叉树（递归），输出每个结点的数据，格式如下：
// | LTag | 左指针所指元素 | 本结点的值 | 右指针所指元素 | RTag |
// 如： | 1 | ^ | D | F | 0 |  或   | 1 | @ | D | F | 0 |
Status InOrderTraverse(BiThrTree T) {
    if (T) {
        InOrderTraverse(T->LTag == 0 ? T->lchild : NULL);
        printf("| %d | %c | %c | %c | %d | \n", T->LTag, T->lchild ? T->lchild->data : '^', T->data, T->rchild ? T->rchild->data : '^', T->RTag);
        InOrderTraverse(T->RTag == 0 ? T->rchild : NULL);
    }
    return OK;
}

// InOrderTraverse_Thr(BiThrTree T)——按线索和孩子中序遍历线索二叉树（非递归），输出每个结点的数据，格式同上。
Status InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p = T->lchild;// p指向根结点
    while (p != T) {// 遍历线索二叉树
        while (p->LTag == 0) p = p->lchild;// 找到中序遍历的第一个结点
        printf("| %d | %c | %c | %c | %d | \n", p->LTag, p->lchild->data, p->data, p->rchild->data, p->RTag);
        while (p->RTag == 1 && p->rchild != T) {// 遍历线索，找到中序遍历的下一个结点
            p = p->rchild;
            printf("| %d | %c | %c | %c | %d | \n", p->LTag, p->lchild->data , p->data, p->rchild->data, p->RTag);
        }
        p = p->rchild;// p指向下一个结点
    }
    return OK;
}


int main(){
    BiThrTree T, Thrt;
    printf("请输入结点值(以#结束): ");
    InitBiThrTree(T);

    printf("中序遍历结果: \n");
    InOrderTraverse(T);
    printf("\n");

    InOrderThreading(Thrt, T);
    printf("线索化中序遍历结果: \n");
    InOrderTraverse(Thrt);
    printf("\n");

    printf("线索化中序遍历结果(非递归): \n");
    InOrderTraverse_Thr(Thrt);
    printf("\n");

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