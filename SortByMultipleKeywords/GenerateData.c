#include "SortByMultipleKeywords.h"

LinkedList *InitLinkedList(LinkedList *LL){
    LL->next=NULL;
    return LL;
}

LinkedList *AddLinkedList(LinkedList *LL, RcdType r){
    LinkedList *p=LL;
    while(p->next!=NULL) p=p->next;
    LinkedList *q=(LinkedList *)malloc(sizeof(LinkedList));
    q->rcd=r;
    q->next=p->next;
    p->next=q;
    return LL;
}

SqList *InitSqList(SqList *SL){
    SL->length=0;
    return SL;
}

SqList *AddSqList(SqList *SL, RcdType r){
    SL->rcd[++SL->length]=r;
    return SL;
}

void PrintLinkedList(LinkedList *LL){
    LinkedList *p=LL->next;
    int i;
    RcdType r;
    while(p!=NULL){
        r=p->rcd;
        for(i=0;i<4;i++){
            printf("%d\t", r.key[i]);
        }
        p=p->next;
        printf("\n");
    }
}

void PrintSqList(SqList *SL){
    SqList *p=SL;
    int i, j;
    RcdType r;
    for(i=1; i <= SL->length ; i++){
        r=SL->rcd[i];
        for(j=0; j<4; j++){
            printf("%d\t", r.key[j]);
        }
        printf("\n");
    }
}