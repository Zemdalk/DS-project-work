
#include "SortByMultipleKeywords.h"

int main(){
    time_t t;
    srand( (unsigned) time(&t));

    // 习题要求是，关键字排序应当由用户指定优先级关系，因此我设立了order数组
    // order数组中按照优先级从大到小存储0，1，2，3四个关键字
    int order[NUM_KEY];
    GetOrder(order);

    int func;
    while(1){
        printf("请选择您想要使用的算法：(1/2/3)\n");
        printf("1.LSD分配与收集\n");
        printf("2.LSD稳定的内部排序法\n");
        printf("3.MSD\n");
        scanf("%d",&func);
        if(func==1 || func==2 || func==3)
            break;
        printf("输入无效，请重新输入！\n");
    }
    
    

    // 由随机数生成测试数据
    // 发现随机数在子函数里面生成会出现问题……于是就委曲求全在main函数里实现了
    int i, j;
    RcdType r;
    SqList *SL=(SqList *)malloc(sizeof(SqList));
    LinkedList *LL=(LinkedList *)malloc(sizeof(LinkedList));
    LL = InitLinkedList(LL);
    SL = InitSqList(SL);
    for(i=0;i<NUM_RCD;i++){
        for(j=0; j<NUM_KEY; j++){
            r.key[j]=rand() % (BOUNDARY + 1);
        }
        LL = AddLinkedList(LL, r);
        SL = AddSqList(SL, r, i);
    }
    printf("原始数据：\n");
    PrintSqList(SL);

    SqList *SL1=SL;

    if(func==1){
        LL  = LSDDistr(LL, order);
        printf("排序结果1：\n");
        PrintLinkedList(LL);
    }
    else if(func==2){
        SL= LSDStable(SL1, order);
        printf("排序结果2：\n");
        PrintSqList(SL);
    }
    else{
        SL= MSD(SL1, order);
        printf("排序结果3：\n");
        PrintSqList(SL);
    }
    

    system("pause");
}