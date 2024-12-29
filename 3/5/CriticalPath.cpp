#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define MAX_VERTEX_NUM  20//最大顶点数

typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;  //图的类型
typedef char VertexType; //顶点数据的类型(字符） 
//边(弧)结点数据类型 
typedef struct ArcNode {
       int    adjvex ;       //该边(弧)所依附(指向)的顶点在顶点数组的下标
       struct ArcNode *nextarc;       //指向下一条边(弧)的指针
       int    weight;        //边(弧)的权值，无权图其值为0
}ArcNode;

//顶点数组数据类型 
typedef struct VNode {
       VertexType  data;          //顶点数据 
       ArcNode  *firstarc;         //指向第一条依附该顶点的边(弧)的指针
}VNode, AdjList[MAX_VERTEX_NUM];

//图的邻接表数据类型 
typedef  struct {
       AdjList   vertices;                   //图的顶点数组 
       int       vexnum, arcnum;     //图的顶点数和边(弧)数 
       GraphKind kind;                    //图的类型 
}ALGraph;

// 栈
#define STACK_INIT_SIZE    10
#define STACKINCREMENT  5
typedef int SElemType;  //声明SElemType的类型
typedef struct  { 
        SElemType *base;  //顺序栈数据存储空间基址 
        SElemType *top;    //顺序栈栈顶指针 
        int stacksize;
}SqStack;  // SqStack为用户定义的顺序栈类型

// 利用malloc函数申请存储空间，构造一个空的顺序栈S，S的初始大小为STACK_INIT_SIZE。
Status InitStack(SqStack &S) {
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));// 分配存储空间
    if (!S.base) exit(OVERFLOW);// 存储分配失败
    S.top = S.base;// 栈顶指针指向栈底
    S.stacksize = STACK_INIT_SIZE;// 栈的初始大小
    return OK;
}

// 将数据e进栈。
Status Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {// 栈满，追加存储空间
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) exit(OVERFLOW);// 存储分配失败
        S.top = S.base + S.stacksize;// 栈顶指针指向新的栈顶
        S.stacksize += STACKINCREMENT;// 栈的大小增加
    }
    *S.top++ = e;// 元素e进栈
    return OK;
}

// 将栈顶元素出栈，用e返回其值。
Status Pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) return ERROR;// 栈空
    e = *--S.top;// 栈顶元素出栈
    return OK;
}

//创建图的邻接表存储
Status CreateALGraph(GraphKind GKind, ALGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) {
        int i, j, k, w;
        ArcNode *p;
        G.vexnum = vexnum; //顶点数
        G.arcnum = arcnum; //边数
        G.kind = GKind; //图的类型
        for (i = 0; i < G.vexnum; i++) {
                G.vertices[i].data = vexs[i];
                G.vertices[i].firstarc = NULL;
        }
        if (GKind == DG || GKind == UDG) {// 有向图,无向图
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        p = (ArcNode *)malloc(sizeof(ArcNode));
                        p->adjvex = j;
                        p->nextarc = G.vertices[i].firstarc;
                        G.vertices[i].firstarc = p;
                        if (GKind == UDG) {// 无向图
                                p = (ArcNode *)malloc(sizeof(ArcNode));
                                p->adjvex = i;
                                p->nextarc = G.vertices[j].firstarc;
                                G.vertices[j].firstarc = p;
                        }
                }
        } else if (GKind == DN || GKind == UDN) {// 带权有向图,带权无向图
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        w = arcs[k * 3 + 2];
                        p = (ArcNode *)malloc(sizeof(ArcNode));
                        p->adjvex = j;
                        p->weight = w;
                        p->nextarc = G.vertices[i].firstarc;
                        G.vertices[i].firstarc = p;
                        if (GKind == UDN) {// 带权无向图
                                p = (ArcNode *)malloc(sizeof(ArcNode));
                                p->adjvex = i;
                                p->weight = w;
                                p->nextarc = G.vertices[j].firstarc;
                                G.vertices[j].firstarc = p;
                        }
                     }
              }
              return OK;
}


//输出图的邻接表存储
Status OutALGraph(ALGraph G) {
        int i;
        ArcNode *p;
        printf("图的顶点数组元素：");
        for (i = 0; i < G.vexnum; i++) {
                printf("%c ", G.vertices[i].data);
        }
        printf("\n");
        printf("图的邻接表：\n");
        for (i = 0; i < G.vexnum; i++) {
                printf("%c->", G.vertices[i].data);
                p = G.vertices[i].firstarc;
                while (p != NULL) {
                        if (G.kind == DN || G.kind == UDN) {// 带权有向图,带权无向图
                                printf("%c(%d)->", G.vertices[p->adjvex].data, p->weight);
                        } else {
                                printf("%c->", G.vertices[p->adjvex].data);
                        }
                        p = p->nextarc;
                }
                printf("∧\n");
        }
        return OK;
}

