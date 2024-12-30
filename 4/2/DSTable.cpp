#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int KeyType;        //关键字的数据类型

//数据元素（记录）的类型定义
typedef struct {
        KeyType  key;            //学号(关键字)
        const char *name;     //姓名
        const char *sex;         //性别 
        int  age;                     //年龄 
} RecordType;

//动态查找表BST的类型定义
typedef  struct BSTNode {   
        RecordType  data;
        struct BSTNode *lchild, *rchild; //指向左右孩子结点的指针
}BSTNode, *BSTree;

/*
2. 动态查找表基本操作的实现

根据定义的存储结构，编写下列基本操作函数的C/C++源代码：
（1）编写一个插入函数InsertDSTable_BST(BSTree &DT, RecordType e)，根据BST的性质将数据元素e插入到动态查找表DT中。若元素e在DT中已存在，则操作失败，返回FALSE。
（2）编写一个创建动态查找表的函数CreateDSTable_BST(BSTree &DT, SSTable &ST)，其中ST为实验4-1所创建的静态查找表。该函数要调用InsertDSTable_BST()函数。
注：为提高程序调试速度，该函数允许直接用实验4-1所创建的静态查找表ST1中的数据元素。
（3）编写一个中序遍历函数TraversDSTable_InOrde(BSTree DT)，输出动态查找表DT的所有数据元素。
（4）编写一个查找函数 BSTree SearchDSTable_BST(BSTree DT, KeyType key)，其中参数key为要查找元素的关键字。若查找成功，函数返回该关键字元素结点的地址（指针），否则，查找不成功，返回NULL。该函数可以用递归或非递归方式实现，同时要计数查找过程中关键字比较的次数（递归函数可利用全局变量实现）。
（5）编写一个删除函数 DeleteDSTable_BST(BSTree &DT, KeyType key)，其中参数key为要删除元素的关键字，若该关键字的元素在DT中不存在，则操作失败，返回FALSE。

3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）定义一个静态查找表ST1，将下列各元素的值写入ST1，然后输出ST1的各元素的值。相关类型定义和操作函数可直接利用实验4-1.
    学号key	 姓名name 	   性别sex    年龄age 
       56    Zhang          F           19
       19 	 Wang 	        F 	        20
       80 	 Zhou 	        F 	        19 
        5 	 Huang 	        M	        20 
       21 	 Zheng 	        M 	        20
       64 	 Li 	        M 	        19 
       88 	 Liu 	        F 	        18 
       13 	 Qian 	        F 	        19 
       37 	 Sun 	        M 	        20 
       75 	 Zhao 	        M 	        20 
       92 	 Chen 	        M 	        20 
（2）定义一个动态查找表DT1，调用CreateDSTable_BST(DT1,ST1)函数，根据静态查找表ST1中的数据元素创建动态查找表DT1，然后调用TraversDSTable_InOrder(DT1)函数输出DT1中的的所有数据元素。
（3）编写一段代码，根据输入的一个关键字，调用SearchDSTable_BST()函数，查找动态表中的数据元素，若查找成功，输出找到的元素（记录）的值和关键字的比较次数，否则输出“当前要查找的记录不存在！”和关键字的比较次数。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
（4）依次使用静态查找表ST1中的关键字调用SearchDSTable_BST()函数，查找动态表中的数据元素，计算并输出查找成功的ASL。
（5）选择使用不在静态查找表中的关键字进行查找，计算并输出查找不成功的ASL。
（6）编写一段代码，实现动态查找的元素插入操作。首先输入(scanf)要插入元素e的各个数据项的值，调用InsertDSTable_BST(DT1, e)将元素e插入到动态查找表中，若插入成功，调用TraversDSTable_InOrder(DT1)函数输出DT1中的的所有数据元素，否则输出“当前要插入的记录已存在，禁止插入！”。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
（7）编写一段代码，实现动态查找的元素删除操作。首先输入要删除元素的关键字值，调用DeleteDSTable_BST(DT1, key)将关键字为key的元素e从DT1中删除，若删除成功，调用TraversDSTable_InOrder(DT1)函数输出DT1中的的所有数据元素，否则输出“当前要删除的记录不存在，禁止删除！”。该段代码可以重复上述操作多次，关键字输入“-1”时结束。

附录：main()函数
int main(){
	int i,key;
	int n=11;
	SSTable ST1;
	BSTree DT1,p;

	//创建静态查找表ST1 
	CreateSSTable(ST1,n);
	printf("\n静态查找表\n");
	TraversSSTable(ST1);

	//创建动态查找表DT1 
	CreateDSTable_BST(DT1,ST1);
	printf("\n动态查找表(中序遍历)\n");
	printf("学号 姓名 性别 年龄\n");
	TraversDSTable_InOrder(DT1);

	//查找动态查找表元素 
	printf("\n---元素查找---\n");
	printf("\n请输入要查找记录的学号(输入-1结束)："); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0;
		p=SearchDSTable_BST2(DT1,key);
		if(!p)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem_BST(p); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",count);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	} 

	int total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchDSTable_BST1(DT1, ST1.elem[i].key);
		total=total+count;
	}
	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchDSTable_BST1(DT1,4);
		else SearchDSTable_BST1(DT1,ST1.elem[i].key+1);
		total=total+count;
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));

	//构造动态查找表（插入新元素 ） 
	printf("\n---元素插入---\n");
	RecordType e;
	printf("\n请输入要插入的新记录(输入-1结束)\n学号 姓名 性别 年龄\n");
	InputElem(e); 
	while (e.key!=-1) {
		if(InsertDSTable_BST(DT1,e)){
			printf("\n插入元素后的动态查找表(中序遍历)\n");
			printf("学号 姓名 性别 年龄\n");
			TraversDSTable_InOrder(DT1);
		}
		else printf("当前要插入的记录已存在，禁止插入！\n");
		printf("\n请输入要插入的新记录(输入-1结束)\n学号 姓名 性别 年龄\n");
		InputElem(e); 
	}

	//删除动态查找表元素 
	printf("\n---元素删除---\n");
	printf("\n请输入要删除记录的学号(输入-1结束)："); 
	scanf("%d",&key); 
	while (key!=-1){
		if(DeleteDSTable_BST(DT1,key)){
			printf("\n删除元素后的动态查找表(中序遍历)\n");
			printf("学号 姓名 性别 年龄\n");
			TraversDSTable_InOrder(DT1);
		}
	    else printf("当前要删除的记录不存在！\n");
		printf("\n请输入要删除记录的学号(输入-1结束)："); //下一次删除 
		scanf("%d",&key); 
	} 

	return 1;
}
*/

