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

// ջ
#define STACK_INIT_SIZE    10
#define STACKINCREMENT  5
typedef int SElemType;  //����SElemType������
typedef struct  { 
        SElemType *base;  //˳��ջ���ݴ洢�ռ��ַ 
        SElemType *top;    //˳��ջջ��ָ�� 
        int stacksize;
}SqStack;  // SqStackΪ�û������˳��ջ����

// ����malloc��������洢�ռ䣬����һ���յ�˳��ջS��S�ĳ�ʼ��СΪSTACK_INIT_SIZE��
Status InitStack(SqStack &S) {
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));// ����洢�ռ�
    if (!S.base) exit(OVERFLOW);// �洢����ʧ��
    S.top = S.base;// ջ��ָ��ָ��ջ��
    S.stacksize = STACK_INIT_SIZE;// ջ�ĳ�ʼ��С
    return OK;
}

// ������e��ջ��
Status Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {// ջ����׷�Ӵ洢�ռ�
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) exit(OVERFLOW);// �洢����ʧ��
        S.top = S.base + S.stacksize;// ջ��ָ��ָ���µ�ջ��
        S.stacksize += STACKINCREMENT;// ջ�Ĵ�С����
    }
    *S.top++ = e;// Ԫ��e��ջ
    return OK;
}

// ��ջ��Ԫ�س�ջ����e������ֵ��
Status Pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) return ERROR;// ջ��
    e = *--S.top;// ջ��Ԫ�س�ջ
    return OK;
}

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
��һ������������ͼ��ʾ����Ҫ������C/C++���Ա�дһ������������������Դ��A���յ�J�Ĺؼ�·����
*/

// ������������ȣ�������inDegree������
Status FindInDegree(ALGraph G, int *inDegree) {
    int i;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++) {//��ʼ��
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

// ȫ�ֱ���
int *ve;
int *vl;

Status TopologicalSort(ALGraph G, SqStack &T) {
    int i, j, k, e, dut;
    int *inDegree = (int *)malloc(G.vexnum * sizeof(int));
    FindInDegree(G, inDegree);//�������������
    SqStack S;
    InitStack(S);// ��ʼ��ջ
    for (i = 0; i < G.vexnum; i++) {
            if (inDegree[i] == 0) {
                    Push(S, i);// ���Ϊ0�Ķ����ջ
            }
    }
    int count = 0;
    InitStack(T);// ��ʼ����������Ķ���ջ
    // ȫ�ֱ���ve[]
    ve = (int *)malloc(G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum; i++) {
            ve[i] = 0;
    }
    while (S.top != S.base) {
        Pop(S, e);// ��ջ
        Push(T, e);// ��ջ
        printf("%c ", G.vertices[e].data);// ���
        count++;
        ArcNode *p = G.vertices[e].firstarc;
        while (p != NULL) {
                j = p->adjvex;
                inDegree[j]--;
                if (inDegree[j] == 0) {
                        Push(S, j);// ���Ϊ0�Ķ����ջ
                }
                dut = p->weight;
                if (ve[e] + dut > ve[j]) {// ���㶥��j�����緢��ʱ��
                        ve[j] = ve[e] + dut;
                }
                p = p->nextarc;
        }
    }
    if (count < G.vexnum) {
            printf("ͼ���л�·\n");
            return ERROR;
    }else{
            printf("\n");
            return OK;
    }
}

// �ؼ�·���㷨
Status CriticalPath(ALGraph G) {
    SqStack T;
    if (TopologicalSort(G, T) == ERROR) return ERROR;
    // ȫ�ֱ���vl[]
    vl = (int *)malloc(G.vexnum * sizeof(int));
    for (int i = 0; i < G.vexnum; i++) {
            vl[i] = ve[G.vexnum - 1];
    }
    int i, j, k, dut;
    ArcNode *p;
    while (T.top != T.base) {
        Pop(T, i);// ��ջ
        p = G.vertices[i].firstarc;
        while (p != NULL) {
                j = p->adjvex;
                dut = p->weight;
                if (vl[j] - dut < vl[i]) {// ���㶥��j��������ʱ��
                        vl[i] = vl[j] - dut;
                }
                p = p->nextarc;
        }
    }
    printf("�ؼ�·��Ϊ��\n");
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
    // ������
    printf("������\n");
    vexnum = 10;
    arcnum = 15;
    char vexs1[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int arcs1[15][3] = {{0, 1, 8}, {0, 2, 6}, {0, 4, 7}, {1, 3, 3}, {2, 3, 10}, {2, 6, 9}, {3, 5, 4}, {3, 8, 19}, {4, 6, 9}, {4, 7, 13}, {5, 9, 14}, {6, 7, 2}, {6, 8, 8}, {7, 8, 6}, {8, 9, 10}};
    CreateALGraph(DN, G, vexnum, arcnum, vexs1, (int *)arcs1);
    OutALGraph(G);
    CriticalPath(G);
    return 0;
}