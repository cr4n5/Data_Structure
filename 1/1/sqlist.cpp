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

typedef int Status;   //���庯��������

typedef int ElemType;//����ElemType����

typedef struct {	 
    ElemType *elem;  //���Ա����ݴ洢�ռ��ַ 
    int length;		//���Ա�ǰ����
}SqList;// LISTΪ�û���������Ա�����




// ��ʼ�������Ա�
Status InitList(SqList &L) { 
    L.elem = new ElemType[MAXSIZE]; // ����new��������洢�ռ�
    if (!L.elem) return OVERFLOW; // ����ڴ�����Ƿ�ɹ�
    L.length = 0; // �ձ���Ϊ0
    return OK;
}

//������Ա�Ԫ�� 
Status ClearList(SqList &L){ 
	L.length=0;
	return OK;
} 

//������Ա���
int ListLength(SqList L){ 
	return L.length;
}

//�����Ա�ָ��λ�ò���һ����Ԫ��
Status ListInsert(SqList &L, int pos, ElemType e){
//posΪ����ģ��߼���λ��,eΪ�����������Ԫ�ء�����ɹ��򷵻�1������������ֵΪ0��
	if (pos<1 || pos>L.length+1) return ERROR; // ������λ���Ƿ�Ϸ�
	if (L.length >= MAXSIZE) return ERROR; // ���洢�ռ��Ƿ�����
	for (int i = L.length; i >= pos; i--) {// ����λ�ü�֮���Ԫ�غ���
		L.elem[i] = L.elem[i - 1]; 
	}

	L.elem[pos - 1] = e; // ������Ԫ��
	L.length++; // ���±�
	return OK;// ����ɹ�
} 

//�����Ա���ɾ��ָ��λ���Ԫ��
Status ListDelete(SqList &L, int pos, ElemType &e)
{//posΪɾ���ģ��߼���λ��,��item���ر�ɾԪ�ء�ɾ���ɹ��򷵻�1������������ֵΪ0��
	if (pos<1 || pos>L.length) return ERROR; // ���ɾ��λ���Ƿ�Ϸ�
	e = L.elem[pos - 1]; // ���汻ɾ��Ԫ��
	for (int i = pos; i < L.length; i++) {// ɾ��λ��֮���Ԫ��ǰ��
		L.elem[i - 1] = L.elem[i];
	}
	L.length--; // ���±�

	return OK;// ɾ���ɹ�

}

//��ȡ˳�����ָ��λ���ϵ�����Ԫ�� 
Status GetElem(SqList L,int pos,ElemType &e){
//posΪָ��λ��,item���ڷ����ҵ�������Ԫ�أ������գ��򷵻�ERROR;
	if (pos<1 || pos>L.length) return ERROR; // ���λ���Ƿ�Ϸ�
	e = L.elem[pos - 1]; // ��ȡָ��λ��Ԫ��
	return OK;// ��ȡ�ɹ�
} 

//�����Ա��в���Ԫ�أ����ص�һ����ָ��ֵƥ��Ԫ��λ��
int LocateElem(SqList L,ElemType e){

	for (int i = 0; i < L.length; i++) {// ˳�����
		if (L.elem[i] == e) return i + 1; // �ҵ�ƥ��Ԫ��
	}
	return 0; // δ�ҵ�ƥ��Ԫ��

} 

