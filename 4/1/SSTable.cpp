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

//静态查找表的类型定义
typedef struct {
        RecordType *Record;      //数据元素存储空间的基址(一维数组名)
        int    length;             //表的长度（元素个数）
}SSTable;  

/*
2. 静态查找表基本操作的实现

根据定义的存储结构，编写下列基本操作函数的C/C++源代码：
（1）编写一个创建静态查找表的函数CreateSSTable(SSTable &ST, int n)，其中n为元素个数。创建的静态查找表从下标1开始存放数据(0元素可以用作“哨兵”)。
注：为提高程序调试速度，该函数允许直接用赋值语句将各数据元素的值以“常量”形式赋给静态查找表的各个数组元素。
（2）编写一个遍历函数TraversSSTable(SSTable ST)，输出静态查找表ST的所有数据元素。
（3）编写一个顺序查找函数 int SearchSSTable_Seq(SSTable ST, KeyType key, int &c)，其中参数key为要查找的关键字，参数c保存查找过程中关键字比较的次数。若查找成功，函数返回该关键字元素所在的下标，否则，查找不成功，返回0（有“哨兵”）或-1（无“哨兵”）。
（4）编写一个排序函数SortSSTable(SSTable &ST)，将静态查找表所有数据元素按关键字大小递增排序（有序表）。
（5）编写一个折半查找函数 int SearchSSTable_Bin(SSTable ST, KeyType key, int &c)，其中参数key为要查找的关键字，参数c保存查找过程中关键字比较的次数。若查找成功，函数返回该关键字元素所在的下标，否则，查找不成功，返回-1。

3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）定义一个静态查找表ST1，将下列各元素的值写入ST1，然后输出ST1的各元素的值。
    学号key	 姓名name 	    性别sex 	     年龄age 
       64 	 Li 	        M 	        19 
       88 	 Liu 	         F 	        18 
       13 	 Qian 	         F 	        19 
       37 	 Sun 	        M 	        20 
       75 	 Zhao 	        M 	        20 
       92 	 Chen 	        M 	        20 
（2）编写一段代码，根据输入的一个关键字，顺序查找静态表中的数据元素，若查找成功，输出找到的元素（记录）的值和关键字的比较次数，否则输出“当前要查找的记录不存在！”和关键字的比较次数（查找不成功的ASL）。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
（3）依次使用静态查找表中的关键字进行顺序查找，计算并输出查找成功的ASL。
（4）将静态查找表ST1按关键字递增排序，变成一个有序表，然后输出有序表的各元素的值。
（5）编写一段代码，根据输入的一个关键字，折半查找静态表中的数据元素，若查找成功，输出找到的元素（记录）的值和关键字的比较次数，否则输出“当前要查找的记录不存在！”和关键字的比较次数。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
（6）依次使用静态查找表中的关键字进行折半查找，计算并输出查找成功的ASL。
（7）选择使用不在静态查找表中的关键字进行折半查找，计算并输出查找不成功的ASL。

附录：main()函数

int main(){
	int i,key;
	int n=10;
	int c,total;
	SSTable ST1;

	//创建静态查找表ST1 
	CreateSSTable(ST1,n);
	printf("\n学号无序的静态查找表\n");
	TraversSSTable(ST1);

	printf("---顺序查找---\n");
	printf("\n请输入要查找的学号："); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Seq(ST1,key);
		if(i==0)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem(ST1,i); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",n-i+1);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	}
	printf("\n顺序查找各关键字的比较次数：\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		c=SearchSSTable_Seq(ST1,ST1.elem[i].key);
		total=total+ST1.length-c+1;
		printf("关键字=%2d  比较次数=%d\n",ST1.elem[i].key,ST1.length-c+1);
	}

	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)ST1.length+1);

	//查找表排序 
	SortSSTable(ST1);
	printf("\n学号有序的静态查找表\n");
	TraversSSTable(ST1);

	//* 
	printf("---折半查找(非递归)---\n"); 
	printf("\n请输入要查找的学号："); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Bin(ST1,key,c);
		if(i==0)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem(ST1,i); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",c);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	}

	printf("\n折半查找各关键字的比较次数：\n");
	total=0;
	for(i=1;i<=ST1.length;i++){
		SearchSSTable_Bin(ST1,ST1.elem[i].key,c);
		total=total+c;
		printf("关键字=%2d  比较次数=%d\n",ST1.elem[i].key,c);
	}
	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n折半查找各关键字的比较次数：\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		if(i==0) SearchSSTable_Bin(ST1,4,c);
		else SearchSSTable_Bin(ST1,ST1.elem[i].key+1,c);
		total=total+c;
		printf("关键字=%2d  比较次数=%d\n",(i==0)?4:ST1.elem[i].key+1,c);
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));

    // !
	printf("---折半查找(递归)---\n"); 
	printf("\n请输入要查找的学号："); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0; 
		i=SearchSSTable_Bin1(ST1,key,1,ST1.length);
		if(i==0)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem(ST1,i); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",count);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	}
	printf("\n折半查找各关键字的比较次数：\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchSSTable_Bin1(ST1,ST1.elem[i].key,1,ST1.length);
		total=total+count;
		printf("关键字=%2d  比较次数=%d\n",ST1.elem[i].key,count);
	}
	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n折半查找各关键字的比较次数：\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchSSTable_Bin1(ST1,4,1,ST1.length);
		else SearchSSTable_Bin1(ST1,ST1.elem[i].key+1,1,ST1.length);
		total=total+count;
		printf("关键字=%2d  比较次数=%d\n",(i==0)?4:ST1.elem[i].key+1,count);
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));

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

//创建静态查找表
int CreateSSTable(SSTable &ST, int n){
    ST.Record = (RecordType *)malloc((n+1)*sizeof(RecordType));
    if(!ST.Record) exit(OVERFLOW);
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

    for (int i = 0; i <= n; i++) {
        ST.Record[i].key = DATA[i].key;
        ST.Record[i].name = DATA[i].name;
		ST.Record[i].sex = DATA[i].sex;
        ST.Record[i].age = DATA[i].age;
    }
    return OK;
}

//遍历函数
void TraversSSTable(SSTable ST){
	printf("学号\t姓名\t性别\t年龄\n");
    for (int i = 1; i <= ST.length; i++) {
		printf("%d\t%s\t%s\t%d\n", ST.Record[i].key, ST.Record[i].name, ST.Record[i].sex, ST.Record[i].age);
	}
}

//顺序查找
int SearchSSTable_Seq(SSTable ST, KeyType key){
	ST.Record[0].key = key;
	int i = ST.length;
	while (ST.Record[i].key != key) {
		i--;
	}
	return i;
}

//排序
void SortSSTable(SSTable &ST){
	RecordType temp;
	for (int i = 1; i < ST.length; i++) {// 选择排序, 从小到大
		for (int j = i+1; j <= ST.length; j++) {
			if (ST.Record[i].key > ST.Record[j].key) {
				temp = ST.Record[i];
				ST.Record[i] = ST.Record[j];
				ST.Record[j] = temp;
			}
		}
	}
}

//折半查找
int SearchSSTable_Bin(SSTable ST, KeyType key, int &c){
	int low = 1, high = ST.length, mid;
	c = 0;
	while (low <= high) {
		mid = (low + high) / 2;
		c++;
		if (ST.Record[mid].key == key) {
			return mid;
		} else if (ST.Record[mid].key > key) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return 0;
}

void OutElem(SSTable ST, int i){
	printf("学号\t姓名\t性别\t年龄\n");
	printf("%d\t%s\t%s\t%d\n", ST.Record[i].key, ST.Record[i].name, ST.Record[i].sex, ST.Record[i].age);
}

int main(){
	int i,key;
	int n=10;
	int c,total;
	SSTable ST1;

	//创建静态查找表ST1 
	CreateSSTable(ST1,n);
	printf("\n学号无序的静态查找表\n");
	TraversSSTable(ST1);

	printf("---顺序查找---\n");
	printf("\n请输入要查找的学号："); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Seq(ST1,key);
		if(i==0)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem(ST1,i); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",n-i+1);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	}
	printf("\n顺序查找各关键字的比较次数：\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		c=SearchSSTable_Seq(ST1,ST1.Record[i].key);
		total=total+ST1.length-c+1;
		printf("关键字=%2d  比较次数=%d\n",ST1.Record[i].key,ST1.length-c+1);
	}

	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)ST1.length+1);

	//查找表排序 
	SortSSTable(ST1);
	printf("\n学号有序的静态查找表\n");
	TraversSSTable(ST1);

	printf("---折半查找(非递归)---\n"); 
	printf("\n请输入要查找的学号："); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Bin(ST1,key,c);
		if(i==0)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem(ST1,i); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",c);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	}

	printf("\n折半查找各关键字的比较次数：\n");
	total=0;
	for(i=1;i<=ST1.length;i++){
		SearchSSTable_Bin(ST1,ST1.Record[i].key,c);
		total=total+c;
		printf("关键字=%2d  比较次数=%d\n",ST1.Record[i].key,c);
	}
	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n折半查找各错误关键字的比较次数：\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		if(i==0) SearchSSTable_Bin(ST1,4,c);
		else SearchSSTable_Bin(ST1,ST1.Record[i].key+1,c);
		total=total+c;
		printf("关键字=%2d  比较次数=%d\n",(i==0)?4:ST1.Record[i].key+1,c);
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));

    /*
	printf("---折半查找(递归)---\n"); 
	printf("\n请输入要查找的学号："); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0; 
		i=SearchSSTable_Bin1(ST1,key,1,ST1.length);
		if(i==0)
			printf("当前要查找的记录不存在！\n");
		else 
			OutElem(ST1,i); 		//输出找到的记录 
		printf("查找时比较的次数=%d\n",count);
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf("%d",&key); 
	}
	printf("\n折半查找各关键字的比较次数：\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchSSTable_Bin1(ST1,ST1.elem[i].key,1,ST1.length);
		total=total+count;
		printf("关键字=%2d  比较次数=%d\n",ST1.elem[i].key,count);
	}
	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n折半查找各关键字的比较次数：\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchSSTable_Bin1(ST1,4,1,ST1.length);
		else SearchSSTable_Bin1(ST1,ST1.elem[i].key+1,1,ST1.length);
		total=total+count;
		printf("关键字=%2d  比较次数=%d\n",(i==0)?4:ST1.elem[i].key+1,count);
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));
	*/

	return 1;
}