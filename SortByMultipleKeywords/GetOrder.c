#include "SortByMultipleKeywords.h"

void GetOrder(int order[]){
    printf("请指出关键字的优先级关系：\n");
    printf("说明：共有4个关键字，分别为1、2、3、4，输入格式：K1 K2 K3 K4\n");
    printf("例：1 3 4 2\n");
    
    int flag=0;
    do{
        char c;
        int i;
        for(i=0;i<NUM_KEY;i++){
            scanf("%d", order+i);
            order[i]--;

            // is input format valid?
            c=getchar();
            if( !((c==' ' && i!=(NUM_KEY-1)) || (c=='\n' && i==(NUM_KEY-1)))){
                InvalidInput();
                flag=1;
                while(c!='\n' && getchar()!='\n') ;
                break;
            }else{
                flag=0;
            }
        }
        if(flag==1) continue;
        if(isOrderValid(order)){
            flag=0;
        }else{
            InvalidInput();
            while(c!='\n' && getchar()!='\n') ;
            flag=1;
        }
    }while(flag == 1);
}

void InvalidInput(){
    printf("输入无效，请重新输入！\n");
}

int isOrderValid(int order[]){
    int i, j;
    for(i=0;i<NUM_KEY;i++){
        if(order[i]<0 || order[i]>3){
            return 0;
        }
        for(j=0;j<i;j++){
            if(order[i]==order[j]) return 0;
        }
    }
    return 1;
}