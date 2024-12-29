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

/*
3. 最小生成树的求解操作
（1）编写一个实现Prim算法的函数MiniSpanTree_Prim(MGraph G, VertexType u)，其中参数u是图中任一个顶点元素。要求输出每一条最小生成边（例如：（A,B,10））和辅助数组closedge[]的变化过程。
（2）编写一个实现Kruskal算法的函数MiniSpanTree_Kruskal(MGraph G)，要求输出排序后的edge数组，然后输出每一条最小生成边和连通分量数组cnvx[]的变化过程。

4. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）调用CreateMGraph()函数生成以下图的邻接矩阵存储结构：
（2）调用OutMGraph()函数输出上图的邻接矩阵存储数据。
（3）调用MiniSpanTree_Prim()函数，输出上图的最小生成树。
（3）调用MiniSpanTree_Kruskal()函数，输出上图的最小生成树。

*/

//最小生成树的Prim算法
Status MiniSpanTree_Prim(MGraph G, int u) {//u是图中任一个顶点元素下标
    struct {
        VertexType adjvex; //顶点元素
        VRType lowcost;
    }closedge[MAX_VERTEX_NUM];
    int i, j, k, min;
    k = u;
    for (i = 0; i < G.vexnum; i++) {
        closedge[i].lowcost = INFINITY;
        closedge[i].adjvex = G.vexs[u];
    }
    closedge[u].lowcost = 0;
    // 输出辅助数组closedge[]的变化过程
    printf("closedge[]数组的变化过程：");
    for (i = 0; i < G.vexnum; i++) {
        printf("(%c,%d) ", closedge[i].adjvex, closedge[i].lowcost);
    }
    printf("\n");
    for (i = 0; i < G.vexnum; i++) {
        min = INFINITY;
        for (j = 0; j < G.vexnum; j++) {
            if (closedge[j].lowcost != 0 && closedge[j].lowcost < min) {// 选择最小权值边
                min = closedge[j].lowcost;
                k = j;
            }
        }
        printf("最小生成边：");
        printf("(%c,%c,%d)\n", closedge[k].adjvex, G.vexs[k], closedge[k].lowcost);
        closedge[k].lowcost = 0;
        for (j = 0; j < G.vexnum; j++) { //更新closedge数组
            if (G.arcs[k][j].adj < closedge[j].lowcost) {
                closedge[j].lowcost = G.arcs[k][j].adj;
                closedge[j].adjvex = G.vexs[k];
            }
        }
        printf("closedge[]数组的变化过程：");
        for (j = 0; j < G.vexnum; j++) {
            printf("(%c,%d) ", closedge[j].adjvex, closedge[j].lowcost);
        }
        printf("\n");
    }
    return OK;
}

// 最小生成树的Kruskal算法
Status MiniSpanTree_Kruskal(MGraph G) {
    struct Edge {
        int begin;
        int end;
        int weight;
    }edge[MAX_VERTEX_NUM];//边集数组
    int i, j, k, n, m;
    m = 0;
    for (i = 0; i < G.vexnum; i++) {//初始化
        for (j = 0; j < G.vexnum; j++) {
            if (G.arcs[i][j].adj != INFINITY) {
                edge[m].begin = i;
                edge[m].end = j;
                edge[m].weight = G.arcs[i][j].adj;
                m++;
            }
        }
    }
    Edge temp;
    for (i = 0; i < m - 1; i++) {//按权值递增排序
        for (j = i + 1; j < m; j++) {
            if (edge[i].weight > edge[j].weight) {
                temp = edge[i];
                edge[i] = edge[j];
                edge[j] = temp;
            }
        }
    }
    int cnvx[MAX_VERTEX_NUM];//连通分量数组
    for (i = 0; i < G.vexnum; i++) {//初始化连通分量数组
        cnvx[i] = i;
    }
    printf("cnvx[]数组的变化过程：");
    for (i = 0; i < G.vexnum; i++) {
        printf("%d ", cnvx[i]);
    }
    printf("\n");
    for (i = 0; i < m; i++) {
        n = cnvx[edge[i].begin];
        k = cnvx[edge[i].end];
        if (n != k) {//不在同一连通分量中
            printf("最小生成边：");
            printf("(%c,%c,%d)\n", G.vexs[edge[i].begin], G.vexs[edge[i].end], edge[i].weight);
            for (j = 0; j < G.vexnum; j++) {
                if (cnvx[j] == k) {//同一连通分量
                    cnvx[j] = n;//合并连通分量
                }
            }
            printf("cnvx[]数组的变化过程：");
            for (j = 0; j < G.vexnum; j++) {
                printf("%d ", cnvx[j]);
            }
            printf("\n");
        }
    }
    return OK;
}

int main() {
    MGraph G;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int arcs[10][3] = {{0, 1, 10}, {0, 2, 12}, {0, 4, 15}, {1, 2, 7}, {1, 3, 5}, {1, 5, 6}, {2, 4, 12}, {2, 5, 8}, {3, 5, 6}, {4, 5, 10}};
    CreateMGraph(UDN, G, 6, 7, vexs, (int *)arcs);
    OutMGraph(G);
    printf("\nPrim算法\n");
    MiniSpanTree_Prim(G, 0);
    printf("\nKruskal算法\n");
    MiniSpanTree_Kruskal(G);
    return 0;
}
