#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int KeyType;        //�ؼ��ֵ���������

//����Ԫ�أ���¼�������Ͷ���
typedef struct {
        KeyType  key;            //ѧ��(�ؼ���)
        const char *name;     //����
        const char *sex;         //�Ա� 
        int  age;                     //���� 
} RecordType;

//��̬���ұ�����Ͷ���
typedef struct {
        RecordType *Record;      //����Ԫ�ش洢�ռ�Ļ�ַ(һά������)
        int    length;             //��ĳ��ȣ�Ԫ�ظ�����
}SSTable;  

/*
2. ��̬���ұ����������ʵ��

���ݶ���Ĵ洢�ṹ����д���л�������������C/C++Դ���룺
��1����дһ��������̬���ұ�ĺ���CreateSSTable(SSTable &ST, int n)������nΪԪ�ظ����������ľ�̬���ұ���±�1��ʼ�������(0Ԫ�ؿ����������ڱ���)��
ע��Ϊ��߳�������ٶȣ��ú�������ֱ���ø�ֵ��佫������Ԫ�ص�ֵ�ԡ���������ʽ������̬���ұ�ĸ�������Ԫ�ء�
��2����дһ����������TraversSSTable(SSTable ST)�������̬���ұ�ST����������Ԫ�ء�
��3����дһ��˳����Һ��� int SearchSSTable_Seq(SSTable ST, KeyType key, int &c)�����в���keyΪҪ���ҵĹؼ��֣�����c������ҹ����йؼ��ֱȽϵĴ����������ҳɹ����������ظùؼ���Ԫ�����ڵ��±꣬���򣬲��Ҳ��ɹ�������0���С��ڱ�������-1���ޡ��ڱ�������
��4����дһ��������SortSSTable(SSTable &ST)������̬���ұ���������Ԫ�ذ��ؼ��ִ�С���������������
��5����дһ���۰���Һ��� int SearchSSTable_Bin(SSTable ST, KeyType key, int &c)�����в���keyΪҪ���ҵĹؼ��֣�����c������ҹ����йؼ��ֱȽϵĴ����������ҳɹ����������ظùؼ���Ԫ�����ڵ��±꣬���򣬲��Ҳ��ɹ�������-1��

3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1������һ����̬���ұ�ST1�������и�Ԫ�ص�ֵд��ST1��Ȼ�����ST1�ĸ�Ԫ�ص�ֵ��
    ѧ��key	 ����name 	    �Ա�sex 	     ����age 
       64 	 Li 	        M 	        19 
       88 	 Liu 	         F 	        18 
       13 	 Qian 	         F 	        19 
       37 	 Sun 	        M 	        20 
       75 	 Zhao 	        M 	        20 
       92 	 Chen 	        M 	        20 
��2����дһ�δ��룬���������һ���ؼ��֣�˳����Ҿ�̬���е�����Ԫ�أ������ҳɹ�������ҵ���Ԫ�أ���¼����ֵ�͹ؼ��ֵıȽϴ����������������ǰҪ���ҵļ�¼�����ڣ����͹ؼ��ֵıȽϴ��������Ҳ��ɹ���ASL�����öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
��3������ʹ�þ�̬���ұ��еĹؼ��ֽ���˳����ң����㲢������ҳɹ���ASL��
��4������̬���ұ�ST1���ؼ��ֵ������򣬱��һ�������Ȼ����������ĸ�Ԫ�ص�ֵ��
��5����дһ�δ��룬���������һ���ؼ��֣��۰���Ҿ�̬���е�����Ԫ�أ������ҳɹ�������ҵ���Ԫ�أ���¼����ֵ�͹ؼ��ֵıȽϴ����������������ǰҪ���ҵļ�¼�����ڣ����͹ؼ��ֵıȽϴ������öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
��6������ʹ�þ�̬���ұ��еĹؼ��ֽ����۰���ң����㲢������ҳɹ���ASL��
��7��ѡ��ʹ�ò��ھ�̬���ұ��еĹؼ��ֽ����۰���ң����㲢������Ҳ��ɹ���ASL��

��¼��main()����

int main(){
	int i,key;
	int n=10;
	int c,total;
	SSTable ST1;

	//������̬���ұ�ST1 
	CreateSSTable(ST1,n);
	printf("\nѧ������ľ�̬���ұ�\n");
	TraversSSTable(ST1);

	printf("---˳�����---\n");
	printf("\n������Ҫ���ҵ�ѧ�ţ�"); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Seq(ST1,key);
		if(i==0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem(ST1,i); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",n-i+1);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	}
	printf("\n˳����Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		c=SearchSSTable_Seq(ST1,ST1.elem[i].key);
		total=total+ST1.length-c+1;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.elem[i].key,ST1.length-c+1);
	}

	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)ST1.length+1);

	//���ұ����� 
	SortSSTable(ST1);
	printf("\nѧ������ľ�̬���ұ�\n");
	TraversSSTable(ST1);

	//* 
	printf("---�۰����(�ǵݹ�)---\n"); 
	printf("\n������Ҫ���ҵ�ѧ�ţ�"); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Bin(ST1,key,c);
		if(i==0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem(ST1,i); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",c);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	}

	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");
	total=0;
	for(i=1;i<=ST1.length;i++){
		SearchSSTable_Bin(ST1,ST1.elem[i].key,c);
		total=total+c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.elem[i].key,c);
	}
	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		if(i==0) SearchSSTable_Bin(ST1,4,c);
		else SearchSSTable_Bin(ST1,ST1.elem[i].key+1,c);
		total=total+c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",(i==0)?4:ST1.elem[i].key+1,c);
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));

    // !
	printf("---�۰����(�ݹ�)---\n"); 
	printf("\n������Ҫ���ҵ�ѧ�ţ�"); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0; 
		i=SearchSSTable_Bin1(ST1,key,1,ST1.length);
		if(i==0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem(ST1,i); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",count);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	}
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchSSTable_Bin1(ST1,ST1.elem[i].key,1,ST1.length);
		total=total+count;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.elem[i].key,count);
	}
	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchSSTable_Bin1(ST1,4,1,ST1.length);
		else SearchSSTable_Bin1(ST1,ST1.elem[i].key+1,1,ST1.length);
		total=total+count;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",(i==0)?4:ST1.elem[i].key+1,count);
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));

	return 1;
}
*/

