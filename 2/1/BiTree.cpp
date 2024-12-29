#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;            //��������������
typedef  char TElemType;  //�������Ԫ��ֵ������
typedef  struct BiTNode {  //����������������� 
    TElemType  		data;
    struct BiTNode  *lchild, *rchild; 	//ָ�����Һ��ӽ���ָ��
} BiTNode, *BiTree;

/*
2. ��������������������ʵ��

���ݶ���Ķ�������ṹ����д���л�������������C/C++Դ���룺

��1��CreateBiTree(BiTree &T)������������������ַ����У�����һ�ð���������ṹ�洢�Ķ�������ָ�����Tָ��������ĸ���㡣

��2��PreOrderTraverse(BiTree T)�����ݹ��������������T��������ʵĽ���ַ�����;

��3��InOrderTraverse(BiTree T)�����ݹ��������������T��������ʵĽ���ַ�����;

��4��PostOrderTraverse(BiTree T)�����ݹ���������������T��������ʵĽ���ַ�����;

3. Ӧ�ú�����ʵ��
Ӧ��ʵ��1����һ������TNodes(BiTree T��int d)�����ض�����T�ȷֱ�Ϊ0,1,2�Ľ����������dΪ����������TNodes(T,0)���ض�Ϊ0����Ҷ�ӽ�㣩�Ľ����;
Ӧ��ʵ��2����һ������High(BiTree T)���������T�ĸ߶�;
Ӧ��ʵ��3����һ������CreateBST(BiTree &T, const char *chars)��Ҫ����ݸ������ַ����У��ַ����ظ���������һ�ö��������ڶ������У����������н����ַ�С�ڸ������ַ������������н����ַ����ڸ���㡣��������Ҳ�������������

4. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����

��1������CreateBiTree(T)��������һ�ö�����T��
��2���ֱ���������������������ͺ�������ĵݹ麯�������Ӧ�ı��������
��3������TNodes(T)���������������T�ȷֱ�Ϊ0��1��2�Ľ������
��4������CreateBST(T1,"DBFCAEG")��CreateBST(T2,"ABCDEFG")���������ö������������ǽ������������������High()���������߶ȡ������Ƚ�������
*/


/*
2. ��������������������ʵ��

���ݶ���Ķ�������ṹ����д���л�������������C/C++Դ���룺
*/

// CreateBiTree(BiTree &T)������������������ַ����У�����һ�ð���������ṹ�洢�Ķ�������ָ�����Tָ��������ĸ���㡣
Status CreateBiTree(BiTree &T) {
    char ch;
    scanf(" %c", &ch);// ������ֵ
    if (ch == '#') {
        T = NULL;
    } else {
        T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);// �ݹ鴴��������
        CreateBiTree(T->rchild);// �ݹ鴴��������
    }
    return OK;
}

// PreOrderTraverse(BiTree T)�����ݹ��������������T��������ʵĽ���ַ�����;
Status PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%c ", T->data);
        PreOrderTraverse(T->lchild);// �ݹ����������
        PreOrderTraverse(T->rchild);// �ݹ����������
    }else{
        printf("# ");
    }
    return OK;
}

// InOrderTraverse(BiTree T)�����ݹ��������������T��������ʵĽ���ַ�����;
Status InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild);// �ݹ����������
        printf("%c ", T->data);
        InOrderTraverse(T->rchild);// �ݹ����������
    }else{
        printf("# ");
    }
    return OK;
}

// PostOrderTraverse(BiTree T)�����ݹ���������������T��������ʵĽ���ַ�����;
Status PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild);// �ݹ����������
        PostOrderTraverse(T->rchild);// �ݹ����������
        printf("%c ", T->data);
    }else{
        printf("# ");
    }
    return OK;
}


/*
3. Ӧ�ú�����ʵ��
*/

// Ӧ��ʵ��1����һ������TNodes(BiTree T��int d)�����ض�����T�ȷֱ�Ϊ0,1,2�Ľ����������dΪ����������TNodes(T,0)���ض�Ϊ0����Ҷ�ӽ�㣩�Ľ����;
int TNodes(BiTree T, int d) {
    if (!T) return 0;// ����
    int NodeCount = 0; // ��Ϊd�Ľ����
    
    // ���㵱ǰ���Ķ�
    int degree = 0;
    if (T->lchild) degree++;
    if (T->rchild) degree++;

    // �����ǰ���Ķȵ���d���������1
    if (degree == d) NodeCount = 1;

    // �ݹ�������������������ж�Ϊd�Ľ����
    return NodeCount + TNodes(T->lchild, d) + TNodes(T->rchild, d);
}

// Ӧ��ʵ��2����һ������High(BiTree T)���������T�ĸ߶�;
int High(BiTree T) {
    if (!T) return 0;// ����
    int lhigh = High(T->lchild);// �������߶�
    int rhigh = High(T->rchild);// �������߶�
    return lhigh > rhigh ? lhigh + 1 : rhigh + 1;
}

// Ӧ��ʵ��3����һ������CreateBST(BiTree &T, const char *chars)��Ҫ����ݸ������ַ����У��ַ����ظ���������һ�ö��������ڶ������У����������н����ַ�С�ڸ������ַ������������н����ַ����ڸ���㡣��������Ҳ�������������
Status CreateBST(BiTree &T, const char *chars) {
    if (chars == NULL) return ERROR; // ���ַ�����
    T = (BiTree)malloc(sizeof(BiTNode)); // ���������
    if (!T) exit(OVERFLOW); // �ڴ����ʧ��
    T->data = chars[0]; // ����㸳ֵ
    T->lchild = NULL;
    T->rchild = NULL;
    for (int i = 1; i < strlen(chars); i++) {
        BiTree p = T;
        BiTree q = (BiTree)malloc(sizeof(BiTNode));// �����½��
        if (!q) exit(OVERFLOW);
        q->data = chars[i];
        q->lchild = NULL;
        q->rchild = NULL;
        while (1) { // ������
            if (q->data < p->data) {// ����������
                if (p->lchild == NULL) {
                    p->lchild = q;
                    break;
                } else {
                    p = p->lchild;
                }
            } else {// ����������
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
    printf("��������ֵ(��#����): ");
    CreateBiTree(T);

    printf("����������: ");
    PreOrderTraverse(T);
    printf("\n");

    printf("����������: ");
    InOrderTraverse(T);
    printf("\n");

    printf("����������: ");
    PostOrderTraverse(T);
    printf("\n");

    printf("��Ϊ0�Ľ����: %d\n", TNodes(T, 0));
    printf("��Ϊ1�Ľ����: %d\n", TNodes(T, 1));
    printf("��Ϊ2�Ľ����: %d\n", TNodes(T, 2));

    printf("���ĸ߶�: %d\n", High(T));
    
    BiTree T1;
    CreateBST(T1, "DBFCAEG");
    printf("DBFCAEG����������: ");
    InOrderTraverse(T1);
    printf("\n");
    printf("���ĸ߶�: %d\n", High(T1));

    BiTree T2;
    CreateBST(T2, "ABCDEFG");
    printf("ABCDEFG����������: ");
    InOrderTraverse(T2);
    printf("\n");
    printf("���ĸ߶�: %d\n", High(T2));

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