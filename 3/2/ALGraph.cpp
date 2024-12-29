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

/*
2. 图的邻接表存储与基本操作的实现
根据定义的存储结构，编写下列基本操作函数的C/C++源代码：

（1）编写一个能够创建4种不同类型图的邻接表存储的通用函数，函数格式如下：
CreateALGraph(GraphKind GKind, ALGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) 
函数参数说明如下： 
GraphKind GKind: 图的类型 DG,DN,UDG,UDN
MGraph G: 图变量，存放图的顶点数组、邻接边（弧）等数据 
int vexnum: 图的顶点数
int arcnum: 图的边或弧数
char *vexs: 顶点数组，存放图的顶点 
int *arcs:  边(弧)数组，每条边（弧）采用三元组形式存放(i, j, w)，分别表示边的邻接顶点和权值或弧的弧尾、弧头和权值，对于无权值的图，权值=1。该参数的实参用二维数组存储，形参用一维数组的形式访问。
在实现时要注意无向图（网）每条边要产生两个边结点，而有向图（网）是出边表。
（2）编写一个函数OutALGraph(ALGraph G)，输出图G的顶点数组元素和邻接表结构数据，对于有权图（网），权值加括号表示。
（3）编写一个函数VerDegree(ALGraph G)，输出图G中各顶点的度（有向图分入度和出度）。

3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）分别调用CreateALGraph()函数生成以下4个图的邻接表存储结构：
（2）分别调用OutALGraph()函数输出以上4个图的邻接表存储的数据。
（3）分别调用VerDegree()函数输出以上4个图的各顶点的度。
*/

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

//输出图中各顶点的度
Status VerDegree(ALGraph G) {
        int i, j, inDegree, outDegree;
        ArcNode *p;
        for (i = 0; i < G.vexnum; i++) {
                inDegree = 0;
                outDegree = 0;
                for (j = 0; j < G.vexnum; j++) {// 遍历所有弧
                        p = G.vertices[j].firstarc;
                        while (p != NULL) {
                                if (j == i) {
                                        outDegree++;
                                }
                                if (p->adjvex == i) {
                                        inDegree++;
                                }
                                p = p->nextarc;
                        }
                }
                printf("顶点%c的入度为%d，出度为%d\n", G.vertices[i].data, inDegree, outDegree);
        }
        return OK;
}

int main() {
       ALGraph G;
       int vexnum, arcnum;
       char vexs[MAX_VERTEX_NUM];
       int arcs[MAX_VERTEX_NUM][3];
       // 无向图
       printf("无向图\n");
       vexnum = 4;
       arcnum = 5;
        char vexs1[4] = {'A', 'B', 'C', 'D'};
        int arcs1[5][3] = {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}, {1, 2, 1}, {2, 3, 1}};
       CreateALGraph(UDG, G, vexnum, arcnum, vexs1, (int *)arcs1);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       // 有向图
       printf("有向图\n");
       vexnum = 4;
       arcnum = 6;
        char vexs2[4] = {'A', 'B', 'C', 'D'};
        int arcs2[6][3] = {{0, 1, 1}, {1, 0, 1}, {1, 2, 1}, {2, 0, 1}, {2, 1, 1}, {3, 1, 1}};
       CreateALGraph(DG, G, vexnum, arcnum, vexs2, (int *)arcs2);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       // 带权无向图
       printf("带权无向图\n");
       vexnum = 4;
       arcnum = 4;
        char vexs3[4] = {'A', 'B', 'C', 'D'};
        int arcs3[4][3] = {{0, 1, 56}, {0, 2,34}, {0, 3, 78}, {2, 3, 25}};
       CreateALGraph(UDN, G, vexnum, arcnum, vexs3, (int *)arcs3);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       // 带权有向图
       printf("带权有向图\n");
       vexnum = 3;
       arcnum = 3;
        char vexs4[3] = {'A', 'B', 'C'};
        int arcs4[3][3] = {{0, 2, 50}, {1, 2, 45}, {2, 0, 64}};
       CreateALGraph(DN, G, vexnum, arcnum, vexs4, (int *)arcs4);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       return 0;
}