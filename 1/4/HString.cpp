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
    char *ch;       //若是非空串，则按串长分配存储区，否则ch为NULL。
    int  length;   //串长度

} HString;

/*
2. 串基本操作函数的实现

编写下列基于存储结构的基本操作函数的C/C++源代码。

（1）StrAssign(HString &S,chars)——将字符串常量chars赋给串变量S；

（2）StrCompare(HSTring S, HString T)——比较串S与T的值 ，若S>T,
则返回1；若S=T,则返回0；否则返回-1。

（3）StrLength(HString S)——返回串S的长度。

（4）Concat(HString &S, HString T1, HString T2)——将串T1和T2连接在一起赋给串变量S。

（5）SubString(HString &sub, HString S, int pos, int len)——用Sub返回串S的第pos个字符起长度为len的子串，1≤ pos ≤StrLength(S)，1≤len≤StrLength(S)-pos+1

（6）StrTraverse(HString S)——遍历（输出）字符串S中的各个字符。

（7）StrCopy(HString &S, HString T)——将串T赋给串S。

3. 串其他操作函数的实现 

调用上述串的基本操作函数，编制下列串的操作函数。

（1）Index(HString S, HString T, int pos)——返回串T在串S中第pos个字符开始出现的位置，若串T不是串S的子串，则返回0。1≤ pos ≤StrLength(S)。利用SubString()和StrCompare()实现。

（2）Replace(HString &S, HString T1, HString T2)——将S串中所有的子串T1用串T2代替。利用SubString()、StrCompare()和Concat()实现。

（3）StrInsert (HString &S, int pos, HString T)——在串S的第pos个字符之前插入串T。1≤ pos ≤StrLength(S)+1。利用SubString()和Concat()实现。

（4）StrDelete(HString &S, int pos, int len)——删除串S中从第pos个字符开始连续的len个字符。1≤ pos ≤StrLength(S)-len+1，利用SubString()和Concat()实现。



4. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：

（1）数据准备。利用StrAssign()将设定的字符串常量（自行设定）赋给3个字符串变量T1,T2,T3，然后利用StrTraverse()输出字符串字符。


（2）利用StrCopy()将串T1赋给串S，并输出S的字符。


（3）利用StrInsert()将串T2插入到S的尾部，并输出S的字符。

（4）利用StrReplace()将串S中的T1替换成T3，并输出S的字符。

（5）利用Index()查找串T2在S中的位置，并输出位置结果。

（6）利用StrDelete()删除S中子串T2，并输出删除后S的结果。
 */


/*
2. 串基本操作函数的实现

编写下列基于存储结构的基本操作函数的C/C++源代码。
*/

// StrAssign(HString &S,chars)——将字符串常量chars赋给串变量S；
Status StrAssign(HString &S, char *chars) {
    if (S.ch) {// 释放原有空间
        free(S.ch);
    }
    int len = strlen(chars); // 字符串长度
    if (!len) {// 空串
        S.ch = NULL;
        S.length = 0;
    } else {
        S.ch = (char *)malloc(len * sizeof(char));// 分配存储空间
        if (!S.ch) {// 存储分配失败
            exit(OVERFLOW);
        }
        for (int i = 0; i < len; ++i) {// 复制字符串
            S.ch[i] = chars[i];
        }
        S.length = len;// 串长度
    }
    return OK;
}

