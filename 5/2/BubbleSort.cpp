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

typedef int KeyType;          //定义关键字类型为整数类型
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

int ccount,mcount;	        //全局变量，ccount关键字比较次数，mcount记录移到次数 

/*
2. 基本操作函数的实现
根据定义的记录表存储结构，编写下列基本操作函数的C/C++源代码：
（1）编写一个创建待排序记录表的函数CreateRecordTable(RecordTable &RT)，创建的记录表保留“哨兵”，即记录从下标=1的数组元素开始存放。
注：待排序记录数据的可以直接放在该函数中。参照实验4-1的静态查找表的创建方法和记录数据。
（2）编写一个输出函数OutRecordTable(RecordTable RT)，输出排序表RT的所有记录。
（3）编写一个简单交换（冒泡）排序函数 BubbleSort(RecordTable &RT)，将记录表RT中原来无序的记录按记录关键字值作正序排序，并利用全局变量ccount和mcount计算排序过程中关键字的比较次数和记录的交换次数。
（4）编写一个快速排序函数QuickSort(RecordTable &RT, int low, int high)，将记录表RT中原来无序的记录按记录关键字值作正序排序，参数low和high表示排序记录的下标范围，并利用全局变量ccount和mcount计算排序过程中关键字的比较次数和记录的交换次数。同时输出每一次划分的序号和划分后的记录表内容（可以利用全局变量pcount计算划分的次数）。

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
（2）调用 BubbleSort()函数对RT1进行记录排序，然后调用OutRecordTable()函数输出排序后RT1的各记录的数据、关键字比较次数和记录移到次数。
（3）调用CreateRecordTable()函数恢复待排序记录表RT1，调用QuickSort()函数对RT1进行记录排序，然后调用OutRecordTable()函数输出排序后RT1的各记录的数据、关键字比较次数和记录移到次数。
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

//冒泡排序
void BubbleSort(RecordTable &RT){
    int i, j;
    RecordType temp;
    int ccount = 0, mcount = 0;
    for (i = 1; i < RT.length; i++) {
        for (j = 1; j <= RT.length - i; j++) {
            if (RT.r[j].key > RT.r[j + 1].key) {
                temp = RT.r[j];
                RT.r[j] = RT.r[j + 1];
                RT.r[j + 1] = temp;
                mcount++;
            }
            ccount++;
        }
    }
    printf("冒泡排序后的记录表：\n");
    OutRecordTable(RT);
    printf("关键字比较次数：%d\n", ccount);
    printf("记录交换次数：%d\n", mcount);
}

//（4）编写一个快速排序函数QuickSort(RecordTable &RT, int low, int high)，将记录表RT中原来无序的记录按记录关键字值作正序排序，参数low和high表示排序记录的下标范围，并利用全局变量ccount和mcount计算排序过程中关键字的比较次数和记录的交换次数。同时输出每一次划分的序号和划分后的记录表内容（可以利用全局变量pcount计算划分的次数）。
void QuickSort(RecordTable &RT, int low, int high){
    int i = low, j = high;
    RecordType temp;
    if (low < high) {
        temp = RT.r[low];
        while (i < j) {
            while (i < j && RT.r[j].key >= temp.key) {
                j--;
            }
            if (i < j) {
                RT.r[i] = RT.r[j];
                i++;
            }
            while (i < j && RT.r[i].key < temp.key) {
                i++;
            }
            if (i < j) {
                RT.r[j] = RT.r[i];
                j--;
            }
        }
        RT.r[i] = temp;
        printf("第%d次划分后的记录表：\n", ++ccount);
        OutRecordTable(RT);
        QuickSort(RT, low, i - 1);
        QuickSort(RT, i + 1, high);
    }
}

int main(){
    RecordTable RT1;
    //创建顺序表RT1
    CreateRecordTable(RT1);
    //输出顺序表RT1
    printf("顺序表RT1：\n");
    OutRecordTable(RT1);
    //冒泡排序
    BubbleSort(RT1);
    //快速排序
    CreateRecordTable(RT1);
    QuickSort(RT1, 1, RT1.length);
    printf("快速排序后的记录表：\n");
    OutRecordTable(RT1);
    return 1;
}