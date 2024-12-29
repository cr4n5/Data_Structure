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
2. 图的邻接表存储与基本操作的实现
利用实验3-2的CreateALGraph()函数和OutALGraph()函数实现图的邻接表存储与输出操作。

3. 图的遍历操作的实现
（1）编写一个图的深度优先遍历函数DFSTraverse(ALGraph G)，输出各顶点的遍历序列。建议采用递归方式实现。
（2）编写一个图的广度优先遍历函数BFSTraverse(ALGraph G)，输出各顶点的遍历序列。建议采用非递归方式实现。

4. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）调用CreateALGraph()函数生成以下图的邻接表存储结构：
（2）调用OutALGraph()函数输出上图的邻接表存储数据。
（3）调用深度优先遍历函数DFSTraverse()，输出各顶点的遍历序列。
（4）调用广度优先遍历函数BFSTraverse()，输出各顶点的遍历序列。
*/

//深度优先遍历
bool visited[MAX_VERTEX_NUM];
Status DFS(ALGraph G, int v) {
        ArcNode *p;
        visited[v] = TRUE;
        printf("%c ", G.vertices[v].data);
        p = G.vertices[v].firstarc;
        while (p != NULL) {
                if (!visited[p->adjvex]) {
                        DFS(G, p->adjvex);// 优先向下搜索
                }
                p = p->nextarc;
        }
        return OK;
}

Status DFSTraverse(ALGraph G) {
        int i;
        for (i = 0; i < G.vexnum; i++) {
                visited[i] = FALSE;
        }
        for (i = 0; i < G.vexnum; i++) {
                if (!visited[i]) {
                        DFS(G, i);
                }
        }
        printf("\n");
        return OK;
}

//广度优先遍历
typedef struct {
        int data[MAX_VERTEX_NUM];
        int front, rear;
}Queue;

Status InitQueue(Queue &Q) {
        Q.front = Q.rear = 0;
        return OK;
}

Status EnQueue(Queue &Q, int e) {
        Q.data[Q.rear] = e;
        Q.rear = (Q.rear + 1) % MAX_VERTEX_NUM;
        return OK;
}

Status DeQueue(Queue &Q, int &e) {
        e = Q.data[Q.front];
        Q.front = (Q.front + 1) % MAX_VERTEX_NUM;
        return OK;
}

Status BFSTraverse(ALGraph G) {
        int i, j;
        ArcNode *p;
        Queue Q;
        InitQueue(Q);
        for (i = 0; i < G.vexnum; i++) {
                visited[i] = FALSE;
        }
        for (i = 0; i < G.vexnum; i++) {
                if (!visited[i]) {
                        visited[i] = TRUE;
                        printf("%c ", G.vertices[i].data);
                        EnQueue(Q, i);
                        while (Q.front != Q.rear) {
                                DeQueue(Q, j);// 进行出队，然后访问该顶点的所有邻接点
                                p = G.vertices[j].firstarc;
                                while (p != NULL) {
                                        if (!visited[p->adjvex]) {
                                                visited[p->adjvex] = TRUE;
                                                printf("%c ", G.vertices[p->adjvex].data);
                                                EnQueue(Q, p->adjvex);// 将该顶点的所有邻接点入队
                                        }
                                        p = p->nextarc;
                                }
                        }
                }
        }
        printf("\n");
        return OK;
}

int main() {
        ALGraph G;
        char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
        int arcs[7][3] = {{0, 1, 1}, {0, 2, 1}, {1, 3, 1}, {1, 4, 1}, {2, 5, 1}, {3, 4, 1}, {4, 5, 1}};
        CreateALGraph(UDG, G, 6, 7, vexs, (int *)arcs);
        OutALGraph(G);
        DFSTraverse(G);
        BFSTraverse(G);
        return 0;
}
