#include "SortByMultipleKeywords.h"

typedef struct ElemType{
    RcdType data;
    int ord;
}ElemType,*PTR_To_ElemType;
//Ϊ�˼�С�㷨��ʱ�临�Ӷȣ�ѡ���˿��ţ��������ڿ��Ų����ȶ��������������������������һ����ָʾ�������������е�˳�򣬴Ӷ��ﵽ�ȶ��ԡ�

int Partition(PTR_To_ElemType Elem_ptr,int low,int high,int key_num){
    Elem_ptr[0]=Elem_ptr[low];
    int pivotkey=Elem_ptr[low].data.key[key_num];
    int pivotord=Elem_ptr[low].ord;
    while(low<high){
        while(low<high && (Elem_ptr[high].data.key[key_num]>pivotkey || (Elem_ptr[high].data.key[key_num]==pivotkey && Elem_ptr[high].ord>=pivotord)))
        --high;
        Elem_ptr[low]=Elem_ptr[high];
        while(low<high && (Elem_ptr[low].data.key[key_num]<pivotkey || (Elem_ptr[low].data.key[key_num]==pivotkey && Elem_ptr[low].ord<=pivotord)))
        ++low;
        Elem_ptr[high]=Elem_ptr[low];
    }
    Elem_ptr[low]=Elem_ptr[0];
    return low;
}

void Qsort(PTR_To_ElemType Elem_ptr,int low, int high,int key_num){
    if(low<high){
        int pivotloc=Partition(Elem_ptr,low,high,key_num);
        Qsort(Elem_ptr,low,pivotloc-1,key_num);
        Qsort(Elem_ptr,pivotloc+1,high,key_num);
    }
}

SqList *LSDStable(SqList *SL, int order[]){
    PTR_To_ElemType Elem_ptr;
    Elem_ptr=(PTR_To_ElemType)malloc((SL->length+1)*sizeof(ElemType));
    int i;
    for(i=1;i<=SL->length;i++){
        Elem_ptr[i].data=SL->rcd[i];
        Elem_ptr[i].ord=i;
    }
    int key_num,j;
    for(i=3;i>=0;i--){
        key_num=order[i];
        Qsort(Elem_ptr,1,SL->length,key_num);
        for(j=1;j<=SL->length;j++){
           Elem_ptr[j].ord=j;
        }
    }
    for(i=1;i<=SL->length;i++){
        SL->rcd[i]=Elem_ptr[SL->length+1-i].data;
    }
    return SL;
}