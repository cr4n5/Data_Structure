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

typedef struct {
    char *ch;       //���Ƿǿմ����򰴴�������洢��������chΪNULL��
    int  length;   //������

} HString;

/*
2. ����������������ʵ��

��д���л��ڴ洢�ṹ�Ļ�������������C/C++Դ���롣

��1��StrAssign(HString &S,chars)�������ַ�������chars����������S��

��2��StrCompare(HSTring S, HString T)�����Ƚϴ�S��T��ֵ ����S>T,
�򷵻�1����S=T,�򷵻�0�����򷵻�-1��

��3��StrLength(HString S)�������ش�S�ĳ��ȡ�

��4��Concat(HString &S, HString T1, HString T2)��������T1��T2������һ�𸳸�������S��

��5��SubString(HString &sub, HString S, int pos, int len)������Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���1�� pos ��StrLength(S)��1��len��StrLength(S)-pos+1

��6��StrTraverse(HString S)����������������ַ���S�еĸ����ַ���

��7��StrCopy(HString &S, HString T)��������T������S��

3. ����������������ʵ�� 

�����������Ļ��������������������д��Ĳ���������

��1��Index(HString S, HString T, int pos)�������ش�T�ڴ�S�е�pos���ַ���ʼ���ֵ�λ�ã�����T���Ǵ�S���Ӵ����򷵻�0��1�� pos ��StrLength(S)������SubString()��StrCompare()ʵ�֡�

��2��Replace(HString &S, HString T1, HString T2)������S�������е��Ӵ�T1�ô�T2���档����SubString()��StrCompare()��Concat()ʵ�֡�

��3��StrInsert (HString &S, int pos, HString T)�����ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��1�� pos ��StrLength(S)+1������SubString()��Concat()ʵ�֡�

��4��StrDelete(HString &S, int pos, int len)����ɾ����S�дӵ�pos���ַ���ʼ������len���ַ���1�� pos ��StrLength(S)-len+1������SubString()��Concat()ʵ�֡�



4. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����

��1������׼��������StrAssign()���趨���ַ��������������趨������3���ַ�������T1,T2,T3��Ȼ������StrTraverse()����ַ����ַ���


��2������StrCopy()����T1������S�������S���ַ���


��3������StrInsert()����T2���뵽S��β���������S���ַ���

��4������StrReplace()����S�е�T1�滻��T3�������S���ַ���

��5������Index()���Ҵ�T2��S�е�λ�ã������λ�ý����

��6������StrDelete()ɾ��S���Ӵ�T2�������ɾ����S�Ľ����
 */


/*
2. ����������������ʵ��

��д���л��ڴ洢�ṹ�Ļ�������������C/C++Դ���롣
*/

// StrAssign(HString &S,chars)�������ַ�������chars����������S��
Status StrAssign(HString &S, char *chars) {
    if (S.ch) {// �ͷ�ԭ�пռ�
        free(S.ch);
    }
    int len = strlen(chars); // �ַ�������
    if (!len) {// �մ�
        S.ch = NULL;
        S.length = 0;
    } else {
        S.ch = (char *)malloc(len * sizeof(char));// ����洢�ռ�
        if (!S.ch) {// �洢����ʧ��
            exit(OVERFLOW);
        }
        for (int i = 0; i < len; ++i) {// �����ַ���
            S.ch[i] = chars[i];
        }
        S.length = len;// ������
    }
    return OK;
}

// StrCompare(HSTring S, HString T)�����Ƚϴ�S��T��ֵ ����S>T,�򷵻�1����S=T,�򷵻�0�����򷵻�-1��
int StrCompare(HString S, HString T) {
    for (int i = 0; i < S.length && i < T.length; ++i) {// ����ַ��Ƚ�
        if (S.ch[i]>T.ch[i]) {// S>T
            return 1;
        } else if (S.ch[i] < T.ch[i]) {// S<T
            return -1;
        }
    }
    if (S.length > T.length) {// S>T
        return 1;
    } else if (S.length < T.length) {// S<T
        return -1;
    } else {
        return 0;// S=T
    }
}

// StrLength(HString S)�������ش�S�ĳ��ȡ�
int StrLength(HString S) {
    return S.length;
}

// StrCopy(HString &S, HString T)��������T������S��
Status StrCopy(HString &S, HString T) {
    if (S.ch) {
        free(S.ch);
    }
    S.ch = (char *)malloc(T.length * sizeof(char));
    if (!S.ch) {
        exit(OVERFLOW);
    }
    for (int i = 0; i < T.length; ++i) {// �����ַ���
        S.ch[i] = T.ch[i];
    }
    S.length = T.length;
    return OK;
}

// Concat(HString &S, HString T1, HString T2)��������T1��T2������һ�𸳸�������S��
Status Concat(HString &S, HString T1, HString T2) {

    if (S.ch) {
        free(S.ch);
    }
    S.ch = (char *)malloc((T1.length + T2.length) * sizeof(char));
    if (!S.ch) {
        exit(OVERFLOW);
    }
    for (int i = 0; i < T1.length; ++i) {// �����ַ���T1
        S.ch[i] = T1.ch[i];
    }
    for (int i = 0; i < T2.length; ++i) {// �����ַ���T2
        S.ch[T1.length + i] = T2.ch[i];
    }
    S.length = T1.length + T2.length;// ������
    return OK;
}

