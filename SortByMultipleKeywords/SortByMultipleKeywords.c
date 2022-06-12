#include "SortByMultipleKeywords.h"

int main(){
    time_t t;
    srand( (unsigned) time(&t));

    // 习题要求是，关键字排序应当由用户指定优先级关系，因此我设立了order数组
    // order数组中按照优先级从大到小存储0，1，2，3四个关键字
    int order[4];
    GetOrder(order);

    // 由随机数生成测试数据
    // 发现随机数在子函数里面生成会出现问题……于是就委曲求全在main函数里实现了
    int i, j;
    RcdType r;
    SqList *SL=(SqList *)malloc(sizeof(SqList));
    LinkedList *LL=(LinkedList *)malloc(sizeof(LinkedList));
    LL = InitLinkedList(LL);
    SL = InitSqList(SL);
    for(i=0;i<NUM_RCD;i++){
        for(j=0; j<4; j++){
            r.key[j]=rand() % (BOUNDARY + 1);
        }
        LL = AddLinkedList(LL, r);
        SL = AddSqList(SL, r);
    }

    // 进入算法
    SqList *SL1=SL, *SL2=SL;
    // SL1 = LSDStable(SL1, order);
    // SL2 = MSD(SL2, order);
    // LL  = LSDDistr(LL, order);

    // 把其中一个计算结果打印出来即可
    printf("排序结果：\n");
    // PrintLinkedList(LL);
    PrintSqList(SL);
    // PrintSqList(SL2);

    system("pause");
}