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

typedef struct {	 
    ElemType *elem;  //线性表数据存储空间基址 
    int length;		//线性表当前长度
}SqList;// LIST为用户定义的线性表类型




// 初始化空线性表
Status InitList(SqList &L) { 
    L.elem = new ElemType[MAXSIZE]; // 利用new函数申请存储空间
    if (!L.elem) return OVERFLOW; // 检查内存分配是否成功
    L.length = 0; // 空表长度为0
    return OK;
}

//清空线性表元素 
Status ClearList(SqList &L){ 
	L.length=0;
	return OK;
} 

//求出线性表长度
int ListLength(SqList L){ 
	return L.length;
}

//向线性表指定位置插入一个新元素
Status ListInsert(SqList &L, int pos, ElemType e){
//pos为插入的（逻辑）位置,e为待插入的数据元素。插入成功则返回1；否则函数返回值为0。
	if (pos<1 || pos>L.length+1) return ERROR; // 检查插入位置是否合法
	if (L.length >= MAXSIZE) return ERROR; // 检查存储空间是否已满
	for (int i = L.length; i >= pos; i--) {// 插入位置及之后的元素后移
		L.elem[i] = L.elem[i - 1]; 
	}

	L.elem[pos - 1] = e; // 插入新元素
	L.length++; // 更新表长
	return OK;// 插入成功
} 

//从线性表中删除指定位序的元素
Status ListDelete(SqList &L, int pos, ElemType &e)
{//pos为删除的（逻辑）位置,用item返回被删元素。删除成功则返回1；否则函数返回值为0。
	if (pos<1 || pos>L.length) return ERROR; // 检查删除位置是否合法
	e = L.elem[pos - 1]; // 保存被删除元素
	for (int i = pos; i < L.length; i++) {// 删除位置之后的元素前移
		L.elem[i - 1] = L.elem[i];
	}
	L.length--; // 更新表长

	return OK;// 删除成功

}

//获取顺序表中指定位置上的数据元素 
Status GetElem(SqList L,int pos,ElemType &e){
//pos为指定位置,item用于返回找到的数据元素，如果表空，则返回ERROR;
	if (pos<1 || pos>L.length) return ERROR; // 检查位置是否合法
	e = L.elem[pos - 1]; // 获取指定位置元素
	return OK;// 获取成功
} 

//从线性表中查找元素，返回第一个与指定值匹配元素位置
int LocateElem(SqList L,ElemType e){

	for (int i = 0; i < L.length; i++) {// 顺序查找
		if (L.elem[i] == e) return i + 1; // 找到匹配元素
	}
	return 0; // 未找到匹配元素

} 

