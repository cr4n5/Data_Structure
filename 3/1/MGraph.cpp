#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define INFINITY 32767                   //表示最大值∞
#define MAX_VERTEX_NUM  20       //最大顶点数
typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;  //图的枚举类型
typedef int VRType;
typedef char InfoType;  
typedef struct ArcCell { 
        VRType adj  ;          //对无权图用1或0表示；对带权图，则为权值类型。
        InfoType *info;       //该边或弧相关信息的指针（字符串） 
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef char VertexType;
typedef struct{
        VertexType vexs[MAX_VERTEX_NUM];   //顶点数组，存放顶点信息
        AdjMatrix   arcs;                  //邻接矩阵
        int vexnum, arcnum;           //图中顶点总数与弧数
        GraphKind  kind;                 //图的种类标志
} MGraph;      


/*
2. 图的邻接矩阵存储与基本操作的实现
根据定义的存储结构，编写下列基本操作函数的C/C++源代码：

（1）编写一个能够创建4种不同类型图的邻接矩阵存储的通用函数，函数格式如下：
CreateMGraph(GraphKind GKind, MGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) 
函数参数说明如下： 
GraphKind GKind: 图的类型 DG,DN,UDG,UDN
MGraph G: 图变量，存放图的顶点数组、邻接矩阵等数据 
int vexnum: 图的顶点数
int arcnum: 图的边或弧数
char *vexs: 顶点数组，存放图的顶点 
int *arcs:  边(弧)数组，每条边（弧）采用三元组形式存放(i, j, w)，分别表示边的邻接顶点和权值或弧的弧尾、弧头和权值，对于无权值的图，权值=1。该参数的实参用二维数组存储，形参用一维数组的形式访问。
在实现时要注意无向图（网）是对称矩阵，有向图（网）是非对称矩阵。

（2）编写一个函数OutMGraph(MGraph G)，输出图G的顶点数组元素和邻接矩阵，对于无权图，元素用1和0表示，对于有权图（网），边的权值正整数表示，其他用∞表示。

（3）编写一个函数VerDegree(MGraph G)，输出图G中各顶点的度（有向图分入度和出度）。

3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）分别调用CreateMGraph()函数生成以下4个图的邻接矩阵存储结构：
（2）分别调用OutMGraph()函数输出以上4个图的邻接矩阵存储的数据。
（3）分别调用VerDegree()函数输出以上4个图的各顶点的度。
*/

//创建图的邻接矩阵存储
Status CreateMGraph(GraphKind GKind, MGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) {
        int i, j, k, w;
        G.vexnum = vexnum; //顶点数
        G.arcnum = arcnum; //边数
        G.kind = GKind; //图的类型
        for (i = 0; i < G.vexnum; i++) {
                G.vexs[i] = vexs[i];
        }
        for (i = 0; i < G.vexnum; i++) {
                for (j = 0; j < G.vexnum; j++) {
                        G.arcs[i][j].adj = INFINITY;
                }
        }
        if (GKind == DG || GKind == UDG) {// 有向图,无向图
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        G.arcs[i][j].adj = 1;
                        if (GKind == UDG) {// 无向图
                                G.arcs[j][i].adj = 1;
                        }
                }
        } else if (GKind == DN || GKind == UDN) {// 带权有向图,带权无向图
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        w = arcs[k * 3 + 2];
                        G.arcs[i][j].adj = w;
                        if (GKind == UDN) {// 带权无向图
                                G.arcs[j][i].adj = w;
                        }
                }
        }
        return OK;
}

//输出图的邻接矩阵存储
Status OutMGraph(MGraph G) {
        int i, j;
        printf("图的顶点数组元素：");
        for (i = 0; i < G.vexnum; i++) {
                printf("%c ", G.vexs[i]);
        }
        printf("\n");
        printf("图的邻接矩阵：\n");
        for (i = 0; i < G.vexnum; i++) {
                for (j = 0; j < G.vexnum; j++) {
                        if (G.arcs[i][j].adj == INFINITY) {
                                printf("∞ ");
                        } else {
                                printf("%d ", G.arcs[i][j].adj);
                        }
                }
                printf("\n");
        }
        return OK;
}

//输出图中各顶点的度
Status VerDegree(MGraph G) {
        int i, j, inDegree, outDegree;
        for (i = 0; i < G.vexnum; i++) {
                inDegree = 0;
                outDegree = 0;
                for (j = 0; j < G.vexnum; j++) {
                        if (G.arcs[j][i].adj != INFINITY) {
                                inDegree++;
                        }
                        if (G.arcs[i][j].adj != INFINITY) {
                                outDegree++;
                        }
                }
                printf("顶点%c的入度为%d，出度为%d\n", G.vexs[i], inDegree, outDegree);
        }
        return OK;
}

int main() {
        MGraph G;
        int vexnum, arcnum;
        char vexs[MAX_VERTEX_NUM];
        int arcs[MAX_VERTEX_NUM][3];
        // 无向图
        printf("无向图\n");
        vexnum = 4;
        arcnum = 5;
        char vexs1[4] = {'A', 'B', 'C', 'D'};
        int arcs1[5][3] = {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}, {1, 2, 1}, {2, 3, 1}};
        CreateMGraph(UDG, G, vexnum, arcnum, vexs1, (int *)arcs1);
        OutMGraph(G);
        VerDegree(G);
        printf("\n");
        // 有向图
        printf("有向图\n");
        vexnum = 4;
        arcnum = 6;
        char vexs2[4] = {'A', 'B', 'C', 'D'};
        int arcs2[6][3] = {{0, 1, 1}, {1, 0, 1}, {1, 2, 1}, {2, 0, 1}, {2, 1, 1}, {3, 1, 1}};
        CreateMGraph(DG, G, vexnum, arcnum, vexs2, (int *)arcs2);
        OutMGraph(G);
        VerDegree(G);
        printf("\n");
        // 带权无向图
        printf("带权无向图\n");
        vexnum = 4;
        arcnum = 4;
        char vexs3[4] = {'A', 'B', 'C', 'D'};
        int arcs3[4][3] = {{0, 1, 56}, {0, 2,34}, {0, 3, 78}, {2, 3, 25}};
        CreateMGraph(UDN, G, vexnum, arcnum, vexs3, (int *)arcs3);
        OutMGraph(G);
        VerDegree(G);
        printf("\n");
        // 带权有向图
        printf("带权有向图\n");
        vexnum = 3;
        arcnum = 3;
        char vexs4[3] = {'A', 'B', 'C'};
        int arcs4[3][3] = {{0, 2, 50}, {1, 2, 45}, {2, 0, 64}};
        CreateMGraph(DN, G, vexnum, arcnum, vexs4, (int *)arcs4);
        OutMGraph(G);
        VerDegree(G);
        return 0;
}