#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define SUCCESS        1        //���ҳɹ�     
#define UNSUCCESS   0        //���Ҳ��ɹ�

typedef int KeyType;             //�ؼ��ֵ���������

 //������̽����ɢ�С���ϣ������Ͷ���
typedef struct {                 
        KeyType *key;        //��ϣ��Ļ�ַ��һά���飬����Ԫ��ֻ��һ���ؼ��֣�
        int count;               //Ԫ�ظ���
        int size;                   //��ϣ��ĳ���
} HashTable;

//������ַ������ͬ��ʽ������Ͷ���
typedef struct KeyNode {    
        KeyType key;                //����Ԫ�صĹؼ���
        struct KeyNode *next;  //ָ����һ��ͬ��ʽ���ָ��
}KeyNode, *KeyLink;

//������ַ������ϣ������Ͷ��� 
typedef struct {
        KeyLink *head;   //��ϣ��Ļ�ַ��һάָ�����飬ÿ��Ԫ����ͬ��ʵ������ͷָ�룩
        int count;            //Ԫ�ظ���
        int size;                //��ϣ��ĳ��ȣ���ϣ�������������������ĳ�����
}HashLink;

//��ϣ����
int Hash(KeyType key){
        return key % 13;  //����������
}

/*
2. ������̽����ɢ�С���ϣ�����������ʵ��

��1����дһ��������ϣ��ĺ�����������ʽ���£�
        CreateHashTable(HashTable &HT, int HT_Length, KeyType key[], int KeyNum)

��������˵�����£� 
HashTable &HT�� ��ϣ���������Ź�ϣ����������
int HT_Length�� ��ϣ��ĳ��� 
KeyType key[]����Źؼ��ֵ�һά����
int KeyNum���ؼ��ָ���

�ú����Ĺ�ϣ����Ϊ Hash(key)=key % 13����Hash(key)��ֵΪ�±꽫�ؼ��ִ����ϣ��HT�е�key�����У�����ͬ��ʣ�����á�����̽����ɢ�С����������Źؼ��ֵ��±ꡣû�д�Źؼ��ֵ�����Ԫ����-1��ʾ��

��2����дһ����ϣ���Һ�����������ʽ���£�
        SearchHashTable(HashTable HT, KeyType key, int &p, int &c)

��������˵�����£� 
HashTable HT�� ��ϣ���������Ź�ϣ����������
KeyType key��Ҫ���ҵĹؼ���
int &p�������ҳɹ�����ʾ�ؼ����ڹ�ϣ���е��±꣬����p=-1
int &c���ؼ��ֱȽϵĴ���

�ú������ݲ���key�ڹ�ϣ���в��Ҹùؼ��֣������ҳɹ�������SUCCESS�����򷵻�UNSUCCESS��

3. ������ַ������ϣ�����������ʵ��
��1����дһ��������ϣ��ĺ�����������ʽ���£�
        CreateHashLink(HashLink &HL, int HL_Length, KeyType key[], int KeyNum)

��������˵�����£� 
HashLink  &HL�� ��ϣ���������Ź�ϣ����������
int HL_Length�� ��ϣ��ĳ��ȣ���ϣ�������������������ĳ�����
KeyType key[]����Źؼ��ֵ�һά����
int KeyNum���ؼ��ָ���

�ú����Ĺ�ϣ����Ϊ Hash(key)=key % 13��ͬ��ʲ��뵽��Hash(key)Ϊ�±�ĵ������У�����ͷ�巨����

��2����дһ����ϣ���Һ�����������ʽ���£�
        SearchHashLink(HashLink HL, KeyType key, KeyLink &p, int &c)

��������˵�����£� 
HashLink  &HL�� ��ϣ���������Ź�ϣ����������
KeyType key��Ҫ���ҵĹؼ���
KeyLink &p�������ҳɹ���ָ����ҹؼ��ֽ���ָ�룬����p=NULL
 int &c���ؼ��ֱȽϵĴ���
�ú������ݲ���key�ڹ�ϣ���в��Ҹùؼ����ڵ������еĽ�㣬�����ҳɹ�������SUCCESS�����򷵻�UNSUCCESS��

��3����дһ�������ϣ�����ݵĺ���OutHashLink(HashLink HL)�������ʽ��̲�P-225ͼ7.30��ʾ��

4. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����

��1������׼�������ݽ̲�p-224 ��7-2��p-227 ��7-3�����Ĺؼ��֣�����һ��һά����keys[]�洢��Щ�ؼ��֣��������Щ�ؼ��֡�
        int keys[12]={19,14,23,1,68,20,84,27,55,11,10,79};
��2������CreateHashTable(HT,16, keys, 12)��������һ��������̽����ɢ�С���ϣ��HT��Ȼ�������ϣ������ݡ�����7.3��
��3������ʹ��keys[]�����еĹؼ��ֵ���SearchHashTable()�������ڹ�ϣ��HT�в��ҹؼ��֣���������ؼ����ڹ�ϣ���е�λ�ã��±꣩�͹ؼ��ֵıȽϴ����������㲢��������ҳɹ���ASL��������7.3��
��4������CreateHashLink(HL,13, keys, 12)��������һ��������ַ������ϣ��HL��Ȼ�����OutHashLink(HL)���������ϣ��HL�����ݡ�����7.2��
��5������ʹ��keys[]�����еĹؼ��ֵ���SearchHashLink()�������ڹ�ϣ��HL�в��ҹؼ��֣���������ؼ����ڲ���ʱ�ؼ��ֵıȽϴ����������㲢������ҳɹ���ASL������7.2��
��6������һ��һά����keys1[13]���£�
        keys1[13]={26,40,15,29,30,18,32,46,60,74,36,24,38};
���еĹؼ��ֶ����ڹ�ϣ���У�ȡ���еĹؼ��ֶԹ�ϣ��HT��HL�����Ҳ�����������ֲ���ʱ�����ؼ��ֵġ��ؼ��ֱȽϴ�������Ȼ����㲢������ֹ�ϣ��ġ����Ҳ��ɹ���ASL����
*/