//遍历输出线性表
Status TraverseList(SqList L){
	for (int i = 0; i < L.length; i++) {// 顺序输出
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	return OK;

}

// 集合并运算LA=LA∪LB
Status Union(SqList &La, SqList Lb){
	for (int i = 0; i < Lb.length; i++) {// 逐个查找LB中元素
		if (!LocateElem(La, Lb.elem[i])) {// 若La中不存在该元素
			if (!ListInsert(La, La.length + 1, Lb.elem[i])) return ERROR; // 插入到La中,插入失败则返回错误
		}
	}
	return OK;// 并运算成功

}

// 集合交运算LA=LA ∩LB
Status Intersection(SqList &La, SqList Lb) {
    for (int i = 0; i < La.length; i++) {// 逐个查找La中元素
		if (!LocateElem(Lb, La.elem[i])) {// 若Lb中不存在该元素
			if (!ListDelete(La, i + 1, La.elem[i])) return ERROR; // 删除La中该元素,删除失败则返回错误
			i--; // 删除后，当前位置元素已改变，需重新检查当前位置
		}
	}
	return OK;// 交运算成功

} 

// 集合差运算LA=LA-LB
Status Difference(SqList &La, SqList Lb) {
	for (int i = 0; i < La.length; i++) {// 逐个查找La中元素
		if (LocateElem(Lb, La.elem[i])) {// 若Lb中存在该元素
			if (!ListDelete(La, i + 1, La.elem[i])) return ERROR; // 删除La中该元素,删除失败则返回错误
			i--; // 删除后，当前位置元素已改变，需重新检查当前位置
		}
	}
	return OK;// 差运算成功

}

// 有序表合并LC=LA+LB
Status MergeList(SqList La, SqList Lb, SqList &Lc) {
	int i = 0, j = 0, k = 0;
	while (i < La.length && j < Lb.length) {// 逐个比较La和Lb中元素
		if (La.elem[i] < Lb.elem[j]) {// 若La中元素小于Lb中元素
			Lc.elem[k++] = La.elem[i++]; // 将La中元素插入Lc中
		}
		else {
			Lc.elem[k++] = Lb.elem[j++]; // 将Lb中元素插入Lc中
		}
	}
	while (i < La.length) {// 将La中剩余元素插入Lc中
		Lc.elem[k++] = La.elem[i++];
	}
	while (j < Lb.length) {// 将Lb中剩余元素插入Lc中
		Lc.elem[k++] = Lb.elem[j++];
	}
	Lc.length = k; // 更新Lc的长度
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
Status Purge(SqList &Lc) {
	int i = 0, j = 0;
	while (i < Lc.length) {// 逐个查找Lc中元素
		j = i + 1;
		while (j < Lc.length) {// 逐个比较Lc中元素
			if (Lc.elem[i] == Lc.elem[j]) {// 若Lc中存在重复元素
				if (!ListDelete(Lc, j + 1, Lc.elem[j])) return ERROR; // 删除Lc中重复元素,删除失败则返回错误
			}
			else {
				j++;
			}
		}
		i++;
	}
	return OK;// 去重成功

}

// 从输入字符串中读取元素并插入到顺序表
void ReadList(SqList &L, const char *input) {
    char *token;
    char *input_copy = strdup(input); // 复制输入字符串
    token = strtok(input_copy, ",");
    while (token != NULL) {
        int value = atoi(token);
        ListInsert(L, L.length + 1, value);
        token = strtok(NULL, ",");
    }
    free(input_copy); // 释放复制的字符串
}

//主函数 
int main(){
	SqList LA,LB,LC;				//定义顺序表变量
	// ElemType Array1[]={2,8,27,39,66,77,89};		//顺序表LA的元素 
	// ElemType Array2[]={6,18,27,59,65,77,89,120,140};//顺序表LB的元素 
	ElemType item;
	int i;
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

	// 备份LA,LB。用于后续更改后的恢复
	SqList LA1,LB1;
	InitList(LA1);
	InitList(LB1);
	for(i=0;i<LA.length;i++) ListInsert(LA1,i+1,LA.elem[i]);
	for(i=0;i<LB.length;i++) ListInsert(LB1,i+1,LB.elem[i]);


	// //0-2生成顺序表LA,LB
	// for(i=0;i<7;i++) ListInsert(LA,i+1,Array1[i]);//0-2生成顺序表LA
	// for(i=0;i<9;i++) ListInsert(LB,i+1,Array2[i]);//0-2生成顺序表LB


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
	for(i=0;i<LA1.length;i++) ListInsert(LA,i+1,LA1.elem[i]);
	for(i=0;i<LB1.length;i++) ListInsert(LB,i+1,LB1.elem[i]);


	//2.计算LA=LA ∩LB，并输出结果
	Intersection(LA,LB);
	printf("LA∩LB的元素：");
	TraverseList(LA);

	//恢复LA,LB
	ClearList(LA);
	ClearList(LB);
	for(i=0;i<LA1.length;i++) ListInsert(LA,i+1,LA1.elem[i]);
	for(i=0;i<LB1.length;i++) ListInsert(LB,i+1,LB1.elem[i]);

	//3.计算LA=LA-LB，并输出结果
	Difference(LA,LB);
	printf("LA-LB的元素：");
	TraverseList(LA);

	//恢复LA,LB
	ClearList(LA);
	ClearList(LB);
	for(i=0;i<LA1.length;i++) ListInsert(LA,i+1,LA1.elem[i]);
	for(i=0;i<LB1.length;i++) ListInsert(LB,i+1,LB1.elem[i]);

	
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