#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2
#define MAXSIZE 100

typedef int Status;   //定义函数类型名

typedef int ElemType;//定义ElemType类型

typedef struct LNode {  //结点类型定义 
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;  



// 初始化空线性表
Status InitList(LinkList &L) { 
	L = (LinkList)malloc(sizeof(LNode)); // 分配头结点空间
	if (!L) return ERROR; // 分配失败
	L->next = NULL; // 头结点指针域置空
	return OK; // 初始化成功
}

//清空线性表元素 
Status ClearList(LinkList &L){ 
	LinkList p, q;
	p = L->next; // p指向第一个结点
	while (p) { // 遍历链表
		q = p->next; // q指向下一个结点
		free(p); // 释放p结点
		p = q; // p指向下一个结点
	}
	L->next = NULL; // 头结点指针域置空
	return OK; // 清空成功
} 

//求出线性表长度
int ListLength(LinkList L){ 
	int len = 0;
	LinkList p = L->next;
	while (p) { // 遍历链表
		len++;
		p = p->next;
	}
	return len; // 返回链表长度
}

//向线性表指定位置插入一个新元素
Status ListInsert(LinkList &L, int pos, ElemType e){
//pos为插入的（逻辑）位置,e为待插入的数据元素。插入成功则返回1；否则函数返回值为0。
	LinkList p = L;
	int i = 0;
	while (p && i < pos - 1) { // 查找插入位置
		p = p->next;
		i++;
	}
	if (!p || i > pos - 1) return ERROR; // 检查插入位置是否合法
	LinkList s = (LinkList)malloc(sizeof(LNode)); // 分配新结点空间
	if (!s) return ERROR; // 分配失败
	s->data = e; // 新结点数据域赋值
	s->next = p->next; // 新结点指针域指向后继结点
	p->next = s; // 前驱结点指针域指向新结点
	return OK; // 插入成功
} 

//从线性表中删除指定位序的元素
Status ListDelete(LinkList &L, int pos, ElemType &e)
{//pos为删除的（逻辑）位置,用item返回被删元素。删除成功则返回1；否则函数返回值为0。
	LinkList p = L;
	int i = 0;
	while (p->next && i < pos - 1) { // 查找删除位置
		p = p->next;
		i++;
	}
	if (!p->next || i > pos - 1) return ERROR; // 检查删除位置是否合法
	LinkList q = p->next; // q指向被删除结点
	e = q->data; // 保存被删除元素
	p->next = q->next; // 前驱结点指针域指向后继结点
	free(q); // 释放被删除结点
	return OK; // 删除成功

}

//获取顺序表中指定位置上的数据元素 
Status GetElem(LinkList L,int pos,ElemType &e){
//pos为指定位置,item用于返回找到的数据元素，如果表空，则返回ERROR;
	LinkList p = L;
	int i = 0;
	while (p && i < pos) { // 查找指定位置
		p = p->next;
		i++;
	}
	if (!p || i > pos) return ERROR; // 检查位置是否合法
	e = p->data; // 获取指定位置元素
	return OK;// 获取成功
} 

//返回L中第1个与e相等的数据结点的地址（指针），若e不存在，则返回NULL。
LNode *LocateList(LinkList L,ElemType e){
	LinkList p = L;
	while (p->next) { // 遍历链表
		p = p->next;
		if (p->data == e) return p; // 找到匹配元素
	}
	return NULL; // 未找到匹配元素
} 

//遍历输出线性表
Status TraverseList(LinkList L){
	LinkList p = L;
	while (p->next) { // 遍历链表
		p = p->next;
		printf("%d ", p->data); // 输出结点数据
	}
	printf("\n");
	return OK; // 遍历成功

}

// 集合并运算LA=LA∪LB
Status Union(LinkList &La, LinkList Lb){
	LinkList p = La->next;
	LinkList q = Lb->next;
	while (q) { // 遍历Lb
		if (!LocateList(La, q->data)) { // 若La中不存在该元素
			LinkList s = (LinkList)malloc(sizeof(LNode)); // 分配新结点空间
			if (!s) return ERROR; // 分配失败
			s->data = q->data; // 新结点数据域赋值
			s->next = p->next; // 新结点指针域指向后继结点
			p->next = s; // 前驱结点指针域指向新结点
			p = s; // p指向新结点
		}
		q = q->next; // q指向下一个结点
	}
	return OK;// 并运算成功

}

// 集合交运算LA=LA ∩LB
Status Intersection(LinkList &La, LinkList Lb) {
	LinkList p = La->next;
	LinkList q = Lb->next;
	LinkList r = La; // r指向La的头结点
	while (p) {// 逐个查找La中元素
		if (!LocateList(Lb, p->data)) {// 若Lb中不存在该元素
			LinkList s = p->next; // s指向下一个结点
			free(p); // 释放p结点
			r->next = s; // 前驱结点指针域指向后继结点
			p = s; // p指向下一个结点
		}
		else {
			r = p; // r指向当前结点
			p = p->next; // p指向下一个结点
		}
	}
	return OK;// 交运算成功

} 

// 集合差运算LA=LA-LB
Status Difference(LinkList &La, LinkList Lb) {
	LinkList p = La->next;
	LinkList q = Lb->next;
	LinkList r = La; // r指向La的头结点
	while (p) {// 逐个查找La中元素
		if (LocateList(Lb, p->data)) {// 若Lb中存在该元素
			LinkList s = p->next; // s指向下一个结点
			free(p); // 释放p结点
			r->next = s; // 前驱结点指针域指向后继结点
			p = s; // p指向下一个结点
		}
		else {
			r = p; // r指向当前结点
			p = p->next; // p指向下一个结点
		}
	}
	return OK;// 差运算成功

}

// 有序表合并LC=LA+LB
Status MergeList(LinkList La, LinkList Lb, LinkList &Lc) {
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = Lc;
	while (pa&&pb){
		if (pa->data <= pb->data) {
			LinkList s = (LinkList)malloc(sizeof(LNode)); // 分配新结点空间
			if (!s) return ERROR; // 分配失败
			s->data = pa->data; // 新结点数据域赋值
			pc->next = s; // 新结点指针域指向后继结点
			pc = s; // pc指向新结点
			pa = pa->next; // pa指向下一个结点
		}
		else {
			LinkList s = (LinkList)malloc(sizeof(LNode)); // 分配新结点空间
			if (!s) return ERROR; // 分配失败
			s->data = pb->data; // 新结点数据域赋值
			pc->next = s; // 新结点指针域指向后继结点
			pc = s; // pc指向新结点
			pb = pb->next; // pb指向下一个结点
		}
	}
	while (pa) {
		LinkList s = (LinkList)malloc(sizeof(LNode)); // 分配新结点空间
		if (!s) return ERROR; // 分配失败
		s->data = pa->data; // 新结点数据域赋值
		pc->next = s; // 新结点指针域指向后继结点
		pc = s; // pc指向新结点
		pa = pa->next; // pa指向下一个结点
	}
	while (pb) {
		LinkList s = (LinkList)malloc(sizeof(LNode)); // 分配新结点空间
		if (!s) return ERROR; // 分配失败
		s->data = pb->data; // 新结点数据域赋值
		pc->next = s; // 新结点指针域指向后继结点
		pc = s; // pc指向新结点
		pb = pb->next; // pb指向下一个结点
	}
	pc->next = NULL; // 尾结点指针域置空
	return OK;// 合并成功
}

// // 去掉LC重复多余的元素
// Status Purge(SqList &Lc) {
// 	for (int i = 0; i < Lc.length; i++) {// 逐个查找Lc中元素
// 		for (int j = i + 1; j < Lc.length; j++) {// 逐个比较Lc中元素
// 			if (Lc.elem[i] == Lc.elem[j]) {// 若Lc中存在重复元素
// 				if (!ListDelete(Lc, j + 1, Lc.elem[j])) return ERROR; // 删除Lc中重复元素,删除失败则返回错误
// 				j--; // 删除后，当前位置元素已改变，需重新检查当前位置
// 			}
// 		}
// 	}
// 	return OK;// 去重成功

// } 

// 去掉LC重复多余的元素
Status Purge(LinkList &Lc) {
	LinkList p = Lc->next;
	while (p) {// 逐个查找Lc中元素
		LinkList q = p;
		while (q->next) {// 逐个比较Lc中元素
			if (p->data == q->next->data) {// 若Lc中存在重复元素
				LinkList s = q->next; // s指向下一个结点
				q->next = s->next; // 前驱结点指针域指向后继结点
				free(s); // 释放s结点
			}
			else {
				q = q->next; // q指向下一个结点
			}
		}
		p = p->next; // p指向下一个结点
	}
	return OK;// 去重成功

}

// 从输入字符串中读取元素并插入到顺序表
void ReadList(LinkList &L, const char *input) {
    char *token;
    char *input_copy = strdup(input); // 复制输入字符串
    token = strtok(input_copy, ",");
    while (token != NULL) {
        int value = atoi(token);
        ListInsert(L, ListLength(L) + 1, value); // 插入到顺序表
        token = strtok(NULL, ",");
    }
    free(input_copy); // 释放复制的字符串
}

//主函数 
int main(){
	LinkList LA,LB,LC;	//定义三个链表
	// // ElemType Array1[]={2,8,27,39,66,77,89};		//顺序表LA的元素 
	// // ElemType Array2[]={6,18,27,59,65,77,89,120,140};//顺序表LB的元素 
	// ElemType item;
	// int i;
	char input[100]; // 用于存储输入字符串

	// 初始化LA,LB
    printf("初始化LA,LB\n");

    // 初始化顺序表LA,LB
    InitList(LA);
    InitList(LB);

    // 输入LA的元素
    printf("输入LA的元素：(以,分隔)\n");
	scanf("%s", input);
    // 读取输入并插入到顺序表
    ReadList(LA, input);

    // 输入LB的元素
    printf("输入LB的元素：(以,分隔)\n");
    scanf("%s", input);
    // 读取输入并插入到顺序表
    ReadList(LB, input);

	// // 备份LA,LB。用于后续更改后的恢复
	LinkList LA1,LB1;
	InitList(LA1);
	InitList(LB1);
	LinkList p = LA->next;
	while (p) {
		ListInsert(LA1, ListLength(LA1) + 1, p->data);
		p = p->next;
	}
	p = LB->next;
	while (p) {
		ListInsert(LB1, ListLength(LB1) + 1, p->data);
		p = p->next;
	}


	// // //0-2生成顺序表LA,LB
	// // for(i=0;i<7;i++) ListInsert(LA,i+1,Array1[i]);//0-2生成顺序表LA
	// // for(i=0;i<9;i++) ListInsert(LB,i+1,Array2[i]);//0-2生成顺序表LB


	//0-3输出顺序表表元素
	printf("LA的元素：");
	TraverseList(LA);
	printf("LB的元素：");
	TraverseList(LB);

	//1. 计算LA=LA∪LB，并输出结果
	Union(LA,LB);
	printf("LA∪LB的元素：");
	TraverseList(LA);

	//恢复LA,LB
	ClearList(LA);
	ClearList(LB);
	LinkList q = LA1->next;
	while (q) {
		ListInsert(LA, ListLength(LA) + 1, q->data);
		q = q->next;
	}
	q = LB1->next;
	while (q) {
		ListInsert(LB, ListLength(LB) + 1, q->data);
		q = q->next;
	}


	//2.计算LA=LA ∩LB，并输出结果
	Intersection(LA,LB);
	printf("LA∩LB的元素：");
	TraverseList(LA);

	//恢复LA,LB
	ClearList(LA);
	ClearList(LB);
	q = LA1->next;
	while (q) {
		ListInsert(LA, ListLength(LA) + 1, q->data);
		q = q->next;
	}
	q = LB1->next;
	while (q) {
		ListInsert(LB, ListLength(LB) + 1, q->data);
		q = q->next;
	}


	//3.计算LA=LA-LB，并输出结果
	Difference(LA,LB);
	printf("LA-LB的元素：");
	TraverseList(LA);

	//恢复LA,LB
	ClearList(LA);
	ClearList(LB);
	q = LA1->next;
	while (q) {
		ListInsert(LA, ListLength(LA) + 1, q->data);
		q = q->next;
	}
	q = LB1->next;
	while (q) {
		ListInsert(LB, ListLength(LB) + 1, q->data);
		q = q->next;
	}

	
	//4.有序表合并LC=LA+LB，并输出结果
	InitList(LC);
	MergeList(LA,LB,LC);
	printf("LC=LA+LB,LC的元素：");
	TraverseList(LC);

	
	//5.去掉LC重复多余的元素 ，并输出结果
	Purge(LC);
	printf("去掉LC重复多余的元素后的LC的元素：");
	TraverseList(LC);


	return 1;
}

// test input
// 2,8,27,39,66,77,89
// 6,18,27,59,65,77,89,120,140