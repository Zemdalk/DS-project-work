#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RCD 10000           // 最大记录数
#define NUM_RCD 100             // 记录数
#define BOUNDARY 100            // 每个数据的最大取值范围
#define NUM_KEY 4               // 关键字个数

typedef struct RcdType{
    int key[NUM_KEY];           // 4个关键字
} RcdType;                      // 记录类型

typedef struct SqList{
    RcdType rcd[MAX_RCD + 1];   // v[0]闲置，供内部排序算法使用 
    int length;                 // 记录数
} SqList;                       // LSD-稳定的内部排序；MSD

typedef struct LinkedList{
    RcdType rcd;
    struct LinkedList *next;
} LinkedList;               // LSD-“分配”和“收集”方法

// LSD，各关键字采用稳定的内部排序方法
SqList *LSDStable(SqList *SL, int order[]);

// LSD，各关键字采用“分配”和“收集”的方法
LinkedList *LSDDistr(LinkedList *LL, int order[]); // distribute & collect

// MSD法
SqList *MSD(SqList *SL, int order[]);

// 输入无效提示语句
void InvalidInput();

// 判断优先级是否正确
int isOrderValid(int order[]);

// 获取优先级
void GetOrder(int order[]);

// 初始化链表
LinkedList *InitLinkedList(LinkedList *LL);

// 向链表结尾添加结点
LinkedList *AddLinkedList(LinkedList *LL, RcdType r);

// 初始化顺序表
SqList *InitSqList(SqList *SL);

// 向顺序表结尾添加结点
SqList *AddSqList(SqList *SL, RcdType r);

// 打印顺序表中的排序结果
void PrintSqList(SqList *SL);

// 打印链表中的排序结果
void PrintLinkedList(LinkedList *LL);

// compare: 存放比较次数
// move: 存放移动次数

unsigned long LSDStable_compare;
unsigned long LSDStable_move;

unsigned long LSDDistr_compare;
unsigned long LSDDistr_move;

unsigned long MSD_compare;
unsigned long MSD_move;