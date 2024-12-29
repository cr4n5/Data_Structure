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


/*
2. ͼ���ڽӾ���洢�����������ʵ��
���ݶ���Ĵ洢�ṹ����д���л�������������C/C++Դ���룺

��1����дһ���ܹ�����4�ֲ�ͬ����ͼ���ڽӾ���洢��ͨ�ú�����������ʽ���£�
CreateMGraph(GraphKind GKind, MGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) 
��������˵�����£� 
GraphKind GKind: ͼ������ DG,DN,UDG,UDN
MGraph G: ͼ���������ͼ�Ķ������顢�ڽӾ�������� 
int vexnum: ͼ�Ķ�����
int arcnum: ͼ�ı߻���
char *vexs: �������飬���ͼ�Ķ��� 
int *arcs:  ��(��)���飬ÿ���ߣ�����������Ԫ����ʽ���(i, j, w)���ֱ��ʾ�ߵ��ڽӶ����Ȩֵ�򻡵Ļ�β����ͷ��Ȩֵ��������Ȩֵ��ͼ��Ȩֵ=1���ò�����ʵ���ö�ά����洢���β���һά�������ʽ���ʡ�
��ʵ��ʱҪע������ͼ�������ǶԳƾ�������ͼ�������ǷǶԳƾ���

��2����дһ������OutMGraph(MGraph G)�����ͼG�Ķ�������Ԫ�غ��ڽӾ��󣬶�����Ȩͼ��Ԫ����1��0��ʾ��������Ȩͼ���������ߵ�Ȩֵ��������ʾ�������áޱ�ʾ��

��3����дһ������VerDegree(MGraph G)�����ͼG�и�����Ķȣ�����ͼ����Ⱥͳ��ȣ���

3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1���ֱ����CreateMGraph()������������4��ͼ���ڽӾ���洢�ṹ��
��2���ֱ����OutMGraph()�����������4��ͼ���ڽӾ���洢�����ݡ�
��3���ֱ����VerDegree()�����������4��ͼ�ĸ�����Ķȡ�
*/

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

//���ͼ�и�����Ķ�
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
                printf("����%c�����Ϊ%d������Ϊ%d\n", G.vexs[i], inDegree, outDegree);
        }
        return OK;
}

int main() {
        MGraph G;
        int vexnum, arcnum;
        char vexs[MAX_VERTEX_NUM];
        int arcs[MAX_VERTEX_NUM][3];
        // ����ͼ
        printf("����ͼ\n");
        vexnum = 4;
        arcnum = 5;
        char vexs1[4] = {'A', 'B', 'C', 'D'};
        int arcs1[5][3] = {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}, {1, 2, 1}, {2, 3, 1}};
        CreateMGraph(UDG, G, vexnum, arcnum, vexs1, (int *)arcs1);
        OutMGraph(G);
        VerDegree(G);
        printf("\n");
        // ����ͼ
        printf("����ͼ\n");
        vexnum = 4;
        arcnum = 6;
        char vexs2[4] = {'A', 'B', 'C', 'D'};
        int arcs2[6][3] = {{0, 1, 1}, {1, 0, 1}, {1, 2, 1}, {2, 0, 1}, {2, 1, 1}, {3, 1, 1}};
        CreateMGraph(DG, G, vexnum, arcnum, vexs2, (int *)arcs2);
        OutMGraph(G);
        VerDegree(G);
        printf("\n");
        // ��Ȩ����ͼ
        printf("��Ȩ����ͼ\n");
        vexnum = 4;
        arcnum = 4;
        char vexs3[4] = {'A', 'B', 'C', 'D'};
        int arcs3[4][3] = {{0, 1, 56}, {0, 2,34}, {0, 3, 78}, {2, 3, 25}};
        CreateMGraph(UDN, G, vexnum, arcnum, vexs3, (int *)arcs3);
        OutMGraph(G);
        VerDegree(G);
        printf("\n");
        // ��Ȩ����ͼ
        printf("��Ȩ����ͼ\n");
        vexnum = 3;
        arcnum = 3;
        char vexs4[3] = {'A', 'B', 'C'};
        int arcs4[3][3] = {{0, 2, 50}, {1, 2, 45}, {2, 0, 64}};
        CreateMGraph(DN, G, vexnum, arcnum, vexs4, (int *)arcs4);
        OutMGraph(G);
        VerDegree(G);
        return 0;
}