// ��ӽṹ�嶨��
typedef struct {
    int key;
    char name[20];
    char sex[2];
    int age;
} DATA_TYPE;

// ����ȫ������
DATA_TYPE DATA[12];

//������̬���ұ�
int CreateSSTable(SSTable &ST, int n){
    ST.Record = (RecordType *)malloc((n+1)*sizeof(RecordType));
    if(!ST.Record) exit(OVERFLOW);
    ST.length = n;

// ��ʼ������Ԫ��
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

//��������
void TraversSSTable(SSTable ST){
	printf("ѧ��\t����\t�Ա�\t����\n");
    for (int i = 1; i <= ST.length; i++) {
		printf("%d\t%s\t%s\t%d\n", ST.Record[i].key, ST.Record[i].name, ST.Record[i].sex, ST.Record[i].age);
	}
}

//˳�����
int SearchSSTable_Seq(SSTable ST, KeyType key){
	ST.Record[0].key = key;
	int i = ST.length;
	while (ST.Record[i].key != key) {
		i--;
	}
	return i;
}

//����
void SortSSTable(SSTable &ST){
	RecordType temp;
	for (int i = 1; i < ST.length; i++) {// ѡ������, ��С����
		for (int j = i+1; j <= ST.length; j++) {
			if (ST.Record[i].key > ST.Record[j].key) {
				temp = ST.Record[i];
				ST.Record[i] = ST.Record[j];
				ST.Record[j] = temp;
			}
		}
	}
}

//�۰����
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
	printf("ѧ��\t����\t�Ա�\t����\n");
	printf("%d\t%s\t%s\t%d\n", ST.Record[i].key, ST.Record[i].name, ST.Record[i].sex, ST.Record[i].age);
}

int main(){
	int i,key;
	int n=10;
	int c,total;
	SSTable ST1;

	//������̬���ұ�ST1 
	CreateSSTable(ST1,n);
	printf("\nѧ������ľ�̬���ұ�\n");
	TraversSSTable(ST1);

	printf("---˳�����---\n");
	printf("\n������Ҫ���ҵ�ѧ�ţ�"); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Seq(ST1,key);
		if(i==0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem(ST1,i); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",n-i+1);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	}
	printf("\n˳����Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		c=SearchSSTable_Seq(ST1,ST1.Record[i].key);
		total=total+ST1.length-c+1;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.Record[i].key,ST1.length-c+1);
	}

	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)ST1.length+1);

	//���ұ����� 
	SortSSTable(ST1);
	printf("\nѧ������ľ�̬���ұ�\n");
	TraversSSTable(ST1);

	printf("---�۰����(�ǵݹ�)---\n"); 
	printf("\n������Ҫ���ҵ�ѧ�ţ�"); 
	scanf("%d",&key); 
	while (key!=-1){
		i=SearchSSTable_Bin(ST1,key,c);
		if(i==0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem(ST1,i); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",c);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	}

	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");
	total=0;
	for(i=1;i<=ST1.length;i++){
		SearchSSTable_Bin(ST1,ST1.Record[i].key,c);
		total=total+c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.Record[i].key,c);
	}
	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n�۰���Ҹ�����ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		if(i==0) SearchSSTable_Bin(ST1,4,c);
		else SearchSSTable_Bin(ST1,ST1.Record[i].key+1,c);
		total=total+c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",(i==0)?4:ST1.Record[i].key+1,c);
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));

    /*
	printf("---�۰����(�ݹ�)---\n"); 
	printf("\n������Ҫ���ҵ�ѧ�ţ�"); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0; 
		i=SearchSSTable_Bin1(ST1,key,1,ST1.length);
		if(i==0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem(ST1,i); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",count);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	}
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchSSTable_Bin1(ST1,ST1.elem[i].key,1,ST1.length);
		total=total+count;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.elem[i].key,count);
	}
	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchSSTable_Bin1(ST1,4,1,ST1.length);
		else SearchSSTable_Bin1(ST1,ST1.elem[i].key+1,1,ST1.length);
		total=total+count;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",(i==0)?4:ST1.elem[i].key+1,count);
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));
	*/

	return 1;
}