//����������Ա�
Status TraverseList(SqList L){
	for (int i = 0; i < L.length; i++) {// ˳�����
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	return OK;

}

// ���ϲ�����LA=LA��LB
Status Union(SqList &La, SqList Lb){
	for (int i = 0; i < Lb.length; i++) {// �������LB��Ԫ��
		if (!LocateElem(La, Lb.elem[i])) {// ��La�в����ڸ�Ԫ��
			if (!ListInsert(La, La.length + 1, Lb.elem[i])) return ERROR; // ���뵽La��,����ʧ���򷵻ش���
		}
	}
	return OK;// ������ɹ�

}

// ���Ͻ�����LA=LA ��LB
Status Intersection(SqList &La, SqList Lb) {
    for (int i = 0; i < La.length; i++) {// �������La��Ԫ��
		if (!LocateElem(Lb, La.elem[i])) {// ��Lb�в����ڸ�Ԫ��
			if (!ListDelete(La, i + 1, La.elem[i])) return ERROR; // ɾ��La�и�Ԫ��,ɾ��ʧ���򷵻ش���
			i--; // ɾ���󣬵�ǰλ��Ԫ���Ѹı䣬�����¼�鵱ǰλ��
		}
	}
	return OK;// ������ɹ�

} 

// ���ϲ�����LA=LA-LB
Status Difference(SqList &La, SqList Lb) {
	for (int i = 0; i < La.length; i++) {// �������La��Ԫ��
		if (LocateElem(Lb, La.elem[i])) {// ��Lb�д��ڸ�Ԫ��
			if (!ListDelete(La, i + 1, La.elem[i])) return ERROR; // ɾ��La�и�Ԫ��,ɾ��ʧ���򷵻ش���
			i--; // ɾ���󣬵�ǰλ��Ԫ���Ѹı䣬�����¼�鵱ǰλ��
		}
	}
	return OK;// ������ɹ�

}

// �����ϲ�LC=LA+LB
Status MergeList(SqList La, SqList Lb, SqList &Lc) {
	int i = 0, j = 0, k = 0;
	while (i < La.length && j < Lb.length) {// ����Ƚ�La��Lb��Ԫ��
		if (La.elem[i] < Lb.elem[j]) {// ��La��Ԫ��С��Lb��Ԫ��
			Lc.elem[k++] = La.elem[i++]; // ��La��Ԫ�ز���Lc��
		}
		else {
			Lc.elem[k++] = Lb.elem[j++]; // ��Lb��Ԫ�ز���Lc��
		}
	}
	while (i < La.length) {// ��La��ʣ��Ԫ�ز���Lc��
		Lc.elem[k++] = La.elem[i++];
	}
	while (j < Lb.length) {// ��Lb��ʣ��Ԫ�ز���Lc��
		Lc.elem[k++] = Lb.elem[j++];
	}
	Lc.length = k; // ����Lc�ĳ���
	return OK;// �ϲ��ɹ�

}

// // ȥ��LC�ظ������Ԫ��
// Status Purge(SqList &Lc) {
// 	for (int i = 0; i < Lc.length; i++) {// �������Lc��Ԫ��
// 		for (int j = i + 1; j < Lc.length; j++) {// ����Ƚ�Lc��Ԫ��
// 			if (Lc.elem[i] == Lc.elem[j]) {// ��Lc�д����ظ�Ԫ��
// 				if (!ListDelete(Lc, j + 1, Lc.elem[j])) return ERROR; // ɾ��Lc���ظ�Ԫ��,ɾ��ʧ���򷵻ش���
// 				j--; // ɾ���󣬵�ǰλ��Ԫ���Ѹı䣬�����¼�鵱ǰλ��
// 			}
// 		}
// 	}
// 	return OK;// ȥ�سɹ�

// } 

// ȥ��LC�ظ������Ԫ��
Status Purge(SqList &Lc) {
	int i = 0, j = 0;
	while (i < Lc.length) {// �������Lc��Ԫ��
		j = i + 1;
		while (j < Lc.length) {// ����Ƚ�Lc��Ԫ��
			if (Lc.elem[i] == Lc.elem[j]) {// ��Lc�д����ظ�Ԫ��
				if (!ListDelete(Lc, j + 1, Lc.elem[j])) return ERROR; // ɾ��Lc���ظ�Ԫ��,ɾ��ʧ���򷵻ش���
			}
			else {
				j++;
			}
		}
		i++;
	}
	return OK;// ȥ�سɹ�

}

// �������ַ����ж�ȡԪ�ز����뵽˳���
void ReadList(SqList &L, const char *input) {
    char *token;
    char *input_copy = strdup(input); // ���������ַ���
    token = strtok(input_copy, ",");
    while (token != NULL) {
        int value = atoi(token);
        ListInsert(L, L.length + 1, value);
        token = strtok(NULL, ",");
    }
    free(input_copy); // �ͷŸ��Ƶ��ַ���
}

//������ 
int main(){
	SqList LA,LB,LC;				//����˳������
	// ElemType Array1[]={2,8,27,39,66,77,89};		//˳���LA��Ԫ�� 
	// ElemType Array2[]={6,18,27,59,65,77,89,120,140};//˳���LB��Ԫ�� 
	ElemType item;
	int i;
	char input[100]; // ���ڴ洢�����ַ���

	// ��ʼ��LA,LB
    printf("��ʼ��LA,LB\n");

    // ��ʼ��˳���LA,LB
    InitList(LA);
    InitList(LB);

    // ����LA��Ԫ��
    printf("����LA��Ԫ�أ�(��,�ָ�)\n");
	scanf("%s", input);
    // ��ȡ���벢���뵽˳���
    ReadList(LA, input);

    // ����LB��Ԫ��
    printf("����LB��Ԫ�أ�(��,�ָ�)\n");
    scanf("%s", input);
    // ��ȡ���벢���뵽˳���
    ReadList(LB, input);

	// ����LA,LB�����ں������ĺ�Ļָ�
	SqList LA1,LB1;
	InitList(LA1);
	InitList(LB1);
	for(i=0;i<LA.length;i++) ListInsert(LA1,i+1,LA.elem[i]);
	for(i=0;i<LB.length;i++) ListInsert(LB1,i+1,LB.elem[i]);


	// //0-2����˳���LA,LB
	// for(i=0;i<7;i++) ListInsert(LA,i+1,Array1[i]);//0-2����˳���LA
	// for(i=0;i<9;i++) ListInsert(LB,i+1,Array2[i]);//0-2����˳���LB


	//0-3���˳����Ԫ��
	printf("LA��Ԫ�أ�");
	TraverseList(LA);
	printf("LB��Ԫ�أ�");
	TraverseList(LB);

	//1. ����LA=LA��LB����������
	Union(LA,LB);
	printf("LA��LB��Ԫ�أ�");
	TraverseList(LA);

	//�ָ�LA,LB
	ClearList(LA);
	ClearList(LB);
	for(i=0;i<LA1.length;i++) ListInsert(LA,i+1,LA1.elem[i]);
	for(i=0;i<LB1.length;i++) ListInsert(LB,i+1,LB1.elem[i]);


	//2.����LA=LA ��LB����������
	Intersection(LA,LB);
	printf("LA��LB��Ԫ�أ�");
	TraverseList(LA);

	//�ָ�LA,LB
	ClearList(LA);
	ClearList(LB);
	for(i=0;i<LA1.length;i++) ListInsert(LA,i+1,LA1.elem[i]);
	for(i=0;i<LB1.length;i++) ListInsert(LB,i+1,LB1.elem[i]);

	//3.����LA=LA-LB����������
	Difference(LA,LB);
	printf("LA-LB��Ԫ�أ�");
	TraverseList(LA);

	//�ָ�LA,LB
	ClearList(LA);
	ClearList(LB);
	for(i=0;i<LA1.length;i++) ListInsert(LA,i+1,LA1.elem[i]);
	for(i=0;i<LB1.length;i++) ListInsert(LB,i+1,LB1.elem[i]);

	
	//4.�����ϲ�LC=LA+LB����������
	InitList(LC);
	MergeList(LA,LB,LC);
	printf("LC=LA+LB,LC��Ԫ�أ�");
	TraverseList(LC);

	
	//5.ȥ��LC�ظ������Ԫ�� ����������
	Purge(LC);
	printf("ȥ��LC�ظ������Ԫ�غ��LC��Ԫ�أ�");
	TraverseList(LC);


	return 1;
}

// test input
// 2,8,27,39,66,77,89
// 6,18,27,59,65,77,89,120,140