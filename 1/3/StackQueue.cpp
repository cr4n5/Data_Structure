#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;         //��������������
#define STACK_INIT_SIZE    10
#define STACKINCREMENT  5
typedef int SElemType;  //����SElemType������
typedef struct  { 
        SElemType *base;  //˳��ջ���ݴ洢�ռ��ַ 
        SElemType *top;    //˳��ջջ��ָ�� 
        int stacksize;
}SqStack;  // SqStackΪ�û������˳��ջ����


#define MAXQSIZE 10    //���е���󳤶�
typedef int QElemtype;  //����QElemtype������
typedef struct {
       QElemtype *base;    //��ʼ������ʱ��̬����洢�ռ�ĵ�ַ(������)
       int front;                 //ͷԪ�ص��±����
       int rear;                   //βԪ�ص��±����
} SqQueue;   // SqQueueΪ�û������ѭ����������

/*
2. ˳��ջ��������������ʵ��
���ݶ����˳��ջ�ṹ����д���л�������������C/C++Դ���룺
��1��InitStack(SqStack &S)��������malloc��������洢�ռ䣬����һ���յ�˳��ջS��S�ĳ�ʼ��СΪSTACK_INIT_SIZE��
��2��ClearStack(SqStack &S)������˳��ջ������ա�ֻ����S.top=S.base��ֵ�������ɡ� 
��3��StackLength(SqStack S)��������L������Ԫ�ظ�����ֱ�ӷ���S.top-S.base��ֵ���ɡ�
��4��GetTop(SqStack S, SElemType &e)������e����ջ��Ԫ�ص�ֵ�� 
��5��Push(SqStack &S, SElemType e)����������e��ջ��
��6��Pop(SqStack &S, SElemType &e)������ջ��Ԫ�س�ջ����e������ֵ��
3. ѭ�����л�������������ʵ��
���ݶ����ѭ�����нṹ����д���л�������������C/C++Դ���룺
��1��InitQueue(SqQueue &Q)��������malloc��������洢�ռ䣬����һ���յ�ѭ������Q��Q�Ĵ�СΪMAXQSIZE��
��2��ClearQueue(SqQueue &Q)������ѭ������������ա� 
��3��QueueLength(SqQueue Q)��������Q������Ԫ�ظ�����
��4��EnQueue(SqQueue &Q, QElemType e)��������e��ӡ�
��5��DeQueue(SqStack &Q, QElemType &e)�������ݳ��ӣ���e������ֵ��
��6��QueueEmpty(SqQueue Q)�����жԿա�
��7��QueueFull(SqQueue Q)�����ж�����
4. Ӧ�ð��� 
��1������˳��ջ�Ļ�����������������һ����ʮ��������mת����n����(n=2��8)����������ת������Conversion(m,n) �����ں��������ת�������
��2����һ������QueueReverse(Q)������ջ���������е�Ԫ���������ţ�����ͷԪ�ر�ɶ�βԪ�ء�
5. ������main()
��1������ת��
����һ��ʮ������m������Conversion(m,n) ������mת���ɶ��������Ͱ˽�������
��2��ѭ�����в���
<1>�������9����������ʾ����Q��front��rear��ֵ��
<2>�������1����������ʾ��ʱ���е�״̬��Ϣ��
<3>��������5�������������2����������ʾ��ʱ�Ķ���Q�ĳ�����front��rear��ֵ��
<4>���ú���QueueReverse(Q)��������Ԫ���������ţ�Ȼ�󽫶���Ԫ�س��Ӳ������
*/

/*
˳��ջ��������������ʵ��
*/

// ����malloc��������洢�ռ䣬����һ���յ�˳��ջS��S�ĳ�ʼ��СΪSTACK_INIT_SIZE��
Status InitStack(SqStack &S) {
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));// ����洢�ռ�
    if (!S.base) exit(OVERFLOW);// �洢����ʧ��
    S.top = S.base;// ջ��ָ��ָ��ջ��
    S.stacksize = STACK_INIT_SIZE;// ջ�ĳ�ʼ��С
    return OK;
}

// ��˳��ջ������ա�ֻ����S.top=S.base��ֵ�������ɡ�
Status ClearStack(SqStack &S) {
    S.top = S.base;// ջ��ָ��ָ��ջ��
    return OK;
}

// ����L������Ԫ�ظ�����ֱ�ӷ���S.top-S.base��ֵ���ɡ�
int StackLength(SqStack S) {
    return S.top - S.base;
}

