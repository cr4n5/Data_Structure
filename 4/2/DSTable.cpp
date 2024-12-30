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

//��̬���ұ�BST�����Ͷ���
typedef  struct BSTNode {   
        RecordType  data;
        struct BSTNode *lchild, *rchild; //ָ�����Һ��ӽ���ָ��
}BSTNode, *BSTree;

/*
2. ��̬���ұ����������ʵ��

���ݶ���Ĵ洢�ṹ����д���л�������������C/C++Դ���룺
��1����дһ�����뺯��InsertDSTable_BST(BSTree &DT, RecordType e)������BST�����ʽ�����Ԫ��e���뵽��̬���ұ�DT�С���Ԫ��e��DT���Ѵ��ڣ������ʧ�ܣ�����FALSE��
��2����дһ��������̬���ұ�ĺ���CreateDSTable_BST(BSTree &DT, SSTable &ST)������STΪʵ��4-1�������ľ�̬���ұ��ú���Ҫ����InsertDSTable_BST()������
ע��Ϊ��߳�������ٶȣ��ú�������ֱ����ʵ��4-1�������ľ�̬���ұ�ST1�е�����Ԫ�ء�
��3����дһ�������������TraversDSTable_InOrde(BSTree DT)�������̬���ұ�DT����������Ԫ�ء�
��4����дһ�����Һ��� BSTree SearchDSTable_BST(BSTree DT, KeyType key)�����в���keyΪҪ����Ԫ�صĹؼ��֡������ҳɹ����������ظùؼ���Ԫ�ؽ��ĵ�ַ��ָ�룩�����򣬲��Ҳ��ɹ�������NULL���ú��������õݹ��ǵݹ鷽ʽʵ�֣�ͬʱҪ�������ҹ����йؼ��ֱȽϵĴ������ݹ麯��������ȫ�ֱ���ʵ�֣���
��5����дһ��ɾ������ DeleteDSTable_BST(BSTree &DT, KeyType key)�����в���keyΪҪɾ��Ԫ�صĹؼ��֣����ùؼ��ֵ�Ԫ����DT�в����ڣ������ʧ�ܣ�����FALSE��

3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
��1������һ����̬���ұ�ST1�������и�Ԫ�ص�ֵд��ST1��Ȼ�����ST1�ĸ�Ԫ�ص�ֵ��������Ͷ���Ͳ���������ֱ������ʵ��4-1.
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
��2������һ����̬���ұ�DT1������CreateDSTable_BST(DT1,ST1)���������ݾ�̬���ұ�ST1�е�����Ԫ�ش�����̬���ұ�DT1��Ȼ�����TraversDSTable_InOrder(DT1)�������DT1�еĵ���������Ԫ�ء�
��3����дһ�δ��룬���������һ���ؼ��֣�����SearchDSTable_BST()���������Ҷ�̬���е�����Ԫ�أ������ҳɹ�������ҵ���Ԫ�أ���¼����ֵ�͹ؼ��ֵıȽϴ����������������ǰҪ���ҵļ�¼�����ڣ����͹ؼ��ֵıȽϴ������öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
��4������ʹ�þ�̬���ұ�ST1�еĹؼ��ֵ���SearchDSTable_BST()���������Ҷ�̬���е�����Ԫ�أ����㲢������ҳɹ���ASL��
��5��ѡ��ʹ�ò��ھ�̬���ұ��еĹؼ��ֽ��в��ң����㲢������Ҳ��ɹ���ASL��
��6����дһ�δ��룬ʵ�ֶ�̬���ҵ�Ԫ�ز����������������(scanf)Ҫ����Ԫ��e�ĸ����������ֵ������InsertDSTable_BST(DT1, e)��Ԫ��e���뵽��̬���ұ��У�������ɹ�������TraversDSTable_InOrder(DT1)�������DT1�еĵ���������Ԫ�أ������������ǰҪ����ļ�¼�Ѵ��ڣ���ֹ���룡�����öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
��7����дһ�δ��룬ʵ�ֶ�̬���ҵ�Ԫ��ɾ����������������Ҫɾ��Ԫ�صĹؼ���ֵ������DeleteDSTable_BST(DT1, key)���ؼ���Ϊkey��Ԫ��e��DT1��ɾ������ɾ���ɹ�������TraversDSTable_InOrder(DT1)�������DT1�еĵ���������Ԫ�أ������������ǰҪɾ���ļ�¼�����ڣ���ֹɾ���������öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������

��¼��main()����
int main(){
	int i,key;
	int n=11;
	SSTable ST1;
	BSTree DT1,p;

	//������̬���ұ�ST1 
	CreateSSTable(ST1,n);
	printf("\n��̬���ұ�\n");
	TraversSSTable(ST1);

	//������̬���ұ�DT1 
	CreateDSTable_BST(DT1,ST1);
	printf("\n��̬���ұ�(�������)\n");
	printf("ѧ�� ���� �Ա� ����\n");
	TraversDSTable_InOrder(DT1);

	//���Ҷ�̬���ұ�Ԫ�� 
	printf("\n---Ԫ�ز���---\n");
	printf("\n������Ҫ���Ҽ�¼��ѧ��(����-1����)��"); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0;
		p=SearchDSTable_BST2(DT1,key);
		if(!p)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem_BST(p); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",count);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	} 

	int total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchDSTable_BST1(DT1, ST1.elem[i].key);
		total=total+count;
	}
	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchDSTable_BST1(DT1,4);
		else SearchDSTable_BST1(DT1,ST1.elem[i].key+1);
		total=total+count;
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));

	//���춯̬���ұ�������Ԫ�� �� 
	printf("\n---Ԫ�ز���---\n");
	RecordType e;
	printf("\n������Ҫ������¼�¼(����-1����)\nѧ�� ���� �Ա� ����\n");
	InputElem(e); 
	while (e.key!=-1) {
		if(InsertDSTable_BST(DT1,e)){
			printf("\n����Ԫ�غ�Ķ�̬���ұ�(�������)\n");
			printf("ѧ�� ���� �Ա� ����\n");
			TraversDSTable_InOrder(DT1);
		}
		else printf("��ǰҪ����ļ�¼�Ѵ��ڣ���ֹ���룡\n");
		printf("\n������Ҫ������¼�¼(����-1����)\nѧ�� ���� �Ա� ����\n");
		InputElem(e); 
	}

	//ɾ����̬���ұ�Ԫ�� 
	printf("\n---Ԫ��ɾ��---\n");
	printf("\n������Ҫɾ����¼��ѧ��(����-1����)��"); 
	scanf("%d",&key); 
	while (key!=-1){
		if(DeleteDSTable_BST(DT1,key)){
			printf("\nɾ��Ԫ�غ�Ķ�̬���ұ�(�������)\n");
			printf("ѧ�� ���� �Ա� ����\n");
			TraversDSTable_InOrder(DT1);
		}
	    else printf("��ǰҪɾ���ļ�¼�����ڣ�\n");
		printf("\n������Ҫɾ����¼��ѧ��(����-1����)��"); //��һ��ɾ�� 
		scanf("%d",&key); 
	} 

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

// ������̬���ұ�
typedef struct {
    RecordType *elem; //�洢����Ԫ�ص�һά����
    int length; //��¼�ĳ���
} SSTable;

// ������̬���ұ�
void CreateSSTable(SSTable &ST, int n) {
    ST.elem = (RecordType *)malloc((n+1)*sizeof(RecordType));
    if (!ST.elem) exit(OVERFLOW);
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


    for (int i=1; i<=n; i++) {
        ST.elem[i].key = DATA[i].key;
        ST.elem[i].name = DATA[i].name;
        ST.elem[i].sex = DATA[i].sex;
        ST.elem[i].age = DATA[i].age;
    }
}

// ��������
void TraversSSTable(SSTable ST) {
    printf("ѧ��\t����\t�Ա�\t����\n");
    for (int i=1; i<=ST.length; i++) {
        printf("%d\t%s\t%s\t%d\n", ST.elem[i].key, ST.elem[i].name, ST.elem[i].sex, ST.elem[i].age);
    }
}

// ������̬���ұ�
int InsertDSTable_BST(BSTree &DT, RecordType e) {
    BSTree p = DT;
    BSTree s = NULL;
    while (p) {// ���Ҳ���λ�ã�sָ��p��ǰ��
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

// ������̬���ұ�
void CreateDSTable_BST(BSTree &DT, SSTable &ST) {
    for (int i=1; i<=ST.length; i++) {
        InsertDSTable_BST(DT, ST.elem[i]);
    }
}

// �������
void TraversDSTable_InOrder(BSTree DT) {
    if (DT) {
        TraversDSTable_InOrder(DT->lchild);
        printf("%d\t%s\t%s\t%d\n", DT->data.key, DT->data.name, DT->data.sex, DT->data.age);
        TraversDSTable_InOrder(DT->rchild);
    }
}

// ����(�ǵݹ�)
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

// ����(�ݹ�)
BSTree SearchDSTable_BST2(BSTree DT, KeyType key) {
	if (!DT) return NULL;
	count++;
	if (key == DT->data.key) return DT;
	if (key < DT->data.key) return SearchDSTable_BST2(DT->lchild, key);
	else return SearchDSTable_BST2(DT->rchild, key);
}

// ���
void OutElem_BST(BSTree p) {
	printf("ѧ��\t����\t�Ա�\t����\n");
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

// ɾ��
int DeleteDSTable_BST(BSTree &DT, KeyType key) {
    BSTree p = DT;
    BSTree f = NULL;
    BSTree s = NULL;
    while (p) {// ����ɾ��λ��,fָ��p��ǰ��
        if (key == p->data.key) break;
        f = p;
        if (key < p->data.key) p = p->lchild;
        else p = p->rchild;
    }
    if (!p) return FALSE;// δ�ҵ�
    if (!p->lchild) {// ��������
        if (!f) DT = p->rchild;// �����
        else if (f->lchild == p) f->lchild = p->rchild;
        else f->rchild = p->rchild;
        free(p);
    } else if (!p->rchild) {// ��������
        if (!f) DT = p->lchild;
        else if (f->lchild == p) f->lchild = p->lchild;
        else f->rchild = p->lchild;
        free(p);
    } else {
        s = p->lchild;
        f = p;
        while (s->rchild) {// �ҵ��Ƴ�pǰ���Ľ��s
            f = s;
            s = s->rchild;
        }
        p->data = s->data;
        if (f != p) f->rchild = s->lchild;// s��ǰ��f����p
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

	//������̬���ұ�ST1 
	CreateSSTable(ST1,n);
	printf("\n��̬���ұ�\n");
	TraversSSTable(ST1);

	//������̬���ұ�DT1 
	CreateDSTable_BST(DT1,ST1);
	printf("\n��̬���ұ�(�������)\n");
	printf("ѧ�� ���� �Ա� ����\n");
	TraversDSTable_InOrder(DT1);

	//���Ҷ�̬���ұ�Ԫ�� 
	printf("\n---Ԫ�ز���---\n");
	printf("\n������Ҫ���Ҽ�¼��ѧ��(����-1����)��"); 
	scanf("%d",&key); 
	while (key!=-1){
		count=0;
		p=SearchDSTable_BST2(DT1,key);
		if(!p)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else 
			OutElem_BST(p); 		//����ҵ��ļ�¼ 
		printf("����ʱ�ȽϵĴ���=%d\n",count);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf("%d",&key); 
	} 

	int total=0;
	for(i=1;i<=ST1.length;i++){
		count=0;
		SearchDSTable_BST1(DT1, ST1.elem[i].key);
		total=total+count;
	}
	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);

	total=0;
	for(i=0;i<=ST1.length;i++){
		count=0;
		if(i==0) SearchDSTable_BST1(DT1,4);
		else SearchDSTable_BST1(DT1,ST1.elem[i].key+1);
		total=total+count;
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));

	//���춯̬���ұ�������Ԫ�� �� 
	printf("\n---Ԫ�ز���---\n");
	RecordType e;
	printf("\n������Ҫ������¼�¼(����-1����)\nѧ�� ���� �Ա� ����\n");
	InputElem(e); 
	while (e.key!=-1) {
		if(InsertDSTable_BST(DT1,e)){
			printf("\n����Ԫ�غ�Ķ�̬���ұ�(�������)\n");
			printf("ѧ�� ���� �Ա� ����\n");
			TraversDSTable_InOrder(DT1);
		}
		else printf("��ǰҪ����ļ�¼�Ѵ��ڣ���ֹ���룡\n");
		printf("\n������Ҫ������¼�¼(����-1����)\nѧ�� ���� �Ա� ����\n");
		InputElem(e); 
	}

	//ɾ����̬���ұ�Ԫ�� 
	printf("\n---Ԫ��ɾ��---\n");
	printf("\n������Ҫɾ����¼��ѧ��(����-1����)��"); 
	scanf("%d",&key); 
	while (key!=-1){
		if(DeleteDSTable_BST(DT1,key)){
			printf("\nɾ��Ԫ�غ�Ķ�̬���ұ�(�������)\n");
			printf("ѧ�� ���� �Ա� ����\n");
			TraversDSTable_InOrder(DT1);
		}
	    else printf("��ǰҪɾ���ļ�¼�����ڣ�\n");
		printf("\n������Ҫɾ����¼��ѧ��(����-1����)��"); //��һ��ɾ�� 
		scanf("%d",&key); 
	} 

	return 1;
}