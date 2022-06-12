#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RCD 10000       // ����¼��
#define NUM_RCD 100         // ��¼��
#define BOUNDARY 100        // ��Χ

typedef struct RcdType{
    int key[4];             // 4���ؼ���
} RcdType;                  // ��¼����

typedef struct SqList{
    RcdType rcd[MAX_RCD + 1]; // v[0]���ã����ڲ������㷨ʹ�� 
    int length;             // ��¼��
} SqList;                   // LSD-�ȶ����ڲ�����MSD

typedef struct LinkedList{
    RcdType rcd;
    struct LinkedList *next;
} LinkedList;               // LSD-�����䡱�͡��ռ�������

// LSD�����ؼ��ֲ����ȶ����ڲ����򷽷�
SqList *LSDStable(SqList *SL, int order[]);

// LSD�����ؼ��ֲ��á����䡱�͡��ռ����ķ���
LinkedList *LSDDistr(LinkedList *LL, int order[]); // distribute & collect

// MSD��
SqList *MSD(SqList *SL, int order[]);

// ������Ч��ʾ���
void InvalidInput();

// �ж����ȼ��Ƿ���ȷ
int isOrderValid(int order[]);

// ��ȡ���ȼ�
void GetOrder(int order[]);

LinkedList *InitLinkedList(LinkedList *LL);

LinkedList *AddLinkedList(LinkedList *LL, RcdType r);

SqList *InitSqList(SqList *SL);

SqList *AddSqList(SqList *SL, RcdType r);

// ��ӡ˳����е�������
void PrintSqList(SqList *SL);

// ��ӡ�����е�������
void PrintLinkedList(LinkedList *LL);