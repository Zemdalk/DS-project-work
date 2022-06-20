
#include "SortByMultipleKeywords.h"

int main(){
    time_t t;
    srand( (unsigned) time(&t));

    // ϰ��Ҫ���ǣ��ؼ�������Ӧ�����û�ָ�����ȼ���ϵ�������������order����
    // order�����а������ȼ��Ӵ�С�洢0��1��2��3�ĸ��ؼ���
    int order[NUM_KEY];
    GetOrder(order);

    int func;
    while(1){
        printf("��ѡ������Ҫʹ�õ��㷨��(1/2/3)\n");
        printf("1.LSD�������ռ�\n");
        printf("2.LSD�ȶ����ڲ�����\n");
        printf("3.MSD\n");
        scanf("%d",&func);
        if(func==1 || func==2 || func==3)
            break;
        printf("������Ч�����������룡\n");
    }
    
    

    // ����������ɲ�������
    // ������������Ӻ����������ɻ�������⡭�����Ǿ�ί����ȫ��main������ʵ����
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
    printf("ԭʼ���ݣ�\n");
    PrintSqList(SL);

    SqList *SL1=SL;

    if(func==1){
        LL  = LSDDistr(LL, order);
        printf("������1��\n");
        PrintLinkedList(LL);
    }
    else if(func==2){
        SL= LSDStable(SL1, order);
        printf("������2��\n");
        PrintSqList(SL);
    }
    else{
        SL= MSD(SL1, order);
        printf("������3��\n");
        PrintSqList(SL);
    }
    

    system("pause");
}