#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;         //声明函数类型名
#define STACK_INIT_SIZE    10
#define STACKINCREMENT  5
typedef int SElemType;  //声明SElemType的类型
typedef struct  { 
        SElemType *base;  //顺序栈数据存储空间基址 
        SElemType *top;    //顺序栈栈顶指针 
        int stacksize;
}SqStack;  // SqStack为用户定义的顺序栈类型


#define MAXQSIZE 10    //队列的最大长度
typedef int QElemtype;  //声明QElemtype的类型
typedef struct {
       QElemtype *base;    //初始化队列时动态分配存储空间的地址(数组名)
       int front;                 //头元素的下标变量
       int rear;                   //尾元素的下标变量
} SqQueue;   // SqQueue为用户定义的循环队列类型

/*
2. 顺序栈基本操作函数的实现
根据定义的顺序栈结构，编写下列基本操作函数的C/C++源代码：
（1）InitStack(SqStack &S)——利用malloc函数申请存储空间，构造一个空的顺序栈S，S的初始大小为STACK_INIT_SIZE。
（2）ClearStack(SqStack &S)——将顺序栈数据清空。只需做S.top=S.base赋值操作即可。 
（3）StackLength(SqStack S)——返回L中数据元素个数。直接返回S.top-S.base的值即可。
（4）GetTop(SqStack S, SElemType &e)——用e返回栈顶元素的值。 
（5）Push(SqStack &S, SElemType e)——将数据e进栈。
（6）Pop(SqStack &S, SElemType &e)——将栈顶元素出栈，用e返回其值。
3. 循环队列基本操作函数的实现
根据定义的循环队列结构，编写下列基本操作函数的C/C++源代码：
（1）InitQueue(SqQueue &Q)——利用malloc函数申请存储空间，构造一个空的循环队列Q，Q的大小为MAXQSIZE。
（2）ClearQueue(SqQueue &Q)——将循环队列数据清空。 
（3）QueueLength(SqQueue Q)——返回Q中数据元素个数。
（4）EnQueue(SqQueue &Q, QElemType e)——数据e入队。
（5）DeQueue(SqStack &Q, QElemType &e)——数据出队，用e返回其值。
（6）QueueEmpty(SqQueue Q)——判对空。
（7）QueueFull(SqQueue Q)——判队满。
4. 应用案例 
（1）利用顺序栈的基本操作函数，编制一个将十进制整数m转换成n进制(n=2或8)整数的数制转换函数Conversion(m,n) ，并在函数中输出转换结果。
（2）编一个函数QueueReverse(Q)，利用栈将将队列中的元素逆序重排，即队头元素变成队尾元素。
5. 主函数main()
（1）数制转换
输入一个十进制数m，调用Conversion(m,n) 函数将m转换成二进制数和八进制数。
（2）循环队列操作
<1>连续入队9个整数后，显示队列Q的front和rear的值；
<2>若再入队1个整数，显示此时队列的状态信息；
<3>连续出队5个整数，再入队2个整数，显示此时的队列Q的长度与front和rear的值；
<4>调用函数QueueReverse(Q)，将队列元素逆序重排，然后将队列元素出队并输出。
*/

/*
顺序栈基本操作函数的实现
*/

// 利用malloc函数申请存储空间，构造一个空的顺序栈S，S的初始大小为STACK_INIT_SIZE。
Status InitStack(SqStack &S) {
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));// 分配存储空间
    if (!S.base) exit(OVERFLOW);// 存储分配失败
    S.top = S.base;// 栈顶指针指向栈底
    S.stacksize = STACK_INIT_SIZE;// 栈的初始大小
    return OK;
}

// 将顺序栈数据清空。只需做S.top=S.base赋值操作即可。
Status ClearStack(SqStack &S) {
    S.top = S.base;// 栈顶指针指向栈底
    return OK;
}

// 返回L中数据元素个数。直接返回S.top-S.base的值即可。
int StackLength(SqStack S) {
    return S.top - S.base;
}

// 用e返回栈顶元素的值。
Status GetTop(SqStack S, SElemType &e) {
    if (S.top == S.base) return ERROR;// 栈空
    e = *(S.top - 1);// 栈顶元素赋值给e
    return OK;
}

// 将数据e进栈。
Status Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {// 栈满，追加存储空间
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) exit(OVERFLOW);// 存储分配失败
        S.top = S.base + S.stacksize;// 栈顶指针指向新的栈顶
        S.stacksize += STACKINCREMENT;// 栈的大小增加
    }
    *S.top++ = e;// 元素e进栈
    return OK;
}

// 将栈顶元素出栈，用e返回其值。
Status Pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) return ERROR;// 栈空
    e = *--S.top;// 栈顶元素出栈
    return OK;
}