/*
设一个有向网如下图所示，现要求利用C/C++语言编写一个程序，求解该有向网从源点A到终点J的关键路径。
*/

// 计算各顶点的入度，保存在inDegree数组中
Status FindInDegree(ALGraph G, int *inDegree) {
    int i;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++) {//初始化
            inDegree[i] = 0;
    }
    for (i = 0; i < G.vexnum; i++) {
            p = G.vertices[i].firstarc;
            while (p != NULL) {
                    inDegree[p->adjvex]++;
                    p = p->nextarc;
            }
    }
    return OK;
}

// 全局变量
int *ve;
int *vl;

Status TopologicalSort(ALGraph G, SqStack &T) {
    int i, j, k, e, dut;
    int *inDegree = (int *)malloc(G.vexnum * sizeof(int));
    FindInDegree(G, inDegree);//计算各顶点的入度
    SqStack S;
    InitStack(S);// 初始化栈
    for (i = 0; i < G.vexnum; i++) {
            if (inDegree[i] == 0) {
                    Push(S, i);// 入度为0的顶点进栈
            }
    }
    int count = 0;
    InitStack(T);// 初始化拓扑有序的顶点栈
    // 全局变量ve[]
    ve = (int *)malloc(G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum; i++) {
            ve[i] = 0;
    }
    while (S.top != S.base) {
        Pop(S, e);// 出栈
        Push(T, e);// 入栈
        printf("%c ", G.vertices[e].data);// 输出
        count++;
        ArcNode *p = G.vertices[e].firstarc;
        while (p != NULL) {
                j = p->adjvex;
                inDegree[j]--;
                if (inDegree[j] == 0) {
                        Push(S, j);// 入度为0的顶点进栈
                }
                dut = p->weight;
                if (ve[e] + dut > ve[j]) {// 计算顶点j的最早发生时间
                        ve[j] = ve[e] + dut;
                }
                p = p->nextarc;
        }
    }
    if (count < G.vexnum) {
            printf("图中有回路\n");
            return ERROR;
    }else{
            printf("\n");
            return OK;
    }
}

// 关键路径算法
Status CriticalPath(ALGraph G) {
    SqStack T;
    if (TopologicalSort(G, T) == ERROR) return ERROR;
    // 全局变量vl[]
    vl = (int *)malloc(G.vexnum * sizeof(int));
    for (int i = 0; i < G.vexnum; i++) {
            vl[i] = ve[G.vexnum - 1];
    }
    int i, j, k, dut;
    ArcNode *p;
    while (T.top != T.base) {
        Pop(T, i);// 出栈
        p = G.vertices[i].firstarc;
        while (p != NULL) {
                j = p->adjvex;
                dut = p->weight;
                if (vl[j] - dut < vl[i]) {// 计算顶点j的最晚发生时间
                        vl[i] = vl[j] - dut;
                }
                p = p->nextarc;
        }
    }
    printf("关键路径为：\n");
    for (i = 0; i < G.vexnum; i++) {
            p = G.vertices[i].firstarc;
            while (p != NULL) {
                    j = p->adjvex;
                    dut = p->weight;
                    int ee = ve[i];
                    int el = vl[j] - dut;
                    if (ee == el) {
                            printf("%c->%c ", G.vertices[i].data, G.vertices[j].data);
                    }
                    p = p->nextarc;
            }
    }
    printf("\n");
    return OK;
}

int main(){
    ALGraph G;
    int vexnum, arcnum;
    char vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][3];
    // 有向网
    printf("有向网\n");
    vexnum = 10;
    arcnum = 15;
    char vexs1[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int arcs1[15][3] = {{0, 1, 8}, {0, 2, 6}, {0, 4, 7}, {1, 3, 3}, {2, 3, 10}, {2, 6, 9}, {3, 5, 4}, {3, 8, 19}, {4, 6, 9}, {4, 7, 13}, {5, 9, 14}, {6, 7, 2}, {6, 8, 8}, {7, 8, 6}, {8, 9, 10}};
    CreateALGraph(DN, G, vexnum, arcnum, vexs1, (int *)arcs1);
    OutALGraph(G);
    CriticalPath(G);
    return 0;
}