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

typedef  struct  {  //定义二叉链表结点类型 
      int weight;
      int parent, lchild, rchild; 
} HTNode, *HTree;           //动态分配数组存储赫夫曼树

typedef  char **HTCode;  //动态分配字符串数组存储赫夫曼编码表

/*
2.  赫夫曼树基本操作函数的实现

（1）InitHTree(HTree &HT, int *w, int n)——初始化赫夫曼树，其中w和n分别是权重数组和叶子结点数。要求根据定义的赫夫曼树结构，申请一个由2n-1个元素组成的一维数组HT，HT[0..n-1]存放n个叶子结点的权重，其他元素和数据域的值度置成-1。
（2）CreateHTree(HTree &HT, int n)——构造赫夫曼树HT，其中n是叶子结点数。要求根据赫夫曼树的构造规则，生成一个由2n-1个结点组成的一棵赫夫曼树。
（3） HTCoding(HTree HT, HTCode &HC,int n)——生成赫夫曼编码HC，其中n是叶子结点数。要求根据生成的赫夫曼树HT，生成n个叶子结点的赫夫曼编码并输出。


3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：

（1）设共有8个叶子结点，其权重w={5, 29, 7, 8, 14, 23, 3, 11}，调用InitHTree()函数，将叶子结点的权重存入赫夫曼树的存储结构HT中，并输出HT的内容；
（2）调用CreateHTree()函数，构造一棵完整的赫夫曼树HT，并输出HT的内容；
（3）调用HTCoding()函数，输出赫夫曼树HT中各叶子结点的赫夫曼编码。
*/

// InitHTree(HTree &HT, int *w, int n)——初始化赫夫曼树，其中w和n分别是权重数组和叶子结点数。要求根据定义的赫夫曼树结构，申请一个由2n-1个元素组成的一维数组HT，HT[0..n-1]存放n个叶子结点的权重，其他元素和数据域的值度置成-1。
Status InitHTree(HTree &HT, int *w, int n) {
    HT = (HTree)malloc((2*n-1)*sizeof(HTNode));// 分配存储空间
    if (!HT) exit(OVERFLOW);
    for (int i = 0; i < 2*n-1; i++) {// 初始化赫夫曼树
        if (i < n) {
            HT[i].weight = w[i];
        } else {
            HT[i].weight = -1;
        }
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    return OK;
}

// CreateHTree(HTree &HT, int n)——构造赫夫曼树HT，其中n是叶子结点数。要求根据赫夫曼树的构造规则，生成一个由2n-1个结点组成的一棵赫夫曼树。
Status CreateHTree(HTree &HT, int n) {
    if (n <= 1) return ERROR;// 只有一个结点
    int m = 2*n-1;
    for (int i = n; i < m; i++) {// 构造赫夫曼树
        int s1 = -1, s2 = -1;// 两个最小权重结点
        int w1 = 0x7fffffff, w2 = 0x7fffffff;// 两个最小权重
        for (int j = 0; j < i; j++) {
            if (HT[j].parent == -1) {// 未被选中
                if (HT[j].weight < w1) {// 更新最小权重
                    w2 = w1;// 更新第二小权重
                    s2 = s1;// 更新第二小结点
                    w1 = HT[j].weight;// 更新最小权重
                    s1 = j;// 更新最小结点
                } else if (HT[j].weight < w2) {
                    w2 = HT[j].weight;
                    s2 = j;
                }
            }
        }
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    return OK;
}

// HTCoding(HTree HT, HTCode &HC,int n)——生成赫夫曼编码HC，其中n是叶子结点数。要求根据生成的赫夫曼树HT，生成n个叶子结点的赫夫曼编码并输出。
Status HTCoding(HTree HT, HTCode &HC,int n) {
    HC = (HTCode)malloc(n*sizeof(char*));// 分配存储空间
    if (!HC) exit(OVERFLOW);
    char *cd = (char*)malloc(n*sizeof(char));// 分配存储空间
    if (!cd) exit(OVERFLOW);
    cd[n-1] = '\0';// 结束符
    for (int i = 0; i < n; i++) {// 生成赫夫曼编码
        int start = n-1;// 起始位置
        int c = i;// 当前结点
        int f = HT[i].parent;// 父结点
        while (f != -1) {
            --start;
            if (HT[f].lchild == c) {// 左孩子
                cd[start] = '0';
            } else {
                cd[start] = '1';
            }
            c = f;
            f = HT[f].parent;
        }
        HC[i] = (char*)malloc((n-start)*sizeof(char));// 分配存储空间
        if (!HC[i]) exit(OVERFLOW);
        strcpy(HC[i], &cd[start]);// 复制赫夫曼编码
    }
    free(cd);
    return OK;
}


// 读入权重
void ReadWeight(int *w, int n) {
    printf("请输入权重（以,分隔）：\n");
    char input[100];
    // 读入多余的\n
    fgetc(stdin);
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *token;
        char *input_copy = strdup(input); // 复制输入字符串
        token = strtok(input_copy, ",");
        for (int i = 0; i < n; i++) {
            if (token != NULL) {
                w[i] = atoi(token);
                token = strtok(NULL, ",");
            } else {
                printf("输入的权重数量不足。\n");
                free(input_copy);
                exit(ERROR);
            }
        }
        free(input_copy); // 释放复制的字符串
    } else {
        printf("读取输入失败。\n");
        exit(ERROR);
    }
}

int main() {
    // int w[8] = {5, 29, 7, 8, 14, 23, 3, 11};

    // 初始化赫夫曼树
    char input[100]; // 用于存储输入字符串
    int n;
    printf("请输入n: ");
    scanf("%d", &n);
    int w[n];
    ReadWeight(w, n);

    HTree HT;
    HTCode HC;
    InitHTree(HT, w, 8);
    printf("调用InitHTree()函数,HT:\n");
    for (int i = 0; i < 15; i++) {
        printf("%d %d %d %d %d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild, i);
    }
    CreateHTree(HT, 8);
    printf("调用CreateHTree()函数,HT:\n");
    for (int i = 0; i < 15; i++) {
        printf("%d %d %d %d %d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild, i);
    }
    HTCoding(HT, HC, 8);
    printf("调用HTCoding()函数,HC:\n");
    for (int i = 0; i < 8; i++) {
        printf("%s\n", HC[i]);
    }
    return 0;
}

// test data
// 5, 29, 7, 8, 14, 23, 3, 11