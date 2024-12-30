#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define SUCCESS        1        //查找成功     
#define UNSUCCESS   0        //查找不成功

typedef int KeyType;             //关键字的数据类型

 //“线性探测再散列”哈希表的类型定义
typedef struct {                 
        KeyType *key;        //哈希表的基址（一维数组，数据元素只用一个关键字）
        int count;               //元素个数
        int size;                   //哈希表的长度
} HashTable;

//“链地址法”中同义词结点的类型定义
typedef struct KeyNode {    
        KeyType key;                //数据元素的关键字
        struct KeyNode *next;  //指向下一个同义词结点的指针
}KeyNode, *KeyLink;

//“链地址法”哈希表的类型定义 
typedef struct {
        KeyLink *head;   //哈希表的基址（一维指针数组，每个元素是同义词单链表的头指针）
        int count;            //元素个数
        int size;                //哈希表的长度（哈希函数“除留余数法”的除数）
}HashLink;

//哈希函数
int Hash(KeyType key){
        return key % 13;  //除留余数法
}

/*
2. “线性探测再散列”哈希表基本操作的实现

（1）编写一个创建哈希表的函数，函数格式如下：
        CreateHashTable(HashTable &HT, int HT_Length, KeyType key[], int KeyNum)

函数参数说明如下： 
HashTable &HT： 哈希表变量，存放哈希表的相关内容
int HT_Length： 哈希表的长度 
KeyType key[]：存放关键字的一维数组
int KeyNum：关键字个数

该函数的哈希函数为 Hash(key)=key % 13，以Hash(key)的值为下标将关键字存入哈希表HT中的key数组中，若有同义词，则采用“线性探测再散列”方法计算存放关键字的下标。没有存放关键字的数组元素用-1表示。

（2）编写一个哈希查找函数，函数格式如下：
        SearchHashTable(HashTable HT, KeyType key, int &p, int &c)

函数参数说明如下： 
HashTable HT： 哈希表变量，存放哈希表的相关数据
KeyType key：要查找的关键字
int &p：若查找成功，表示关键字在哈希表中的下标，否则p=-1
int &c：关键字比较的次数

该函数根据参数key在哈希表中查找该关键字，若查找成功，返回SUCCESS，否则返回UNSUCCESS。

3. “链地址法”哈希表基本操作的实现
（1）编写一个创建哈希表的函数，函数格式如下：
        CreateHashLink(HashLink &HL, int HL_Length, KeyType key[], int KeyNum)

函数参数说明如下： 
HashLink  &HL： 哈希表变量，存放哈希表的相关数据
int HL_Length： 哈希表的长度（哈希函数“除留余数法”的除数）
KeyType key[]：存放关键字的一维数组
int KeyNum：关键字个数

该函数的哈希函数为 Hash(key)=key % 13，同义词插入到以Hash(key)为下标的单链表中（采用头插法）。

（2）编写一个哈希查找函数，函数格式如下：
        SearchHashLink(HashLink HL, KeyType key, KeyLink &p, int &c)

函数参数说明如下： 
HashLink  &HL： 哈希表变量，存放哈希表的相关数据
KeyType key：要查找的关键字
KeyLink &p：若查找成功，指向查找关键字结点的指针，否则p=NULL
 int &c：关键字比较的次数
该函数根据参数key在哈希表中查找该关键字在单链表中的结点，若查找成功，返回SUCCESS，否则返回UNSUCCESS。

（3）编写一个输出哈希表数据的函数OutHashLink(HashLink HL)，输出格式如教材P-225图7.30所示。

4. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：

（1）数据准备：根据教材p-224 例7-2、p-227 例7-3给出的关键字，定义一个一维数组keys[]存储这些关键字，并输出这些关键字。
        int keys[12]={19,14,23,1,68,20,84,27,55,11,10,79};
（2）调用CreateHashTable(HT,16, keys, 12)函数创建一个“线性探测再散列”哈希表HT，然后输出哈希表的数据。（例7.3）
（3）依次使用keys[]数组中的关键字调用SearchHashTable()函数，在哈希表HT中查找关键字，输出各个关键字在哈希表中的位置（下标）和关键字的比较次数，最后计算并输出“查找成功的ASL”。（例7.3）
（4）调用CreateHashLink(HL,13, keys, 12)函数创建一个“链地址法”哈希表HL，然后调用OutHashLink(HL)函数输出哈希表HL的数据。（例7.2）
（5）依次使用keys[]数组中的关键字调用SearchHashLink()函数，在哈希表HL中查找关键字，输出各个关键字在查找时关键字的比较次数，最后计算并输出查找成功的ASL。（例7.2）
（6）定义一个一维数组keys1[13]如下：
        keys1[13]={26,40,15,29,30,18,32,46,60,74,36,24,38};
其中的关键字都不在哈希表中，取其中的关键字对哈希表HT和HL做查找操作，输出两种查找时各个关键字的“关键字比较次数”，然后计算并输出两种哈希表的“查找不成功的ASL”。
*/


