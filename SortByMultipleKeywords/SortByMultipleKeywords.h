#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RCD 10000           // ����¼��
#define NUM_RCD 100             // ��¼��
#define BOUNDARY 100            // ÿ�����ݵ����ȡֵ���?
#define NUM_KEY 4               // �ؼ��ָ���

typedef struct RcdType{
    int key[NUM_KEY];           // 4���ؼ���
} RcdType;                      // ��¼����

typedef struct RcdSqType{
    RcdType data;           // 4���ؼ���
    int ord;                    // ˳��������֤�ȶ�
}RcdSqType;

typedef struct SqList{
    RcdSqType rcd[MAX_RCD + 1];   // v[0]���ã����ڲ������㷨ʹ�� 
    int length;                 // ��¼��
} SqList;                       // LSD-�ȶ����ڲ�����MSD

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

// ������Ч��ʾ���?
void InvalidInput();

// �ж����ȼ��Ƿ���ȷ
int isOrderValid(int order[]);

// ��ȡ���ȼ�
void GetOrder(int order[]);

// ��ʼ������
LinkedList *InitLinkedList(LinkedList *LL);

// ��������β���ӽ��?
LinkedList *AddLinkedList(LinkedList *LL, RcdType r);

// ��ʼ��˳���?
SqList *InitSqList(SqList *SL);

// ��˳�����β���ӽ��
SqList *AddSqList(SqList *SL, RcdType r, int i);

// ��ӡ˳����е�������?
void PrintSqList(SqList *SL);

// ��ӡ�����е�������
void PrintLinkedList(LinkedList *LL);

// compare: ��űȽϴ���?
// move: ����ƶ�����?

/*unsigned long LSDStable_compare;
unsigned long LSDStable_move;

unsigned long LSDDistr_compare;
unsigned long LSDDistr_move;

unsigned long MSD_compare;
unsigned long MSD_move;*/

void Qsort(SqList *SL,int low, int high,int key_num);

int Partition(SqList *SL,int low,int high,int key_num);