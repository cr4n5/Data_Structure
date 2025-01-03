#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;

#define MAXSIZE 20         //文件中记录个数的最大值

typedef int  KeyType;          //定义关键字类型为整数类型

//记录类型
typedef struct  {
        KeyType  key;             //学号（记录的关键字）
        const char *name;     //姓名
        const char *sex;         //性别 
        int  age;                     //年龄 
} RecordType;                     

//记录表的类型
typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]闲置或用作“哨兵”单元
          int length;                                  //记录的个数
}RecordTable;                                    

/*
2. 基本操作函数的实现

根据定义的记录表存储结构，编写下列基本操作函数的C/C++源代码：
（1）编写一个创建待排序记录表的函数CreateRecordTable(RecordTable &RT)，创建的记录表保留“哨兵”，即记录从下标=1的数组元素开始存放。
注：待排序记录数据的可以直接放在该函数中。参照实验4-1的静态查找表的创建方法和记录数据。
（2）编写一个输出函数OutRecordTable(RecordTable RT)，输出排序表RT的所有记录。
（3）编写一个简单插入排序函数 InsertSort(RecordTable &RT)，将记录表RT中原来无序的记录按记录关键字值作正序排序，并利用全局变量ccount和mcount计算排序过程中关键字的比较次数和记录的移动次数（注：记录移到“哨兵”和从“哨兵”移回不算移动）。
（4）编写一个Shell排序函数ShellSort(RecordTable &RT)，将记录表RT中原来无序的记录按记录关键字值作正序排序，并利用全局变量ccount和mcount计算排序过程中关键字的比较次数和记录的移动次数。同时输出每一趟Shell排序后的记录表内容（即对每个d输出一次）。

3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
（1）定义一个排序表RT1，调用CreateRecordTable()函数创建待排序记录表RT1，将下列各记录的数据写入RT1，然后调用OutRecordTable()函数输出RT1的各记录的数据。
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
（2）调用 InsertSort()函数对RT1进行记录排序，然后调用OutRecordTable()函数输出排序后RT1的各记录的数据、关键字比较次数和记录移到次数。
（3）调用CreateRecordTable()函数恢复待排序记录表RT1，调用ShellSort()函数对RT1进行记录排序，然后调用OutRecordTable()函数输出排序后RT1的各记录的数据、关键字比较次数和记录移到次数。
附录：记录表创建与输出源码
Status CreateRecordTable(RecordTable &L) {	//创建顺序表 
	int keys[]={56,19,80, 5,21,64,88,13,37,75,92};
	//int keys[]={25,12,9,20,7,31,24,35,17,10,5};
	const char *names[]={"Zhang","Wang","ZHou","Huang","Zheng","Li","Liu","Qian","Sun","Zhao","Chen"};
	const char *sexs[]={"F","F","F","F","M","M","M","M","M","M","M"};
	int ages[]={19,18,19,18,19,20,20,19,18,19,18};
	int i,n=11;
	for(i=1;i<=n;i++){
		L.r[i].key=keys[i-1];
		L.r[i].name=names[i-1];
		L.r[i].sex=sexs[i-1];
		L.r[i].age=ages[i-1];
	}
	L.length=n;
	return OK;	
}

Status OutRecordTable(RecordTable L){ 	//输出顺序表的各个记录
	int i;
	printf("学号 姓名 性别 年龄\n");
	for(i=1;i<=L.length;i++){
		printf(" %2d ",L.r[i].key);
		printf("%5s   ",L.r[i].name);
		printf("%1s   ",L.r[i].sex);
		printf("%2d\n",L.r[i].age);
	}
}
*/


Status CreateRecordTable(RecordTable &L) {	//创建顺序表 
	int keys[]={56,19,80, 5,21,64,88,13,37,75,92};
	//int keys[]={25,12,9,20,7,31,24,35,17,10,5};
	const char *names[]={"Zhang","Wang","ZHou","Huang","Zheng","Li","Liu","Qian","Sun","Zhao","Chen"};
	const char *sexs[]={"F","F","F","F","M","M","M","M","M","M","M"};
	int ages[]={19,18,19,18,19,20,20,19,18,19,18};
	int i,n=11;
	for(i=1;i<=n;i++){
		L.r[i].key=keys[i-1];
		L.r[i].name=names[i-1];
		L.r[i].sex=sexs[i-1];
		L.r[i].age=ages[i-1];
	}
	L.length=n;
	return OK;	
}

Status OutRecordTable(RecordTable L){ 	//输出顺序表的各个记录
	int i;
	printf("学号 姓名 性别 年龄\n");
	for(i=1;i<=L.length;i++){
		printf(" %2d ",L.r[i].key);
		printf("%5s   ",L.r[i].name);
		printf("%1s   ",L.r[i].sex);
		printf("%2d\n",L.r[i].age);
	}
}

//简单插入排序
void InsertSort(RecordTable &RT){
    int i, j;
    RecordType temp;
    int ccount = 0, mcount = 0;
    for (i = 2; i <= RT.length; i++) {
        if (RT.r[i].key < RT.r[i - 1].key) {
            temp = RT.r[i];
            RT.r[0] = RT.r[i];
            for (j = i - 1; RT.r[0].key < RT.r[j].key; j--) {
                RT.r[j + 1] = RT.r[j];
                mcount++;
                ccount++;
            }
            RT.r[j + 1] = temp;
            mcount++;
        }
    }
    printf("插入排序后的记录表：\n");
    OutRecordTable(RT);
    printf("关键字比较次数：%d\n", ccount);
    printf("记录移动次数：%d\n", mcount);
}

//希尔排序
void ShellSort(RecordTable &RT){
    int i, j, k;
    RecordType temp;
    int ccount = 0, mcount = 0;
    int increment = RT.length;
    do {
        increment = increment / 3 + 1;
        for (i = increment + 1; i <= RT.length; i++) {
            if (RT.r[i].key < RT.r[i - increment].key) {
                temp = RT.r[i];
                RT.r[0] = RT.r[i];
                for (j = i - increment; j > 0 && RT.r[0].key < RT.r[j].key; j -= increment) {
                    RT.r[j + increment] = RT.r[j];
                    mcount++;
                    ccount++;
                }
                RT.r[j + increment] = temp;
                mcount++;
            }
        }
        printf("增量为%d的排序结果：\n", increment);
        OutRecordTable(RT);
    } while (increment > 1);
    printf("希尔排序后的记录表：\n");
    OutRecordTable(RT);
    printf("关键字比较次数：%d\n", ccount);
    printf("记录移动次数：%d\n", mcount);
}

int main(){
    RecordTable RT1;
    CreateRecordTable(RT1);
    printf("待排序记录表RT1：\n");
    OutRecordTable(RT1);
    InsertSort(RT1);
    CreateRecordTable(RT1);
    ShellSort(RT1);
    return 1;
}