// 2. “线性探测再散列”哈希表基本操作的实现
// 创建哈希表
void CreateHashTable(HashTable &HT, int HT_Length, KeyType key[], int KeyNum) {
    HT.key = (KeyType *)malloc(HT_Length * sizeof(KeyType));
    if (!HT.key) exit(OVERFLOW);
    HT.size = HT_Length;
    HT.count = 0;
    for (int i=0; i<HT_Length; i++) {
        HT.key[i] = -1;
    }
    for (int i=0; i<KeyNum; i++) {
        int addr = Hash(key[i]);
        if (HT.key[addr] == -1) {
            HT.key[addr] = key[i];
            HT.count++;
        } else {
            int j = 1;
            while (HT.key[(addr+j)%HT_Length] != -1) {
                j++;
            }
            HT.key[(addr+j)%HT_Length] = key[i];
            HT.count++;
        }
    }
}

// 查找哈希表
int SearchHashTable(HashTable HT, KeyType key, int &p, int &c) {
    p = -1;
    c = 0;
    int addr = Hash(key);
    while (HT.key[addr] != -1 && HT.key[addr] != key) {
        addr = (addr+1) % HT.size;
        c++;
    }
    if (HT.key[addr] == key) {
        p = addr;
        return SUCCESS;
    } else {
        return UNSUCCESS;
    }
}

// 3. “链地址法”哈希表基本操作的实现
// 创建哈希表
void CreateHashLink(HashLink &HL, int HL_Length, KeyType key[], int KeyNum) {
    HL.head = (KeyLink *)malloc(HL_Length * sizeof(KeyLink));
    if (!HL.head) exit(OVERFLOW);
    HL.size = HL_Length;
    HL.count = 0;
    for (int i=0; i<HL_Length; i++) {
        HL.head[i] = NULL;
    }
    for (int i=0; i<KeyNum; i++) {
        int addr = Hash(key[i]);
        KeyLink p = (KeyLink)malloc(sizeof(KeyNode));
        p->key = key[i];// 生成新结点
        p->next = HL.head[addr];// 插入到同义词链表的头部
        HL.head[addr] = p;// 头插法
        HL.count++;
    }
}

// 查找哈希表
int SearchHashLink(HashLink HL, KeyType key, KeyLink &p, int &c) {
    p = NULL;
    c = 0;
    int addr = Hash(key);
    KeyLink q = HL.head[addr];
    while (q) {
        c++;
        if (q->key == key) {
            p = q;
            return SUCCESS;
        }
        q = q->next;
    }
    return UNSUCCESS;
}

// 输出哈希表数据
void OutHashLink(HashLink HL) {
    for (int i=0; i<HL.size; i++) {
        printf("%d: ", i);
        KeyLink p = HL.head[i];
        while (p) {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }
}

int main(){
	int i,j,k,total;
	int keys[12]={19,14,23,1,68,20,84,27,55,11,10,79};
	int keys1[13]={26,40,15,29,30,18,32,46,60,74,36,24,38};
	int n=12,n1=13; 
	int HT_Length=16;
	HashTable HT;

	printf("关键字表:\n");
	for(i=0;i<n;i++) printf("%2d ",keys[i]);
	CreateHashTable(HT, HT_Length, keys, n);

	printf("\n\n线性探测再散列哈希表:\n");
	for(i=0;i<HT_Length;i++) printf("%d ",HT.key[i]);
	printf("\n");

	total=0;
	for(i=0;i<n;i++){
		printf("\n查找关键字=%2d",keys[i]);
		SearchHashTable(HT, keys[i], j, k);
		total=total+k;
		printf("  所在哈希表下标=%2d",j);
		printf("  关键字比较次数=%2d",k);
	}
	printf("\n\n查找成功ASL=%f\n",(float)total/n);

	total=0;
	for(i=0;i<n1;i++){
		printf("\n查找关键字=%2d",keys1[i]);
		SearchHashTable(HT, keys1[i], j, k);
		total=total+k;
		printf("  所在哈希表下标=%2d",j);
		printf("  关键字比较次数=%2d",k);
	}
	printf("\n\n查找不成功ASL=%f\n",(float)total/n1);

	HashLink HL;
	KeyLink p;
	CreateHashLink(HL,13, keys, n);
	printf("\n链地址法哈希表:\n");
	OutHashLink(HL);

	total=0;
	for(i=0;i<n;i++){
		printf("\n查找关键字=%2d",keys[i]);
		SearchHashLink(HL, keys[i], p, k);
		total=total+k;
		printf("  所在哈希表下标=%2d",(keys[i]) % 13);
		printf("  关键字比较次数=%2d",k);
	}
	printf("\n\n查找成功ASL=%f\n",(float)total/n);

	total=0;
	for(i=0;i<n1;i++){
		printf("\n查找关键字=%2d",keys1[i]);
		SearchHashLink(HL, keys1[i], p, k);
		total=total+k;
		printf("  所在哈希表下标=%2d",(keys1[i]) % 13);
		printf("  关键字比较次数=%2d",k);
	}
	printf("\n\n查找不成功ASL=%f\n",(float)total/n1);

	return 1;
}