#include "SortByMultipleKeywords.h"

int main(){
    time_t t;
    srand( (unsigned) time(&t));

    // ϰ��Ҫ���ǣ��ؼ�������Ӧ�����û�ָ�����ȼ���ϵ�������������order����
    // order�����а������ȼ��Ӵ�С�洢0��1��2��3�ĸ��ؼ���
    int order[4];
    GetOrder(order);

    // ����������ɲ�������
    // ������������Ӻ����������ɻ�������⡭�����Ǿ�ί����ȫ��main������ʵ����
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

    // �����㷨
    SqList *SL1=SL, *SL2=SL;
    // SL1 = LSDStable(SL1, order);
    // SL2 = MSD(SL2, order);
    // LL  = LSDDistr(LL, order);

    // ������һ����������ӡ��������
    printf("��������\n");
    // PrintLinkedList(LL);
    PrintSqList(SL);
    // PrintSqList(SL2);

    system("pause");
}