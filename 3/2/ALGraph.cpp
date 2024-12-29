#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define MAX_VERTEX_NUM  20//��󶥵���

typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;  //ͼ������
typedef char VertexType; //�������ݵ�����(�ַ��� 
//��(��)����������� 
typedef struct ArcNode {
       int    adjvex ;       //�ñ�(��)������(ָ��)�Ķ����ڶ���������±�
       struct ArcNode *nextarc;       //ָ����һ����(��)��ָ��
       int    weight;        //��(��)��Ȩֵ����Ȩͼ��ֵΪ0
}ArcNode;

//���������������� 
typedef struct VNode {
       VertexType  data;          //�������� 
       ArcNode  *firstarc;         //ָ���һ�������ö���ı�(��)��ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

//ͼ���ڽӱ��������� 
typedef  struct {
       AdjList   vertices;                   //ͼ�Ķ������� 
       int       vexnum, arcnum;     //ͼ�Ķ������ͱ�(��)�� 
       GraphKind kind;                    //ͼ������ 
}ALGraph;

/*
2. ͼ���ڽӱ�洢�����������ʵ��
���ݶ���Ĵ洢�ṹ����д���л�������������C/C++Դ���룺

��1����дһ���ܹ�����4�ֲ�ͬ����ͼ���ڽӱ�洢��ͨ�ú�����������ʽ���£�
CreateALGraph(GraphKind GKind, ALGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) 
��������˵�����£� 
GraphKind GKind: ͼ������ DG,DN,UDG,UDN
MGraph G: ͼ���������ͼ�Ķ������顢�ڽӱߣ����������� 
int vexnum: ͼ�Ķ�����
int arcnum: ͼ�ı߻���
char *vexs: �������飬���ͼ�Ķ��� 
int *arcs:  ��(��)���飬ÿ���ߣ�����������Ԫ����ʽ���(i, j, w)���ֱ��ʾ�ߵ��ڽӶ����Ȩֵ�򻡵Ļ�β����ͷ��Ȩֵ��������Ȩֵ��ͼ��Ȩֵ=1���ò�����ʵ���ö�ά����洢���β���һά�������ʽ���ʡ�
��ʵ��ʱҪע������ͼ������ÿ����Ҫ���������߽�㣬������ͼ�������ǳ��߱�
��2����дһ������OutALGraph(ALGraph G)�����ͼG�Ķ�������Ԫ�غ��ڽӱ�ṹ���ݣ�������Ȩͼ��������Ȩֵ�����ű�ʾ��
��3����дһ������VerDegree(ALGraph G)�����ͼG�и�����Ķȣ�����ͼ����Ⱥͳ��ȣ���

3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1���ֱ����CreateALGraph()������������4��ͼ���ڽӱ�洢�ṹ��
��2���ֱ����OutALGraph()�����������4��ͼ���ڽӱ�洢�����ݡ�
��3���ֱ����VerDegree()�����������4��ͼ�ĸ�����Ķȡ�
*/

//����ͼ���ڽӱ�洢
Status CreateALGraph(GraphKind GKind, ALGraph &G, int vexnum, int arcnum, char *vexs, int *arcs) {
        int i, j, k, w;
        ArcNode *p;
        G.vexnum = vexnum; //������
        G.arcnum = arcnum; //����
        G.kind = GKind; //ͼ������
        for (i = 0; i < G.vexnum; i++) {
                G.vertices[i].data = vexs[i];
                G.vertices[i].firstarc = NULL;
        }
        if (GKind == DG || GKind == UDG) {// ����ͼ,����ͼ
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        p = (ArcNode *)malloc(sizeof(ArcNode));
                        p->adjvex = j;
                        p->nextarc = G.vertices[i].firstarc;
                        G.vertices[i].firstarc = p;
                        if (GKind == UDG) {// ����ͼ
                                p = (ArcNode *)malloc(sizeof(ArcNode));
                                p->adjvex = i;
                                p->nextarc = G.vertices[j].firstarc;
                                G.vertices[j].firstarc = p;
                        }
                }
        } else if (GKind == DN || GKind == UDN) {// ��Ȩ����ͼ,��Ȩ����ͼ
                for (k = 0; k < G.arcnum; k++) {
                        i = arcs[k * 3];
                        j = arcs[k * 3 + 1];
                        w = arcs[k * 3 + 2];
                        p = (ArcNode *)malloc(sizeof(ArcNode));
                        p->adjvex = j;
                        p->weight = w;
                        p->nextarc = G.vertices[i].firstarc;
                        G.vertices[i].firstarc = p;
                        if (GKind == UDN) {// ��Ȩ����ͼ
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


//���ͼ���ڽӱ�洢
Status OutALGraph(ALGraph G) {
        int i;
        ArcNode *p;
        printf("ͼ�Ķ�������Ԫ�أ�");
        for (i = 0; i < G.vexnum; i++) {
                printf("%c ", G.vertices[i].data);
        }
        printf("\n");
        printf("ͼ���ڽӱ�\n");
        for (i = 0; i < G.vexnum; i++) {
                printf("%c->", G.vertices[i].data);
                p = G.vertices[i].firstarc;
                while (p != NULL) {
                        if (G.kind == DN || G.kind == UDN) {// ��Ȩ����ͼ,��Ȩ����ͼ
                                printf("%c(%d)->", G.vertices[p->adjvex].data, p->weight);
                        } else {
                                printf("%c->", G.vertices[p->adjvex].data);
                        }
                        p = p->nextarc;
                }
                printf("��\n");
        }
        return OK;
}

//���ͼ�и�����Ķ�
Status VerDegree(ALGraph G) {
        int i, j, inDegree, outDegree;
        ArcNode *p;
        for (i = 0; i < G.vexnum; i++) {
                inDegree = 0;
                outDegree = 0;
                for (j = 0; j < G.vexnum; j++) {// �������л�
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
                printf("����%c�����Ϊ%d������Ϊ%d\n", G.vertices[i].data, inDegree, outDegree);
        }
        return OK;
}

int main() {
       ALGraph G;
       int vexnum, arcnum;
       char vexs[MAX_VERTEX_NUM];
       int arcs[MAX_VERTEX_NUM][3];
       // ����ͼ
       printf("����ͼ\n");
       vexnum = 4;
       arcnum = 5;
        char vexs1[4] = {'A', 'B', 'C', 'D'};
        int arcs1[5][3] = {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}, {1, 2, 1}, {2, 3, 1}};
       CreateALGraph(UDG, G, vexnum, arcnum, vexs1, (int *)arcs1);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       // ����ͼ
       printf("����ͼ\n");
       vexnum = 4;
       arcnum = 6;
        char vexs2[4] = {'A', 'B', 'C', 'D'};
        int arcs2[6][3] = {{0, 1, 1}, {1, 0, 1}, {1, 2, 1}, {2, 0, 1}, {2, 1, 1}, {3, 1, 1}};
       CreateALGraph(DG, G, vexnum, arcnum, vexs2, (int *)arcs2);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       // ��Ȩ����ͼ
       printf("��Ȩ����ͼ\n");
       vexnum = 4;
       arcnum = 4;
        char vexs3[4] = {'A', 'B', 'C', 'D'};
        int arcs3[4][3] = {{0, 1, 56}, {0, 2,34}, {0, 3, 78}, {2, 3, 25}};
       CreateALGraph(UDN, G, vexnum, arcnum, vexs3, (int *)arcs3);
       OutALGraph(G);
       VerDegree(G);
       printf("\n");
       // ��Ȩ����ͼ
       printf("��Ȩ����ͼ\n");
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