// ��e����ջ��Ԫ�ص�ֵ��
Status GetTop(SqStack S, SElemType &e) {
    if (S.top == S.base) return ERROR;// ջ��
    e = *(S.top - 1);// ջ��Ԫ�ظ�ֵ��e
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

/*
ѭ�����л�������������ʵ��
*/

// ����malloc��������洢�ռ䣬����һ���յ�ѭ������Q��Q�Ĵ�СΪMAXQSIZE��
Status InitQueue(SqQueue &Q) {
    Q.base = (QElemtype *)malloc(MAXQSIZE * sizeof(QElemtype));// ����洢�ռ�
    if (!Q.base) exit(OVERFLOW);// �洢����ʧ��
    Q.front = Q.rear = 0;// ��ͷ�Ͷ�βָ��ָ�������ʼλ��
    return OK;
}

// ��ѭ������������ա�
Status ClearQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;// ��ͷ�Ͷ�βָ��ָ�������ʼλ��
    return OK;
}

// ����Q������Ԫ�ظ�����
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// ����e��ӡ�
Status EnQueue(SqQueue &Q, QElemtype e) {
    if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;// ����
    Q.base[Q.rear] = e;// Ԫ��e���
    Q.rear = (Q.rear + 1) % MAXQSIZE;// ��βָ�����
    return OK;
}

// ���ݳ��ӣ���e������ֵ��
Status DeQueue(SqQueue &Q, QElemtype &e) {
    if (Q.front == Q.rear) return ERROR;// �ӿ�
    e = Q.base[Q.front];// ��ͷԪ�ظ�ֵ��e
    Q.front = (Q.front + 1) % MAXQSIZE;// ��ͷָ�����
    return OK;
}

// �жԿա�
Status QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

// �ж�����
Status QueueFull(SqQueue Q) {
    return (Q.rear + 1) % MAXQSIZE == Q.front;
}

// ����ת��
void Conversion(int m, int n) {
    SqStack S;
    InitStack(S);// ��ʼ��ջ
    while (m) {
        Push(S, m % n);// ������ջ
        m /= n;// �̼���ת��
    }
    SElemType e;
    while (S.top != S.base) {
        Pop(S, e);// �����ջ
        printf("%d", e);// ���
    }
    printf("\n");
}

// ��ջ�������е�Ԫ����������
void QueueReverse(SqQueue &Q) {
    SqStack S;
    InitStack(S);// ��ʼ��ջ
    QElemtype e;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, e);// �������
        Push(S, e);// ��ջ
    }
    while (S.top != S.base) {
        Pop(S, e);// �����ջ
        EnQueue(Q, e);// ���
    }
}

// �������ַ����ж�ȡԪ�ز����
// 2,8,27,39,66,77,89
void ReadQueue(SqQueue &Q, const char *input) {
    char *token;
    char *input_copy = strdup(input);// ���������ַ���
    token = strtok(input_copy, ",");
    while (token != NULL) {
        int value = atoi(token);
        if (QueueFull(Q)) {
            printf("��������,Ԫ��%d��ʼ�޷����\n", value);
            break;
        }
        EnQueue(Q, value);// ���
        token = strtok(NULL, ",");
    }
    free(input_copy);// �ͷŸ��Ƶ��ַ���
}


int main(){
    // ����ת��
    int m;
    printf("������ m: ");
    scanf("%d", &m);
    printf("ת���ɶ�����: ");
    Conversion(m, 2);// ת���ɶ�����
    printf("ת���ɰ˽���: ");
    Conversion(m, 8);// ת���ɰ˽���

    // ѭ�����в���
    SqQueue Q;
    InitQueue(Q);// ��ʼ������
    QElemtype e;

    while(1){
        // �˵�ѡ����ӳ��ӣ���ʾ״̬������Ϣ������0�˳�
        printf("\n1. ���\n2. ����\n3. ��ʾ״̬��Ϣ\n0. �˳�\n\n");
        int op;
        scanf("%d", &op);
        printf("\n");
        if (op == 0) break;
        switch (op) {
            case 1:
                printf("���������Ԫ��(��,�ָ�): ");// 2,8,27,39,66,77,89
                char input[100];
                scanf("%s", input);
                ReadQueue(Q, input);// �������ַ����ж�ȡԪ�ز����
                break;
            case 2:
                if (QueueEmpty(Q)) {
                    printf("����Ϊ��\n");
                    break;
                }
                printf("����Ԫ�ظ���: ");
                int n;
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    DeQueue(Q, e);// ����
                    printf("%d ", e);
                }
                printf("\n");
                break;
            case 3:
                printf("���г���: %d\n", QueueLength(Q));// ��ʾ���г���
                printf("��ͷ: %d, ��β: %d\n", Q.front, Q.rear);// ��ʾ��ͷ�Ͷ�β
                break;
            default:
                printf("�������\n");
        }
    }

    printf("���ú���QueueReverse(Q)��������Ԫ���������ţ�Ȼ�󽫶���Ԫ�س��Ӳ������\n");
    QueueReverse(Q);// ���ú���QueueReverse(Q)
    while (!QueueEmpty(Q)) {
        DeQueue(Q, e);// ������Ԫ���������ţ�Ȼ�󽫶���Ԫ�س��Ӳ����
        printf("%d ", e);
    }
    printf("\n");

    return 0;
}

// test input
// 6,18,27,59,65,77,89,120,140