// 添加结构体定义
typedef struct {
    int key;
    char name[20];
    char sex[2];
    int age;
} DATA_TYPE;

// 定义全局数组
DATA_TYPE DATA[12];

// 创建静态查找表
typedef struct {
    RecordType *elem; //存储数据元素的一维数组
    int length; //记录的长度
} SSTable;

// 创建静态查找表
void CreateSSTable(SSTable &ST, int n) {
    ST.elem = (RecordType *)malloc((n+1)*sizeof(RecordType));
    if (!ST.elem) exit(OVERFLOW);
    ST.length = n;

    // 初始化数据元素
    DATA[0].key = 0; strcpy(DATA[0].name, ""); strcpy(DATA[0].sex, ""); DATA[0].age = 0;
    DATA[1].key = 56; strcpy(DATA[1].name, "Zhang"); strcpy(DATA[1].sex, "F"); DATA[1].age = 19;
    DATA[2].key = 19; strcpy(DATA[2].name, "Wang"); strcpy(DATA[2].sex, "F"); DATA[2].age = 20;
    DATA[3].key = 80; strcpy(DATA[3].name, "Zhou"); strcpy(DATA[3].sex, "F"); DATA[3].age = 19;
    DATA[4].key = 5; strcpy(DATA[4].name, "Huang"); strcpy(DATA[4].sex, "M"); DATA[4].age = 20;
    DATA[5].key = 21; strcpy(DATA[5].name, "Zheng"); strcpy(DATA[5].sex, "M"); DATA[5].age = 20;
    DATA[6].key = 64; strcpy(DATA[6].name, "Li"); strcpy(DATA[6].sex, "M"); DATA[6].age = 19;
    DATA[7].key = 88; strcpy(DATA[7].name, "Liu"); strcpy(DATA[7].sex, "F"); DATA[7].age = 18;
    DATA[8].key = 13; strcpy(DATA[8].name, "Qian"); strcpy(DATA[8].sex, "F"); DATA[8].age = 19;
    DATA[9].key = 37; strcpy(DATA[9].name, "Sun"); strcpy(DATA[9].sex, "M"); DATA[9].age = 20;
    DATA[10].key = 75; strcpy(DATA[10].name, "Zhao"); strcpy(DATA[10].sex, "M"); DATA[10].age = 20;
    DATA[11].key = 92; strcpy(DATA[11].name, "Chen"); strcpy(DATA[11].sex, "M"); DATA[11].age = 20;


    for (int i=1; i<=n; i++) {
        ST.elem[i].key = DATA[i].key;
        ST.elem[i].name = DATA[i].name;
        ST.elem[i].sex = DATA[i].sex;
        ST.elem[i].age = DATA[i].age;
    }
}

