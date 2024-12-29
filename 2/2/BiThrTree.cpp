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
2.  ��������������������Ӧ�ú�����ʵ�� 

��1�� InitBiThrTree(BiThrTree &T)������������������ַ����У�����һ�ð�������������ṹ�洢����δ�������Ķ��������ڸö��������У�����������ӣ���lchild�ǿգ�������LTag=0������LTag=1�����������Ľ�����Һ��ӣ���rchild�ǿգ�������RTag=0������RTag=1��ָ�����Tָ��������ĸ���㡣
��2��InOrderThreading(BiThrTree &Thrt, BiThrTree T)������InitBiThrTree(BiThrTree &T)���������Ķ�����T������������������������������������������������ͷ��㡱��ͷ����data�����ַ�'@'��ָ��Thrtָ���ͷ��㣬ͷ������ָ��ָ��������ĸ���㣨LTag=0������ָ��ָ��ö�����������������һ����㣨RTag=1����ͬʱ���ö��������������һ��������ָ��ָ��ͷ��㣨LTag=1��������������һ��������ָ��Ҳָ��ͷ��㣨RTag=1����

�������������£���pָ��ǰ���ʵĽ�㣬preָ��p��ǰ����㣬��
            (1) ��p��ָ�Ľ�����ǰ��������������p->LTag=1;   p->lchild=pre;
            (2) ��pre��ָ�Ľ����ɺ��������������pre->RTag=1;  pre->rchild=p;

������÷ǵݹ�������������ʵ�֣�pre�ĳ�ʼֵΪͷ���ָ��Thrt��������������ʽ���λ�ã�printf()��,�����²�����

        if (!p->lchild) {p->LTag=1; p->lchild=pre;}
        if (!pre->rchild) {pre->RTag=1; pre->rchild=p;}
        pre=p;

�ڱ��������󣬻�Ҫ�����һ�����������

        pre->rchild=Thrt;  pre->RTag=1;
        Thrt->rchild=pre;

��3��InOrderTraverse(BiThrTree T)������������������������������ݹ飩�����ÿ���������ݣ���ʽ���£�

            | LTag | ��ָ����ָԪ�� | ������ֵ | ��ָ����ָԪ�� | RTag |

�磺     | 1 | ^ | D | F | 0 |  ��   | 1 | @ | D | F | 0 |  

��4��InOrderTraverse_Thr(BiThrTree T)�����������ͺ�����������������������ǵݹ飩�����ÿ���������ݣ���ʽͬ�ϡ�

3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����

��1������InitBiThrTree(T)����������һ�ð�������������ṹ�洢����δ�������Ķ��������������ṹ���£�
��2������InOrderTraverse(T)���������ÿ���������ݡ�
��3������InOrderThreading(Thrt, T)��������T��������һ������������������
��4������InOrderTraverse(Thrt)���������ÿ���������ݡ�
��5������InOrderTraverse_Thr(Thrt)���������ÿ���������ݡ�
*/

// InitBiThrTree(BiThrTree &T)������������������ַ����У�����һ�ð�������������ṹ�洢����δ�������Ķ��������ڸö��������У�����������ӣ���lchild�ǿգ�������LTag=0������LTag=1�����������Ľ�����Һ��ӣ���rchild�ǿգ�������RTag=0������RTag=1��ָ�����Tָ��������ĸ���㡣
Status InitBiThrTree(BiThrTree &T) {
    char ch;
    scanf(" %c", &ch);// ������ֵ
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

// InOrderThreading(BiThrTree &Thrt, BiThrTree T)������InitBiThrTree(BiThrTree &T)���������Ķ�����T������������������������������������������������ͷ��㡱��ͷ����data�����ַ�'@'��ָ��Thrtָ���ͷ��㣬ͷ������ָ��ָ��������ĸ���㣨LTag=0������ָ��ָ��ö�����������������һ����㣨RTag=1����ͬʱ���ö��������������һ��������ָ��ָ��ͷ��㣨LTag=1��������������һ��������ָ��Ҳָ��ͷ��㣨RTag=1����
// �������������£���pָ��ǰ���ʵĽ�㣬preָ��p��ǰ����㣬��
BiThrTree pre; // ȫ�ֱ�����ָ��ǰ���ʽ���ǰ�����
void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild); 
        if (!p->lchild) { // ���û������
            p->LTag = 1;
            p->lchild = pre;// ��ָ��ָ��ǰ��
        }
        if (!pre->rchild) {// ���ǰ��û���Һ���
            pre->RTag = 1;
            pre->rchild = p;
        }
        pre = p; // preָ��ǰ���
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
    Thrt->LTag = 0; Thrt->RTag = 1;// ͷ���
    Thrt->rchild = Thrt; // ��ָ����ʱ��ָ
    if (!T) {// ����
        Thrt->lchild = Thrt; // ��ָ���ָ
    } else {
        Thrt->lchild = T;// ��ָ��ָ������
        pre = Thrt;// preָ��ͷ���
        InThreading(T);
        pre->rchild = Thrt;// ���һ�����������
        pre->RTag = 1;
        Thrt->rchild = pre;
    }
    return OK;
}

// InOrderTraverse(BiThrTree T)������������������������������ݹ飩�����ÿ���������ݣ���ʽ���£�
// | LTag | ��ָ����ָԪ�� | ������ֵ | ��ָ����ָԪ�� | RTag |
// �磺 | 1 | ^ | D | F | 0 |  ��   | 1 | @ | D | F | 0 |
Status InOrderTraverse(BiThrTree T) {
    if (T) {
        InOrderTraverse(T->LTag == 0 ? T->lchild : NULL);
        printf("| %d | %c | %c | %c | %d | \n", T->LTag, T->lchild ? T->lchild->data : '^', T->data, T->rchild ? T->rchild->data : '^', T->RTag);
        InOrderTraverse(T->RTag == 0 ? T->rchild : NULL);
    }
    return OK;
}

// InOrderTraverse_Thr(BiThrTree T)�����������ͺ�����������������������ǵݹ飩�����ÿ���������ݣ���ʽͬ�ϡ�
Status InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p = T->lchild;// pָ������
    while (p != T) {// ��������������
        while (p->LTag == 0) p = p->lchild;// �ҵ���������ĵ�һ�����
        printf("| %d | %c | %c | %c | %d | \n", p->LTag, p->lchild->data, p->data, p->rchild->data, p->RTag);
        while (p->RTag == 1 && p->rchild != T) {// �����������ҵ������������һ�����
            p = p->rchild;
            printf("| %d | %c | %c | %c | %d | \n", p->LTag, p->lchild->data , p->data, p->rchild->data, p->RTag);
        }
        p = p->rchild;// pָ����һ�����
    }
    return OK;
}


int main(){
    BiThrTree T, Thrt;
    printf("��������ֵ(��#����): ");
    InitBiThrTree(T);

    printf("����������: \n");
    InOrderTraverse(T);
    printf("\n");

    InOrderThreading(Thrt, T);
    printf("����������������: \n");
    InOrderTraverse(Thrt);
    printf("\n");

    printf("����������������(�ǵݹ�): \n");
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