/*
循环队列基本操作函数的实现
*/

// 利用malloc函数申请存储空间，构造一个空的循环队列Q，Q的大小为MAXQSIZE。
Status InitQueue(SqQueue &Q) {
    Q.base = (QElemtype *)malloc(MAXQSIZE * sizeof(QElemtype));// 分配存储空间
    if (!Q.base) exit(OVERFLOW);// 存储分配失败
    Q.front = Q.rear = 0;// 队头和队尾指针指向队列起始位置
    return OK;
}

// 将循环队列数据清空。
Status ClearQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;// 队头和队尾指针指向队列起始位置
    return OK;
}

// 返回Q中数据元素个数。
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 数据e入队。
Status EnQueue(SqQueue &Q, QElemtype e) {
    if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;// 队满
    Q.base[Q.rear] = e;// 元素e入队
    Q.rear = (Q.rear + 1) % MAXQSIZE;// 队尾指针后移
    return OK;
}

// 数据出队，用e返回其值。
Status DeQueue(SqQueue &Q, QElemtype &e) {
    if (Q.front == Q.rear) return ERROR;// 队空
    e = Q.base[Q.front];// 队头元素赋值给e
    Q.front = (Q.front + 1) % MAXQSIZE;// 队头指针后移
    return OK;
}

// 判对空。
Status QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

// 判队满。
Status QueueFull(SqQueue Q) {
    return (Q.rear + 1) % MAXQSIZE == Q.front;
}

// 数制转换
void Conversion(int m, int n) {
    SqStack S;
    InitStack(S);// 初始化栈
    while (m) {
        Push(S, m % n);// 余数进栈
        m /= n;// 商继续转换
    }
    SElemType e;
    while (S.top != S.base) {
        Pop(S, e);// 逐个出栈
        printf("%d", e);// 输出
    }
    printf("\n");
}

// 用栈将队列中的元素逆序重排
void QueueReverse(SqQueue &Q) {
    SqStack S;
    InitStack(S);// 初始化栈
    QElemtype e;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, e);// 逐个出队
        Push(S, e);// 入栈
    }
    while (S.top != S.base) {
        Pop(S, e);// 逐个出栈
        EnQueue(Q, e);// 入队
    }
}

// 从输入字符串中读取元素并入队
// 2,8,27,39,66,77,89
void ReadQueue(SqQueue &Q, const char *input) {
    char *token;
    char *input_copy = strdup(input);// 复制输入字符串
    token = strtok(input_copy, ",");
    while (token != NULL) {
        int value = atoi(token);
        if (QueueFull(Q)) {
            printf("队列已满,元素%d开始无法入队\n", value);
            break;
        }
        EnQueue(Q, value);// 入队
        token = strtok(NULL, ",");
    }
    free(input_copy);// 释放复制的字符串
}


int main(){
    // 数制转换
    int m;
    printf("请输入 m: ");
    scanf("%d", &m);
    printf("转换成二进制: ");
    Conversion(m, 2);// 转换成二进制
    printf("转化成八进制: ");
    Conversion(m, 8);// 转换成八进制

    // 循环队列操作
    SqQueue Q;
    InitQueue(Q);// 初始化队列
    QElemtype e;

    while(1){
        // 菜单选择入队出队，显示状态队列信息，输入0退出
        printf("\n1. 入队\n2. 出队\n3. 显示状态信息\n0. 退出\n\n");
        int op;
        scanf("%d", &op);
        printf("\n");
        if (op == 0) break;
        switch (op) {
            case 1:
                printf("请输入入队元素(以,分隔): ");// 2,8,27,39,66,77,89
                char input[100];
                scanf("%s", input);
                ReadQueue(Q, input);// 从输入字符串中读取元素并入队
                break;
            case 2:
                if (QueueEmpty(Q)) {
                    printf("队列为空\n");
                    break;
                }
                printf("出队元素个数: ");
                int n;
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    DeQueue(Q, e);// 出队
                    printf("%d ", e);
                }
                printf("\n");
                break;
            case 3:
                printf("队列长度: %d\n", QueueLength(Q));// 显示队列长度
                printf("队头: %d, 队尾: %d\n", Q.front, Q.rear);// 显示队头和队尾
                break;
            default:
                printf("输入错误\n");
        }
    }

    printf("调用函数QueueReverse(Q)，将队列元素逆序重排，然后将队列元素出队并输出。\n");
    QueueReverse(Q);// 调用函数QueueReverse(Q)
    while (!QueueEmpty(Q)) {
        DeQueue(Q, e);// 将队列元素逆序重排，然后将队列元素出队并输出
        printf("%d ", e);
    }
    printf("\n");

    return 0;
}

// test input
// 6,18,27,59,65,77,89,120,140