// 遍历函数
void TraversSSTable(SSTable ST) {
    printf("学号\t姓名\t性别\t年龄\n");
    for (int i=1; i<=ST.length; i++) {
        printf("%d\t%s\t%s\t%d\n", ST.elem[i].key, ST.elem[i].name, ST.elem[i].sex, ST.elem[i].age);
    }
}

// 创建动态查找表
int InsertDSTable_BST(BSTree &DT, RecordType e) {
    BSTree p = DT;
    BSTree s = NULL;
    while (p) {// 查找插入位置，s指向p的前驱
        s = p;
        if (e.key == p->data.key) return FALSE;
        if (e.key < p->data.key) p = p->lchild;
        else p = p->rchild;
    }
    p = (BSTree)malloc(sizeof(BSTNode));
    p->data = e;
    p->lchild = p->rchild = NULL;
    if (!DT) DT = p;
    else if (e.key < s->data.key) s->lchild = p;
    else s->rchild = p;
    return OK;
}

// 创建动态查找表
void CreateDSTable_BST(BSTree &DT, SSTable &ST) {
    for (int i=1; i<=ST.length; i++) {
        InsertDSTable_BST(DT, ST.elem[i]);
    }
}

// 中序遍历
void TraversDSTable_InOrder(BSTree DT) {
    if (DT) {
        TraversDSTable_InOrder(DT->lchild);
        printf("%d\t%s\t%s\t%d\n", DT->data.key, DT->data.name, DT->data.sex, DT->data.age);
        TraversDSTable_InOrder(DT->rchild);
    }
}

// 查找(非递归)
int count = 0;
BSTree SearchDSTable_BST1(BSTree DT, KeyType key) {
	BSTree p = DT;
	while (p) {
		count++;
		if (key == p->data.key) return p;
		if (key < p->data.key) p = p->lchild;
		else p = p->rchild;
	}
	return NULL;
}

// 查找(递归)
BSTree SearchDSTable_BST2(BSTree DT, KeyType key) {
	if (!DT) return NULL;
	count++;
	if (key == DT->data.key) return DT;
	if (key < DT->data.key) return SearchDSTable_BST2(DT->lchild, key);
	else return SearchDSTable_BST2(DT->rchild, key);
}

// 输出
void OutElem_BST(BSTree p) {
	printf("学号\t姓名\t性别\t年龄\n");
	printf("%d\t%s\t%s\t%d\n", p->data.key, p->data.name, p->data.sex, p->data.age);
}