// StrCompare(HSTring S, HString T)——比较串S与T的值 ，若S>T,则返回1；若S=T,则返回0；否则返回-1。
int StrCompare(HString S, HString T) {
    for (int i = 0; i < S.length && i < T.length; ++i) {// 逐个字符比较
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

// StrLength(HString S)——返回串S的长度。
int StrLength(HString S) {
    return S.length;
}

// StrCopy(HString &S, HString T)——将串T赋给串S。
Status StrCopy(HString &S, HString T) {
    if (S.ch) {
        free(S.ch);
    }
    S.ch = (char *)malloc(T.length * sizeof(char));
    if (!S.ch) {
        exit(OVERFLOW);
    }
    for (int i = 0; i < T.length; ++i) {// 复制字符串
        S.ch[i] = T.ch[i];
    }
    S.length = T.length;
    return OK;
}

// Concat(HString &S, HString T1, HString T2)——将串T1和T2连接在一起赋给串变量S。
Status Concat(HString &S, HString T1, HString T2) {

    if (S.ch) {
        free(S.ch);
    }
    S.ch = (char *)malloc((T1.length + T2.length) * sizeof(char));
    if (!S.ch) {
        exit(OVERFLOW);
    }
    for (int i = 0; i < T1.length; ++i) {// 复制字符串T1
        S.ch[i] = T1.ch[i];
    }
    for (int i = 0; i < T2.length; ++i) {// 复制字符串T2
        S.ch[T1.length + i] = T2.ch[i];
    }
    S.length = T1.length + T2.length;// 串长度
    return OK;
}

// SubString(HString &sub, HString S, int pos, int len)——用Sub返回串S的第pos个字符起长度为len的子串，1≤ pos ≤StrLength(S)，1≤len≤StrLength(S)-pos+1
Status SubString(HString &sub, HString S, int pos, int len) {
    if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1) {// 参数不合法
        return ERROR; 
    }
    if (sub.ch) {
        free(sub.ch);
    }
    if (len == 0) {// 空串
        sub.ch = NULL;
        sub.length = 0;
    } else {
        sub.ch = (char *)malloc(len * sizeof(char));
        if (!sub.ch) {
            exit(OVERFLOW);
        }
        for (int i = 0; i < len; ++i) {// 复制字符串
            sub.ch[i] = S.ch[pos - 1 + i];
        }
        sub.length = len;// 串长度
    }
    return OK;
}

// StrTraverse(HString S)——遍历（输出）字符串S中的各个字符。
Status StrTraverse(HString S) {
    for (int i = 0; i < S.length; ++i) {
        printf("%c", S.ch[i]);
    }
    printf("\n");
    return OK;
}

/*
3. 串其他操作函数的实现 

调用上述串的基本操作函数，编制下列串的操作函数。
*/

// Index(HString S, HString T, int pos)——返回串T在串S中第pos个字符开始出现的位置，若串T不是串S的子串，则返回0。1≤ pos ≤StrLength(S)。利用SubString()和StrCompare()实现。
int Index(HString S, HString T, int pos) {
    if (pos < 1 || pos > S.length) {
        return 0;
    }
    HString sub={NULL, 0};
    for (int i = pos; i <= S.length - T.length + 1; ++i) {// 逐个位置比较
        SubString(sub, S, i, T.length);// 截取子串
        if (StrCompare(sub, T) == 0) {// 子串相等
            return i;
        }
    }
    return 0;
}

// Replace(HString &S, HString T1, HString T2)——将S串中所有的子串T1用串T2代替。利用SubString()、StrCompare()和Concat()实现。
Status Replace(HString &S, HString T1, HString T2) {
    int pos = 1;
    while (pos <= S.length) {
        pos = Index(S, T1, pos);// 查找子串
        if (pos == 0) {// 未找到子串
            break;
        }
        HString sub1={NULL, 0}, sub2={NULL, 0}, sub3={NULL, 0};
        SubString(sub1, S, 1, pos - 1);// 截取S的前半部分
        SubString(sub2, S, pos + T1.length, S.length - pos - T1.length + 1);// 截取S的后半部分
        Concat(sub3, sub1, T2);// 前半部分连接T2
        StrCopy(sub1, sub3);
        Concat(S, sub1, sub2);// 前半部分连接T2后和后半部分连接
        pos += T2.length;
    }
    return OK;
}

// StrInsert (HString &S, int pos, HString T)——在串S的第pos个字符之前插入串T。1≤ pos ≤StrLength(S)+1。利用SubString()和Concat()实现。
Status StrInsert(HString &S, int pos, HString T) {
    if (pos < 1 || pos > S.length + 1) {
        return ERROR;
    }
    HString sub1={NULL, 0}, sub2={NULL, 0}, sub3={NULL, 0};
    SubString(sub1, S, 1, pos - 1);// 截取S的前半部分
    SubString(sub2, S, pos, S.length - pos + 1);// 截取S的后半部分
    Concat(sub3, sub1, T);// 前半部分连接T
    StrCopy(sub1, sub3);
    Concat(S, sub1, sub2);// 前半部分连接T后和后半部分连接
    return OK;
}

// StrDelete(HString &S, int pos, int len)——删除串S中从第pos个字符开始连续的len个字符。1≤ pos ≤StrLength(S)-len+1，利用SubString()和Concat()实现。
Status StrDelete(HString &S, int pos, int len) {
    if (pos < 1 || pos > S.length - len + 1) {
        return ERROR;
    }
    HString sub1={NULL, 0}, sub2={NULL, 0};
    SubString(sub1, S, 1, pos - 1);// 截取S的前半部分
    SubString(sub2, S, pos + len, S.length - pos - len + 1);// 截取S的后半部分
    Concat(S, sub1, sub2);// 前半部分和后半部分连接
    return OK;
}

int main() {

    // 数据准备
    HString T1={NULL, 0}, T2={NULL, 0}, T3={NULL, 0};
    printf("请输入字符串T1: ");
    char input[100];
    scanf("%s", input);
    StrAssign(T1, input);
    printf("请输入字符串T2: ");
    scanf("%s", input);
    StrAssign(T2, input);
    printf("请输入字符串T3: ");
    scanf("%s", input);
    StrAssign(T3, input);

    printf("T1: ");
    StrTraverse(T1);
    printf("T2: ");
    StrTraverse(T2);
    printf("T3: ");
    StrTraverse(T3);

    HString S={NULL, 0};
    printf("利用StrCopy()将串T1赋给串S，并输出S的字符。");
    StrCopy(S, T1);
    printf("S: ");
    StrTraverse(S);

    printf("利用StrInsert()将串T2插入到S的尾部，并输出S的字符。");
    StrInsert(S, S.length + 1, T2);
    printf("S: ");
    StrTraverse(S);

    printf("利用StrReplace()将串S中的T1替换成T3，并输出S的字符。");
    Replace(S, T1, T3);
    printf("S: ");
    StrTraverse(S);

    printf("利用Index()查找串T2在S中的位置，并输出位置结果。");
    printf("Index: %d\n", Index(S, T2, 1));

    printf("利用StrDelete()删除S中子串T2，并输出删除后S的结果。");
    StrDelete(S, Index(S, T2, 1), T2.length);
    printf("S: ");
    StrTraverse(S);

    return 0;
}