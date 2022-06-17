#include "SortByMultipleKeywords.h"


/*SqList *MSD(SqList *SL, int order[]){
    int key_num,i,j;
    for(i=0;i<NUM_KEY;i++){
        key_num=order[i];
        Qsort(SL,1,SL->length,key_num);
        for(j=1;j<=SL->length;j++){
           SL->rcd[j].ord=j;
        }
        printf("--------------------------\n");
        PrintSqList(SL);
        printf("--------------------------\n");
    }
    RcdSqType temp;
    for(i=1,j=SL->length;i<j;i++,j--){
        temp=SL->rcd[i];
        SL->rcd[i]=SL->rcd[j];
        SL->rcd[j]=temp;
    }
    return SL;
}*/




int MSDcompare(RcdSqType r1, RcdSqType r2, int order[]){
    //权值从大到小，比较两个数据，若大于返回1，若等于返回0，若小于等于返回-1
    int i=0;
    while(i<NUM_KEY && r1.data.key[order[i]]==r2.data.key[order[i]])
        i++;
    if(i==NUM_KEY)
        return 0;
    else{
        if(r1.data.key[order[i]]>r2.data.key[order[i]])
            return 1;
        else
            return -1;
    }
}

int MSDPartition(SqList *SL,int low,int high, int order[]){
    SL->rcd[0]=SL->rcd[low];
    int pivotord=SL->rcd[low].ord;
    while(low<high){
        while(low<high && (MSDcompare(SL->rcd[high],SL->rcd[0],order)==1 || (MSDcompare(SL->rcd[high],SL->rcd[0],order)==0 && SL->rcd[high].ord>=pivotord)))
        --high;
        SL->rcd[low]=SL->rcd[high];
        while(low<high && (MSDcompare(SL->rcd[low],SL->rcd[0],order)==-1 || (MSDcompare(SL->rcd[low],SL->rcd[0],order)==0 && SL->rcd[low].ord<=pivotord)))
        ++low;
        SL->rcd[high]=SL->rcd[low];
    }
    SL->rcd[low]=SL->rcd[0];
    return low;
}

void MSDQsort(SqList *SL,int low, int high, int order[]){
    if(low<high){
        int pivotloc=MSDPartition(SL,low,high, order);
        MSDQsort(SL,low,pivotloc-1,order);
        MSDQsort(SL,pivotloc+1,high,order);
    }
}

SqList *MSD(SqList *SL, int order[]){
    MSDQsort(SL,1,SL->length, order);
    RcdSqType temp;
    int i,j;
    for(i=1,j=SL->length;i<j;i++,j--){
        temp=SL->rcd[i];
        SL->rcd[i]=SL->rcd[j];
        SL->rcd[j]=temp;
    }
    return SL;
}