// Input
void InputElem(RecordType &e) {
    char name[50];
    char sex[10];
    scanf("%d", &e.key);
	if (e.key == -1) return;
	scanf("%s %s %d", name,sex,&e.age);
	e.name = strdup(name);
	e.sex = strdup(sex);
}

// 删除
int DeleteDSTable_BST(BSTree &DT, KeyType key) {
    BSTree p = DT;
    BSTree f = NULL;
    BSTree s = NULL;
    while (p) {// 查找删除位置,f指向p的前驱
        if (key == p->data.key) break;
        f = p;
        if (key < p->data.key) p = p->lchild;
        else p = p->rchild;
    }
    if (!p) return FALSE;// 未找到
    if (!p->lchild) {// 无左子树
        if (!f) DT = p->rchild;// 根结点
        else if (f->lchild == p) f->lchild = p->rchild;
        else f->rchild = p->rchild;
        free(p);
    } else if (!p->rchild) {// 无右子树
        if (!f) DT = p->lchild;
        else if (f->lchild == p) f->lchild = p->lchild;
        else f->rchild = p->lchild;
        free(p);
    } else {
        s = p->lchild;
        f = p;
        while (s->rchild) {// 找到移除p前最大的结点s
            f = s;
            s = s->rchild;
        }
        p->data = s->data;
        if (f != p) f->rchild = s->lchild;// s的前驱f不是p
        else f->lchild = s->lchild;
        free(s);
    }
    return OK;
}

int main(){
	int i,key;
	int n=11;
	SSTable ST1;
	BSTree DT1,p;

	//创建静态查找表ST1 
	CreateSSTable(ST1,n);
	printf("\n静态查找表\n");
	TraversSSTable(ST1);

	//创建动态查找表DT1 
	CreateDSTable_BST(DT1,ST1);
	printf("\n动态查找表(中序遍历)\n");
	printf("学号 姓名 性别 年龄\n");
	TraversDSTable_InOrder(DT1);

	//查找动态查找表元素 
	printf("\n---元素查找---\n");
	printf("\n请输入要查找记录的学号(输入-1结束)："); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0;
		p=SearchDSTable_BST2(DT1,key);
		if(!p)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem_BST(p); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",count);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	} 

	int total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchDSTable_BST1(DT1, ST1.elem[i].key);
		total=total+count;
	}
	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchDSTable_BST1(DT1,4);
		else SearchDSTable_BST1(DT1,ST1.elem[i].key+1);
		total=total+count;
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));

	//构造动态查找表（插入新元素 ） 
	printf("\n---元素插入---\n");
	RecordType e;
	printf("\n请输入要插入的新记录(输入-1结束)\n学号 姓名 性别 年龄\n");
	InputElem(e); 
	while (e.key!=-1) {
		if(InsertDSTable_BST(DT1,e)){
			printf("\n插入元素后的动态查找表(中序遍历)\n");
			printf("学号 姓名 性别 年龄\n");
			TraversDSTable_InOrder(DT1);
		}
		else printf("当前要插入的记录已存在，禁止插入！\n");
		printf("\n请输入要插入的新记录(输入-1结束)\n学号 姓名 性别 年龄\n");
		InputElem(e); 
	}

	//删除动态查找表元素 
	printf("\n---元素删除---\n");
	printf("\n请输入要删除记录的学号(输入-1结束)："); 
	scanf("%d",&key); 
	while (key!=-1){
		if(DeleteDSTable_BST(DT1,key)){
			printf("\n删除元素后的动态查找表(中序遍历)\n");
			printf("学号 姓名 性别 年龄\n");
			TraversDSTable_InOrder(DT1);
		}
	    else printf("当前要删除的记录不存在！\n");
		printf("\n请输入要删除记录的学号(输入-1结束)："); //下一次删除 
		scanf("%d",&key); 
	} 

	return 1;
}