// 2. ������̽����ɢ�С���ϣ�����������ʵ��
// ������ϣ��
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

// ���ҹ�ϣ��
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

// 3. ������ַ������ϣ�����������ʵ��
// ������ϣ��
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
        p->key = key[i];// �����½��
        p->next = HL.head[addr];// ���뵽ͬ��������ͷ��
        HL.head[addr] = p;// ͷ�巨
        HL.count++;
    }
}

// ���ҹ�ϣ��
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

// �����ϣ������
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

	printf("�ؼ��ֱ�:\n");
	for(i=0;i<n;i++) printf("%2d ",keys[i]);
	CreateHashTable(HT, HT_Length, keys, n);

	printf("\n\n����̽����ɢ�й�ϣ��:\n");
	for(i=0;i<HT_Length;i++) printf("%d ",HT.key[i]);
	printf("\n");

	total=0;
	for(i=0;i<n;i++){
		printf("\n���ҹؼ���=%2d",keys[i]);
		SearchHashTable(HT, keys[i], j, k);
		total=total+k;
		printf("  ���ڹ�ϣ���±�=%2d",j);
		printf("  �ؼ��ֱȽϴ���=%2d",k);
	}
	printf("\n\n���ҳɹ�ASL=%f\n",(float)total/n);

	total=0;
	for(i=0;i<n1;i++){
		printf("\n���ҹؼ���=%2d",keys1[i]);
		SearchHashTable(HT, keys1[i], j, k);
		total=total+k;
		printf("  ���ڹ�ϣ���±�=%2d",j);
		printf("  �ؼ��ֱȽϴ���=%2d",k);
	}
	printf("\n\n���Ҳ��ɹ�ASL=%f\n",(float)total/n1);

	HashLink HL;
	KeyLink p;
	CreateHashLink(HL,13, keys, n);
	printf("\n����ַ����ϣ��:\n");
	OutHashLink(HL);

	total=0;
	for(i=0;i<n;i++){
		printf("\n���ҹؼ���=%2d",keys[i]);
		SearchHashLink(HL, keys[i], p, k);
		total=total+k;
		printf("  ���ڹ�ϣ���±�=%2d",(keys[i]) % 13);
		printf("  �ؼ��ֱȽϴ���=%2d",k);
	}
	printf("\n\n���ҳɹ�ASL=%f\n",(float)total/n);

	total=0;
	for(i=0;i<n1;i++){
		printf("\n���ҹؼ���=%2d",keys1[i]);
		SearchHashLink(HL, keys1[i], p, k);
		total=total+k;
		printf("  ���ڹ�ϣ���±�=%2d",(keys1[i]) % 13);
		printf("  �ؼ��ֱȽϴ���=%2d",k);
	}
	printf("\n\n���Ҳ��ɹ�ASL=%f\n",(float)total/n1);

	return 1;
}