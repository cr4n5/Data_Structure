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

/*
2. ͼ���ڽӱ�洢�����������ʵ��
����ʵ��3-2��CreateALGraph()������OutALGraph()����ʵ��ͼ���ڽӱ�洢�����������

3. ͼ�ı���������ʵ��
��1����дһ��ͼ��������ȱ�������DFSTraverse(ALGraph G)�����������ı������С�������õݹ鷽ʽʵ�֡�
��2����дһ��ͼ�Ĺ�����ȱ�������BFSTraverse(ALGraph G)�����������ı������С�������÷ǵݹ鷽ʽʵ�֡�

4. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1������CreateALGraph()������������ͼ���ڽӱ�洢�ṹ��
��2������OutALGraph()���������ͼ���ڽӱ�洢���ݡ�
��3������������ȱ�������DFSTraverse()�����������ı������С�
��4�����ù�����ȱ�������BFSTraverse()�����������ı������С�
*/

//������ȱ���
bool visited[MAX_VERTEX_NUM];
Status DFS(ALGraph G, int v) {
        ArcNode *p;
        visited[v] = TRUE;
        printf("%c ", G.vertices[v].data);
        p = G.vertices[v].firstarc;
        while (p != NULL) {
                if (!visited[p->adjvex]) {
                        DFS(G, p->adjvex);// ������������
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

//������ȱ���
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
                                DeQueue(Q, j);// ���г��ӣ�Ȼ����ʸö���������ڽӵ�
                                p = G.vertices[j].firstarc;
                                while (p != NULL) {
                                        if (!visited[p->adjvex]) {
                                                visited[p->adjvex] = TRUE;
                                                printf("%c ", G.vertices[p->adjvex].data);
                                                EnQueue(Q, p->adjvex);// ���ö���������ڽӵ����
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
