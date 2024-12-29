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

typedef  struct  {  //����������������� 
      int weight;
      int parent, lchild, rchild; 
} HTNode, *HTree;           //��̬��������洢�շ�����

typedef  char **HTCode;  //��̬�����ַ�������洢�շ��������

/*
2.  �շ�������������������ʵ��

��1��InitHTree(HTree &HT, int *w, int n)������ʼ���շ�����������w��n�ֱ���Ȩ�������Ҷ�ӽ������Ҫ����ݶ���ĺշ������ṹ������һ����2n-1��Ԫ����ɵ�һά����HT��HT[0..n-1]���n��Ҷ�ӽ���Ȩ�أ�����Ԫ�غ��������ֵ���ó�-1��
��2��CreateHTree(HTree &HT, int n)��������շ�����HT������n��Ҷ�ӽ������Ҫ����ݺշ������Ĺ����������һ����2n-1�������ɵ�һ�úշ�������
��3�� HTCoding(HTree HT, HTCode &HC,int n)�������ɺշ�������HC������n��Ҷ�ӽ������Ҫ��������ɵĺշ�����HT������n��Ҷ�ӽ��ĺշ������벢�����


3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����

��1���蹲��8��Ҷ�ӽ�㣬��Ȩ��w={5, 29, 7, 8, 14, 23, 3, 11}������InitHTree()��������Ҷ�ӽ���Ȩ�ش���շ������Ĵ洢�ṹHT�У������HT�����ݣ�
��2������CreateHTree()����������һ�������ĺշ�����HT�������HT�����ݣ�
��3������HTCoding()����������շ�����HT�и�Ҷ�ӽ��ĺշ������롣
*/

// InitHTree(HTree &HT, int *w, int n)������ʼ���շ�����������w��n�ֱ���Ȩ�������Ҷ�ӽ������Ҫ����ݶ���ĺշ������ṹ������һ����2n-1��Ԫ����ɵ�һά����HT��HT[0..n-1]���n��Ҷ�ӽ���Ȩ�أ�����Ԫ�غ��������ֵ���ó�-1��
Status InitHTree(HTree &HT, int *w, int n) {
    HT = (HTree)malloc((2*n-1)*sizeof(HTNode));// ����洢�ռ�
    if (!HT) exit(OVERFLOW);
    for (int i = 0; i < 2*n-1; i++) {// ��ʼ���շ�����
        if (i < n) {
            HT[i].weight = w[i];
        } else {
            HT[i].weight = -1;
        }
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    return OK;
}

// CreateHTree(HTree &HT, int n)��������շ�����HT������n��Ҷ�ӽ������Ҫ����ݺշ������Ĺ����������һ����2n-1�������ɵ�һ�úշ�������
Status CreateHTree(HTree &HT, int n) {
    if (n <= 1) return ERROR;// ֻ��һ�����
    int m = 2*n-1;
    for (int i = n; i < m; i++) {// ����շ�����
        int s1 = -1, s2 = -1;// ������СȨ�ؽ��
        int w1 = 0x7fffffff, w2 = 0x7fffffff;// ������СȨ��
        for (int j = 0; j < i; j++) {
            if (HT[j].parent == -1) {// δ��ѡ��
                if (HT[j].weight < w1) {// ������СȨ��
                    w2 = w1;// ���µڶ�СȨ��
                    s2 = s1;// ���µڶ�С���
                    w1 = HT[j].weight;// ������СȨ��
                    s1 = j;// ������С���
                } else if (HT[j].weight < w2) {
                    w2 = HT[j].weight;
                    s2 = j;
                }
            }
        }
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    return OK;
}

// HTCoding(HTree HT, HTCode &HC,int n)�������ɺշ�������HC������n��Ҷ�ӽ������Ҫ��������ɵĺշ�����HT������n��Ҷ�ӽ��ĺշ������벢�����
Status HTCoding(HTree HT, HTCode &HC,int n) {
    HC = (HTCode)malloc(n*sizeof(char*));// ����洢�ռ�
    if (!HC) exit(OVERFLOW);
    char *cd = (char*)malloc(n*sizeof(char));// ����洢�ռ�
    if (!cd) exit(OVERFLOW);
    cd[n-1] = '\0';// ������
    for (int i = 0; i < n; i++) {// ���ɺշ�������
        int start = n-1;// ��ʼλ��
        int c = i;// ��ǰ���
        int f = HT[i].parent;// �����
        while (f != -1) {
            --start;
            if (HT[f].lchild == c) {// ����
                cd[start] = '0';
            } else {
                cd[start] = '1';
            }
            c = f;
            f = HT[f].parent;
        }
        HC[i] = (char*)malloc((n-start)*sizeof(char));// ����洢�ռ�
        if (!HC[i]) exit(OVERFLOW);
        strcpy(HC[i], &cd[start]);// ���ƺշ�������
    }
    free(cd);
    return OK;
}


// ����Ȩ��
void ReadWeight(int *w, int n) {
    printf("������Ȩ�أ���,�ָ�����\n");
    char input[100];
    // ��������\n
    fgetc(stdin);
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *token;
        char *input_copy = strdup(input); // ���������ַ���
        token = strtok(input_copy, ",");
        for (int i = 0; i < n; i++) {
            if (token != NULL) {
                w[i] = atoi(token);
                token = strtok(NULL, ",");
            } else {
                printf("�����Ȩ���������㡣\n");
                free(input_copy);
                exit(ERROR);
            }
        }
        free(input_copy); // �ͷŸ��Ƶ��ַ���
    } else {
        printf("��ȡ����ʧ�ܡ�\n");
        exit(ERROR);
    }
}

int main() {
    // int w[8] = {5, 29, 7, 8, 14, 23, 3, 11};

    // ��ʼ���շ�����
    char input[100]; // ���ڴ洢�����ַ���
    int n;
    printf("������n: ");
    scanf("%d", &n);
    int w[n];
    ReadWeight(w, n);

    HTree HT;
    HTCode HC;
    InitHTree(HT, w, 8);
    printf("����InitHTree()����,HT:\n");
    for (int i = 0; i < 15; i++) {
        printf("%d %d %d %d %d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild, i);
    }
    CreateHTree(HT, 8);
    printf("����CreateHTree()����,HT:\n");
    for (int i = 0; i < 15; i++) {
        printf("%d %d %d %d %d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild, i);
    }
    HTCoding(HT, HC, 8);
    printf("����HTCoding()����,HC:\n");
    for (int i = 0; i < 8; i++) {
        printf("%s\n", HC[i]);
    }
    return 0;
}

// test data
// 5, 29, 7, 8, 14, 23, 3, 11