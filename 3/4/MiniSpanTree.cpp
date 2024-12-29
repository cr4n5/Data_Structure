#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define INFINITY 32767                   //��ʾ���ֵ��
#define MAX_VERTEX_NUM  20       //��󶥵���
typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;  //ͼ��ö������
typedef int VRType;
typedef char InfoType;  
typedef struct ArcCell { 
        VRType adj  ;          //����Ȩͼ��1��0��ʾ���Դ�Ȩͼ����ΪȨֵ���͡�
        InfoType *info;       //�ñ߻������Ϣ��ָ�루�ַ����� 
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef char VertexType;
typedef struct{
        VertexType vexs[MAX_VERTEX_NUM];   //�������飬��Ŷ�����Ϣ
        AdjMatrix   arcs;                  //�ڽӾ���
        int vexnum, arcnum;           //ͼ�ж��������뻡��
        GraphKind  kind;                 //ͼ�������־
} MGraph;     

//����ͼ���ڽӾ���洢
Status CreateMGraph(GraphKind GKind, MGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) {
        int i, j, k, w;
        G.vexnum = vexnum; //������
        G.arcnum = arcnum; //����
        G.kind = GKind; //ͼ������
        for (i = 0; i < G.vexnum; i++) {
                G.vexs[i] = vexs[i];
        }
        for (i = 0; i < G.vexnum; i++) {
                for (j = 0; j < G.vexnum; j++) {
                        G.arcs[i][j].adj = INFINITY;
                }
        }
        if (GKind == DG || GKind == UDG) {// ����ͼ,����ͼ
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        G.arcs[i][j].adj = 1;
                        if (GKind == UDG) {// ����ͼ
                                G.arcs[j][i].adj = 1;
                        }
                }
        } else if (GKind == DN || GKind == UDN) {// ��Ȩ����ͼ,��Ȩ����ͼ
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        w = arcs[k * 3 + 2];
                        G.arcs[i][j].adj = w;
                        if (GKind == UDN) {// ��Ȩ����ͼ
                                G.arcs[j][i].adj = w;
                        }
                }
        }
        return OK;
}

//���ͼ���ڽӾ���洢
Status OutMGraph(MGraph G) {
        int i, j;
        printf("ͼ�Ķ�������Ԫ�أ�");
        for (i = 0; i < G.vexnum; i++) {
                printf("%c ", G.vexs[i]);
        }
        printf("\n");
        printf("ͼ���ڽӾ���\n");
        for (i = 0; i < G.vexnum; i++) {
                for (j = 0; j < G.vexnum; j++) {
                        if (G.arcs[i][j].adj == INFINITY) {
                                printf("�� ");
                        } else {
                                printf("%d ", G.arcs[i][j].adj);
                        }
                }
                printf("\n");
        }
        return OK;
}

/*
3. ��С��������������
��1����дһ��ʵ��Prim�㷨�ĺ���MiniSpanTree_Prim(MGraph G, VertexType u)�����в���u��ͼ����һ������Ԫ�ء�Ҫ�����ÿһ����С���ɱߣ����磺��A,B,10�����͸�������closedge[]�ı仯���̡�
��2����дһ��ʵ��Kruskal�㷨�ĺ���MiniSpanTree_Kruskal(MGraph G)��Ҫ�����������edge���飬Ȼ�����ÿһ����С���ɱߺ���ͨ��������cnvx[]�ı仯���̡�

4. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1������CreateMGraph()������������ͼ���ڽӾ���洢�ṹ��
��2������OutMGraph()���������ͼ���ڽӾ���洢���ݡ�
��3������MiniSpanTree_Prim()�����������ͼ����С��������
��3������MiniSpanTree_Kruskal()�����������ͼ����С��������

*/

//��С��������Prim�㷨
Status MiniSpanTree_Prim(MGraph G, int u) {//u��ͼ����һ������Ԫ���±�
    struct {
        VertexType adjvex; //����Ԫ��
        VRType lowcost;
    }closedge[MAX_VERTEX_NUM];
    int i, j, k, min;
    k = u;
    for (i = 0; i < G.vexnum; i++) {
        closedge[i].lowcost = INFINITY;
        closedge[i].adjvex = G.vexs[u];
    }
    closedge[u].lowcost = 0;
    // �����������closedge[]�ı仯����
    printf("closedge[]����ı仯���̣�");
    for (i = 0; i < G.vexnum; i++) {
        printf("(%c,%d) ", closedge[i].adjvex, closedge[i].lowcost);
    }
    printf("\n");
    for (i = 0; i < G.vexnum; i++) {
        min = INFINITY;
        for (j = 0; j < G.vexnum; j++) {
            if (closedge[j].lowcost != 0 && closedge[j].lowcost < min) {// ѡ����СȨֵ��
                min = closedge[j].lowcost;
                k = j;
            }
        }
        printf("��С���ɱߣ�");
        printf("(%c,%c,%d)\n", closedge[k].adjvex, G.vexs[k], closedge[k].lowcost);
        closedge[k].lowcost = 0;
        for (j = 0; j < G.vexnum; j++) { //����closedge����
            if (G.arcs[k][j].adj < closedge[j].lowcost) {
                closedge[j].lowcost = G.arcs[k][j].adj;
                closedge[j].adjvex = G.vexs[k];
            }
        }
        printf("closedge[]����ı仯���̣�");
        for (j = 0; j < G.vexnum; j++) {
            printf("(%c,%d) ", closedge[j].adjvex, closedge[j].lowcost);
        }
        printf("\n");
    }
    return OK;
}

// ��С��������Kruskal�㷨
Status MiniSpanTree_Kruskal(MGraph G) {
    struct Edge {
        int begin;
        int end;
        int weight;
    }edge[MAX_VERTEX_NUM];//�߼�����
    int i, j, k, n, m;
    m = 0;
    for (i = 0; i < G.vexnum; i++) {//��ʼ��
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
    for (i = 0; i < m - 1; i++) {//��Ȩֵ��������
        for (j = i + 1; j < m; j++) {
            if (edge[i].weight > edge[j].weight) {
                temp = edge[i];
                edge[i] = edge[j];
                edge[j] = temp;
            }
        }
    }
    int cnvx[MAX_VERTEX_NUM];//��ͨ��������
    for (i = 0; i < G.vexnum; i++) {//��ʼ����ͨ��������
        cnvx[i] = i;
    }
    printf("cnvx[]����ı仯���̣�");
    for (i = 0; i < G.vexnum; i++) {
        printf("%d ", cnvx[i]);
    }
    printf("\n");
    for (i = 0; i < m; i++) {
        n = cnvx[edge[i].begin];
        k = cnvx[edge[i].end];
        if (n != k) {//����ͬһ��ͨ������
            printf("��С���ɱߣ�");
            printf("(%c,%c,%d)\n", G.vexs[edge[i].begin], G.vexs[edge[i].end], edge[i].weight);
            for (j = 0; j < G.vexnum; j++) {
                if (cnvx[j] == k) {//ͬһ��ͨ����
                    cnvx[j] = n;//�ϲ���ͨ����
                }
            }
            printf("cnvx[]����ı仯���̣�");
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
    printf("\nPrim�㷨\n");
    MiniSpanTree_Prim(G, 0);
    printf("\nKruskal�㷨\n");
    MiniSpanTree_Kruskal(G);
    return 0;
}