// SubString(HString &sub, HString S, int pos, int len)������Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���1�� pos ��StrLength(S)��1��len��StrLength(S)-pos+1
Status SubString(HString &sub, HString S, int pos, int len) {
    if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1) {// �������Ϸ�
        return ERROR; 
    }
    if (sub.ch) {
        free(sub.ch);
    }
    if (len == 0) {// �մ�
        sub.ch = NULL;
        sub.length = 0;
    } else {
        sub.ch = (char *)malloc(len * sizeof(char));
        if (!sub.ch) {
            exit(OVERFLOW);
        }
        for (int i = 0; i < len; ++i) {// �����ַ���
            sub.ch[i] = S.ch[pos - 1 + i];
        }
        sub.length = len;// ������
    }
    return OK;
}

// StrTraverse(HString S)����������������ַ���S�еĸ����ַ���
Status StrTraverse(HString S) {
    for (int i = 0; i < S.length; ++i) {
        printf("%c", S.ch[i]);
    }
    printf("\n");
    return OK;
}

/*
3. ����������������ʵ�� 

�����������Ļ��������������������д��Ĳ���������
*/

// Index(HString S, HString T, int pos)�������ش�T�ڴ�S�е�pos���ַ���ʼ���ֵ�λ�ã�����T���Ǵ�S���Ӵ����򷵻�0��1�� pos ��StrLength(S)������SubString()��StrCompare()ʵ�֡�
int Index(HString S, HString T, int pos) {
    if (pos < 1 || pos > S.length) {
        return 0;
    }
    HString sub={NULL, 0};
    for (int i = pos; i <= S.length - T.length + 1; ++i) {// ���λ�ñȽ�
        SubString(sub, S, i, T.length);// ��ȡ�Ӵ�
        if (StrCompare(sub, T) == 0) {// �Ӵ����
            return i;
        }
    }
    return 0;
}

// Replace(HString &S, HString T1, HString T2)������S�������е��Ӵ�T1�ô�T2���档����SubString()��StrCompare()��Concat()ʵ�֡�
Status Replace(HString &S, HString T1, HString T2) {
    int pos = 1;
    while (pos <= S.length) {
        pos = Index(S, T1, pos);// �����Ӵ�
        if (pos == 0) {// δ�ҵ��Ӵ�
            break;
        }
        HString sub1={NULL, 0}, sub2={NULL, 0}, sub3={NULL, 0};
        SubString(sub1, S, 1, pos - 1);// ��ȡS��ǰ�벿��
        SubString(sub2, S, pos + T1.length, S.length - pos - T1.length + 1);// ��ȡS�ĺ�벿��
        Concat(sub3, sub1, T2);// ǰ�벿������T2
        StrCopy(sub1, sub3);
        Concat(S, sub1, sub2);// ǰ�벿������T2��ͺ�벿������
        pos += T2.length;
    }
    return OK;
}

// StrInsert (HString &S, int pos, HString T)�����ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��1�� pos ��StrLength(S)+1������SubString()��Concat()ʵ�֡�
Status StrInsert(HString &S, int pos, HString T) {
    if (pos < 1 || pos > S.length + 1) {
        return ERROR;
    }
    HString sub1={NULL, 0}, sub2={NULL, 0}, sub3={NULL, 0};
    SubString(sub1, S, 1, pos - 1);// ��ȡS��ǰ�벿��
    SubString(sub2, S, pos, S.length - pos + 1);// ��ȡS�ĺ�벿��
    Concat(sub3, sub1, T);// ǰ�벿������T
    StrCopy(sub1, sub3);
    Concat(S, sub1, sub2);// ǰ�벿������T��ͺ�벿������
    return OK;
}

// StrDelete(HString &S, int pos, int len)����ɾ����S�дӵ�pos���ַ���ʼ������len���ַ���1�� pos ��StrLength(S)-len+1������SubString()��Concat()ʵ�֡�
Status StrDelete(HString &S, int pos, int len) {
    if (pos < 1 || pos > S.length - len + 1) {
        return ERROR;
    }
    HString sub1={NULL, 0}, sub2={NULL, 0};
    SubString(sub1, S, 1, pos - 1);// ��ȡS��ǰ�벿��
    SubString(sub2, S, pos + len, S.length - pos - len + 1);// ��ȡS�ĺ�벿��
    Concat(S, sub1, sub2);// ǰ�벿�ֺͺ�벿������
    return OK;
}

int main() {

    // ����׼��
    HString T1={NULL, 0}, T2={NULL, 0}, T3={NULL, 0};
    printf("�������ַ���T1: ");
    char input[100];
    scanf("%s", input);
    StrAssign(T1, input);
    printf("�������ַ���T2: ");
    scanf("%s", input);
    StrAssign(T2, input);
    printf("�������ַ���T3: ");
    scanf("%s", input);
    StrAssign(T3, input);

    printf("T1: ");
    StrTraverse(T1);
    printf("T2: ");
    StrTraverse(T2);
    printf("T3: ");
    StrTraverse(T3);

    HString S={NULL, 0};
    printf("����StrCopy()����T1������S�������S���ַ���");
    StrCopy(S, T1);
    printf("S: ");
    StrTraverse(S);

    printf("����StrInsert()����T2���뵽S��β���������S���ַ���");
    StrInsert(S, S.length + 1, T2);
    printf("S: ");
    StrTraverse(S);

    printf("����StrReplace()����S�е�T1�滻��T3�������S���ַ���");
    Replace(S, T1, T3);
    printf("S: ");
    StrTraverse(S);

    printf("����Index()���Ҵ�T2��S�е�λ�ã������λ�ý����");
    printf("Index: %d\n", Index(S, T2, 1));

    printf("����StrDelete()ɾ��S���Ӵ�T2�������ɾ����S�Ľ����");
    StrDelete(S, Index(S, T2, 1), T2.length);
    printf("S: ");
    StrTraverse(S);

    return 0;
}