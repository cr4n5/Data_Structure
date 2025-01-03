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

#define MAXSIZE 20         //�ļ��м�¼���������ֵ

typedef int KeyType;          //����ؼ�������Ϊ��������
//��¼����
typedef struct  {
        KeyType  key;             //ѧ�ţ���¼�Ĺؼ��֣�
        const char *name;     //����
        const char *sex;         //�Ա� 
        int  age;                     //���� 
} RecordType;                     

//��¼�������
typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]���û��������ڱ�����Ԫ
          int length;                                  //��¼�ĸ���
}RecordTable;                                     

int ccount,mcount;	        //ȫ�ֱ�����ccount�ؼ��ֱȽϴ�����mcount��¼�Ƶ����� 

/*
2. ��������������ʵ��
���ݶ���ļ�¼��洢�ṹ����д���л�������������C/C++Դ���룺
��1����дһ�������������¼��ĺ���CreateRecordTable(RecordTable &RT)�������ļ�¼�������ڱ���������¼���±�=1������Ԫ�ؿ�ʼ��š�
ע���������¼���ݵĿ���ֱ�ӷ��ڸú����С�����ʵ��4-1�ľ�̬���ұ�Ĵ��������ͼ�¼���ݡ�
��2����дһ���������OutRecordTable(RecordTable RT)����������RT�����м�¼��
��3����дһ���򵥽�����ð�ݣ������� BubbleSort(RecordTable &RT)������¼��RT��ԭ������ļ�¼����¼�ؼ���ֵ���������򣬲�����ȫ�ֱ���ccount��mcount������������йؼ��ֵıȽϴ����ͼ�¼�Ľ���������
��4����дһ������������QuickSort(RecordTable &RT, int low, int high)������¼��RT��ԭ������ļ�¼����¼�ؼ���ֵ���������򣬲���low��high��ʾ�����¼���±귶Χ��������ȫ�ֱ���ccount��mcount������������йؼ��ֵıȽϴ����ͼ�¼�Ľ���������ͬʱ���ÿһ�λ��ֵ���źͻ��ֺ�ļ�¼�����ݣ���������ȫ�ֱ���pcount���㻮�ֵĴ�������

3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1������һ�������RT1������CreateRecordTable()���������������¼��RT1�������и���¼������д��RT1��Ȼ�����OutRecordTable()�������RT1�ĸ���¼�����ݡ�
    ѧ��key	 ����name 	   �Ա�sex    ����age 
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
��2������ BubbleSort()������RT1���м�¼����Ȼ�����OutRecordTable()������������RT1�ĸ���¼�����ݡ��ؼ��ֱȽϴ����ͼ�¼�Ƶ�������
��3������CreateRecordTable()�����ָ��������¼��RT1������QuickSort()������RT1���м�¼����Ȼ�����OutRecordTable()������������RT1�ĸ���¼�����ݡ��ؼ��ֱȽϴ����ͼ�¼�Ƶ�������
*/

Status CreateRecordTable(RecordTable &L) {	//����˳��� 
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

Status OutRecordTable(RecordTable L){ 	//���˳���ĸ�����¼
	int i;
	printf("ѧ�� ���� �Ա� ����\n");
	for(i=1;i<=L.length;i++){
		printf(" %2d ",L.r[i].key);
		printf("%5s   ",L.r[i].name);
		printf("%1s   ",L.r[i].sex);
		printf("%2d\n",L.r[i].age);
	}
}

//ð������
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
    printf("ð�������ļ�¼��\n");
    OutRecordTable(RT);
    printf("�ؼ��ֱȽϴ�����%d\n", ccount);
    printf("��¼����������%d\n", mcount);
}

//��4����дһ������������QuickSort(RecordTable &RT, int low, int high)������¼��RT��ԭ������ļ�¼����¼�ؼ���ֵ���������򣬲���low��high��ʾ�����¼���±귶Χ��������ȫ�ֱ���ccount��mcount������������йؼ��ֵıȽϴ����ͼ�¼�Ľ���������ͬʱ���ÿһ�λ��ֵ���źͻ��ֺ�ļ�¼�����ݣ���������ȫ�ֱ���pcount���㻮�ֵĴ�������
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
        printf("��%d�λ��ֺ�ļ�¼��\n", ++ccount);
        OutRecordTable(RT);
        QuickSort(RT, low, i - 1);
        QuickSort(RT, i + 1, high);
    }
}

int main(){
    RecordTable RT1;
    //����˳���RT1
    CreateRecordTable(RT1);
    //���˳���RT1
    printf("˳���RT1��\n");
    OutRecordTable(RT1);
    //ð������
    BubbleSort(RT1);
    //��������
    CreateRecordTable(RT1);
    QuickSort(RT1, 1, RT1.length);
    printf("���������ļ�¼��\n");
    OutRecordTable(RT1);
    return 1;
}