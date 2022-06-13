#include "SortByMultipleKeywords.h"

LinkedList *Distribute(LinkedList *LL, LinkedList *subLL, int i);
LinkedList *Collect(LinkedList *LL, LinkedList *subLL);

LinkedList *LSDDistr(LinkedList *LL, int order[]){
    int i, j;
    LinkedList *subLL = (LinkedList *)malloc((BOUNDARY+1) * sizeof(LinkedList));
    for(i=0; i<=BOUNDARY; i++) subLL[i].next=NULL;
    for(i=NUM_KEY-1; i>=0; i--){
        LL = Distribute(LL, subLL, order[i]);
        LL = Collect(LL, subLL);
        for(j=0; j<=BOUNDARY; j++) (&(subLL[j]))->next=NULL;
    }
    return LL;
}

LinkedList *Distribute(LinkedList *LL, LinkedList *subLL, int i){
    LinkedList *p=LL->next;     // 待分配
    int curKey;
    while(p){
        curKey = p->rcd.key[i];
        LinkedList *q=&subLL[curKey];
        while(q->next) q=q->next;   // 找到插入位置
        LL->next=p->next;
        p->next=NULL;               // 从LL中摘出p
        q->next=p;
        p=LL->next;
    }
    return LL;
}

LinkedList *Collect(LinkedList *LL, LinkedList *subLL){
    int i;
    LinkedList *p=LL;
    for(i=BOUNDARY; i>=0; i--){
        p->next=(&subLL[i])->next;
        while(p->next) p=p->next;
    }
    return LL;
}