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

typedef struct LNode {  //������Ͷ��� 
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;  



// ��ʼ�������Ա�
Status InitList(LinkList &L) { 
	L = (LinkList)malloc(sizeof(LNode)); // ����ͷ���ռ�
	if (!L) return ERROR; // ����ʧ��
	L->next = NULL; // ͷ���ָ�����ÿ�
	return OK; // ��ʼ���ɹ�
}

//������Ա�Ԫ�� 
Status ClearList(LinkList &L){ 
	LinkList p, q;
	p = L->next; // pָ���һ�����
	while (p) { // ��������
		q = p->next; // qָ����һ�����
		free(p); // �ͷ�p���
		p = q; // pָ����һ�����
	}
	L->next = NULL; // ͷ���ָ�����ÿ�
	return OK; // ��ճɹ�
} 

//������Ա���
int ListLength(LinkList L){ 
	int len = 0;
	LinkList p = L->next;
	while (p) { // ��������
		len++;
		p = p->next;
	}
	return len; // ����������
}

//�����Ա�ָ��λ�ò���һ����Ԫ��
Status ListInsert(LinkList &L, int pos, ElemType e){
//posΪ����ģ��߼���λ��,eΪ�����������Ԫ�ء�����ɹ��򷵻�1������������ֵΪ0��
	LinkList p = L;
	int i = 0;
	while (p && i < pos - 1) { // ���Ҳ���λ��
		p = p->next;
		i++;
	}
	if (!p || i > pos - 1) return ERROR; // ������λ���Ƿ�Ϸ�
	LinkList s = (LinkList)malloc(sizeof(LNode)); // �����½��ռ�
	if (!s) return ERROR; // ����ʧ��
	s->data = e; // �½��������ֵ
	s->next = p->next; // �½��ָ����ָ���̽��
	p->next = s; // ǰ�����ָ����ָ���½��
	return OK; // ����ɹ�
} 

//�����Ա���ɾ��ָ��λ���Ԫ��
Status ListDelete(LinkList &L, int pos, ElemType &e)
{//posΪɾ���ģ��߼���λ��,��item���ر�ɾԪ�ء�ɾ���ɹ��򷵻�1������������ֵΪ0��
	LinkList p = L;
	int i = 0;
	while (p->next && i < pos - 1) { // ����ɾ��λ��
		p = p->next;
		i++;
	}
	if (!p->next || i > pos - 1) return ERROR; // ���ɾ��λ���Ƿ�Ϸ�
	LinkList q = p->next; // qָ��ɾ�����
	e = q->data; // ���汻ɾ��Ԫ��
	p->next = q->next; // ǰ�����ָ����ָ���̽��
	free(q); // �ͷű�ɾ�����
	return OK; // ɾ���ɹ�

}

//��ȡ˳�����ָ��λ���ϵ�����Ԫ�� 
Status GetElem(LinkList L,int pos,ElemType &e){
//posΪָ��λ��,item���ڷ����ҵ�������Ԫ�أ������գ��򷵻�ERROR;
	LinkList p = L;
	int i = 0;
	while (p && i < pos) { // ����ָ��λ��
		p = p->next;
		i++;
	}
	if (!p || i > pos) return ERROR; // ���λ���Ƿ�Ϸ�
	e = p->data; // ��ȡָ��λ��Ԫ��
	return OK;// ��ȡ�ɹ�
} 

//����L�е�1����e��ȵ����ݽ��ĵ�ַ��ָ�룩����e�����ڣ��򷵻�NULL��
LNode *LocateList(LinkList L,ElemType e){
	LinkList p = L;
	while (p->next) { // ��������
		p = p->next;
		if (p->data == e) return p; // �ҵ�ƥ��Ԫ��
	}
	return NULL; // δ�ҵ�ƥ��Ԫ��
} 

//����������Ա�
Status TraverseList(LinkList L){
	LinkList p = L;
	while (p->next) { // ��������
		p = p->next;
		printf("%d ", p->data); // ����������
	}
	printf("\n");
	return OK; // �����ɹ�

}

// ���ϲ�����LA=LA��LB
Status Union(LinkList &La, LinkList Lb){
	LinkList p = La->next;
	LinkList q = Lb->next;
	while (q) { // ����Lb
		if (!LocateList(La, q->data)) { // ��La�в����ڸ�Ԫ��
			LinkList s = (LinkList)malloc(sizeof(LNode)); // �����½��ռ�
			if (!s) return ERROR; // ����ʧ��
			s->data = q->data; // �½��������ֵ
			s->next = p->next; // �½��ָ����ָ���̽��
			p->next = s; // ǰ�����ָ����ָ���½��
			p = s; // pָ���½��
		}
		q = q->next; // qָ����һ�����
	}
	return OK;// ������ɹ�

}

// ���Ͻ�����LA=LA ��LB
Status Intersection(LinkList &La, LinkList Lb) {
	LinkList p = La->next;
	LinkList q = Lb->next;
	LinkList r = La; // rָ��La��ͷ���
	while (p) {// �������La��Ԫ��
		if (!LocateList(Lb, p->data)) {// ��Lb�в����ڸ�Ԫ��
			LinkList s = p->next; // sָ����һ�����
			free(p); // �ͷ�p���
			r->next = s; // ǰ�����ָ����ָ���̽��
			p = s; // pָ����һ�����
		}
		else {
			r = p; // rָ��ǰ���
			p = p->next; // pָ����һ�����
		}
	}
	return OK;// ������ɹ�

} 

// ���ϲ�����LA=LA-LB
Status Difference(LinkList &La, LinkList Lb) {
	LinkList p = La->next;
	LinkList q = Lb->next;
	LinkList r = La; // rָ��La��ͷ���
	while (p) {// �������La��Ԫ��
		if (LocateList(Lb, p->data)) {// ��Lb�д��ڸ�Ԫ��
			LinkList s = p->next; // sָ����һ�����
			free(p); // �ͷ�p���
			r->next = s; // ǰ�����ָ����ָ���̽��
			p = s; // pָ����һ�����
		}
		else {
			r = p; // rָ��ǰ���
			p = p->next; // pָ����һ�����
		}
	}
	return OK;// ������ɹ�

}

// �����ϲ�LC=LA+LB
Status MergeList(LinkList La, LinkList Lb, LinkList &Lc) {
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = Lc;
	while (pa&&pb){
		if (pa->data <= pb->data) {
			LinkList s = (LinkList)malloc(sizeof(LNode)); // �����½��ռ�
			if (!s) return ERROR; // ����ʧ��
			s->data = pa->data; // �½��������ֵ
			pc->next = s; // �½��ָ����ָ���̽��
			pc = s; // pcָ���½��
			pa = pa->next; // paָ����һ�����
		}
		else {
			LinkList s = (LinkList)malloc(sizeof(LNode)); // �����½��ռ�
			if (!s) return ERROR; // ����ʧ��
			s->data = pb->data; // �½��������ֵ
			pc->next = s; // �½��ָ����ָ���̽��
			pc = s; // pcָ���½��
			pb = pb->next; // pbָ����һ�����
		}
	}
	while (pa) {
		LinkList s = (LinkList)malloc(sizeof(LNode)); // �����½��ռ�
		if (!s) return ERROR; // ����ʧ��
		s->data = pa->data; // �½��������ֵ
		pc->next = s; // �½��ָ����ָ���̽��
		pc = s; // pcָ���½��
		pa = pa->next; // paָ����һ�����
	}
	while (pb) {
		LinkList s = (LinkList)malloc(sizeof(LNode)); // �����½��ռ�
		if (!s) return ERROR; // ����ʧ��
		s->data = pb->data; // �½��������ֵ
		pc->next = s; // �½��ָ����ָ���̽��
		pc = s; // pcָ���½��
		pb = pb->next; // pbָ����һ�����
	}
	pc->next = NULL; // β���ָ�����ÿ�
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
Status Purge(LinkList &Lc) {
	LinkList p = Lc->next;
	while (p) {// �������Lc��Ԫ��
		LinkList q = p;
		while (q->next) {// ����Ƚ�Lc��Ԫ��
			if (p->data == q->next->data) {// ��Lc�д����ظ�Ԫ��
				LinkList s = q->next; // sָ����һ�����
				q->next = s->next; // ǰ�����ָ����ָ���̽��
				free(s); // �ͷ�s���
			}
			else {
				q = q->next; // qָ����һ�����
			}
		}
		p = p->next; // pָ����һ�����
	}
	return OK;// ȥ�سɹ�

}

// �������ַ����ж�ȡԪ�ز����뵽˳���
void ReadList(LinkList &L, const char *input) {
    char *token;
    char *input_copy = strdup(input); // ���������ַ���
    token = strtok(input_copy, ",");
    while (token != NULL) {
        int value = atoi(token);
        ListInsert(L, ListLength(L) + 1, value); // ���뵽˳���
        token = strtok(NULL, ",");
    }
    free(input_copy); // �ͷŸ��Ƶ��ַ���
}

//������ 
int main(){
	LinkList LA,LB,LC;	//������������
	// // ElemType Array1[]={2,8,27,39,66,77,89};		//˳���LA��Ԫ�� 
	// // ElemType Array2[]={6,18,27,59,65,77,89,120,140};//˳���LB��Ԫ�� 
	// ElemType item;
	// int i;
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

	// // ����LA,LB�����ں������ĺ�Ļָ�
	LinkList LA1,LB1;
	InitList(LA1);
	InitList(LB1);
	LinkList p = LA->next;
	while (p) {
		ListInsert(LA1, ListLength(LA1) + 1, p->data);
		p = p->next;
	}
	p = LB->next;
	while (p) {
		ListInsert(LB1, ListLength(LB1) + 1, p->data);
		p = p->next;
	}


	// // //0-2����˳���LA,LB
	// // for(i=0;i<7;i++) ListInsert(LA,i+1,Array1[i]);//0-2����˳���LA
	// // for(i=0;i<9;i++) ListInsert(LB,i+1,Array2[i]);//0-2����˳���LB


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
	LinkList q = LA1->next;
	while (q) {
		ListInsert(LA, ListLength(LA) + 1, q->data);
		q = q->next;
	}
	q = LB1->next;
	while (q) {
		ListInsert(LB, ListLength(LB) + 1, q->data);
		q = q->next;
	}


	//2.����LA=LA ��LB����������
	Intersection(LA,LB);
	printf("LA��LB��Ԫ�أ�");
	TraverseList(LA);

	//�ָ�LA,LB
	ClearList(LA);
	ClearList(LB);
	q = LA1->next;
	while (q) {
		ListInsert(LA, ListLength(LA) + 1, q->data);
		q = q->next;
	}
	q = LB1->next;
	while (q) {
		ListInsert(LB, ListLength(LB) + 1, q->data);
		q = q->next;
	}


	//3.����LA=LA-LB����������
	Difference(LA,LB);
	printf("LA-LB��Ԫ�أ�");
	TraverseList(LA);

	//�ָ�LA,LB
	ClearList(LA);
	ClearList(LB);
	q = LA1->next;
	while (q) {
		ListInsert(LA, ListLength(LA) + 1, q->data);
		q = q->next;
	}
	q = LB1->next;
	while (q) {
		ListInsert(LB, ListLength(LB) + 1, q->data);
		q = q->next;
	}

	
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