#include "SortByMultipleKeywords.h"


int Partition(SqList *SL,int low,int high,int key_num){
    SL->rcd[0]=SL->rcd[low];
    int pivotkey=SL->rcd[low].data.key[key_num];
    int pivotord=SL->rcd[low].ord;
    while(low<high){
        while(low<high && (SL->rcd[high].data.key[key_num]>pivotkey || (SL->rcd[high].data.key[key_num]==pivotkey && SL->rcd[high].ord>=pivotord)))
        --high;
        SL->rcd[low]=SL->rcd[high];
        while(low<high && (SL->rcd[low].data.key[key_num]<pivotkey || (SL->rcd[low].data.key[key_num]==pivotkey && SL->rcd[low].ord<=pivotord)))
        ++low;
        SL->rcd[high]=SL->rcd[low];
    }
    SL->rcd[low]=SL->rcd[0];
    return low;
}

void Qsort(SqList *SL,int low, int high,int key_num){
    if(low<high){
        int pivotloc=Partition(SL,low,high,key_num);
        Qsort(SL,low,pivotloc-1,key_num);
        Qsort(SL,pivotloc+1,high,key_num);
    }
}

SqList *LSDStable(SqList *SL, int order[]){
    int key_num,i,j;
    for(i=3;i>=0;i--){
        key_num=order[i];
        Qsort(SL,1,SL->length,key_num);
        for(j=1;j<=SL->length;j++){
           SL->rcd[j].ord=j;
        }
    }
    RcdSqType temp;
    for(i=1,j=SL->length;i<j;i++,j--){
        temp=SL->rcd[i];
        SL->rcd[i]=SL->rcd[j];
        SL->rcd[j]=temp;
    }
    return SL;
}