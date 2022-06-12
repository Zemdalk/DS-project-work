#include "NationalTrafficConsult.h"

int GetDurationTime(Time t1, Time t2){
    // 你如果乐意的话，可以写这个函数来返回时长
    //t1 起始时间  t2 结束时间   
    //返回值为分钟数
    int duration;
    duration=(t2.hour-t1.hour)*60+(t2.minute-t1.minute);
    if(duration<0)
        duration+=24*60;//隔天
    return duration;
}

CityMap *EditTrain(CityMap *CMap){
    // 流程：(用户输入可能不合法，“输入无效，请重新输入！”)
    // 请问您要执行的操作（1/2）
    // 1. 添加车次
    // 2. 删除车次
    // 请输入起始站
    // 请输入终点站
    // 请输入出发时间
    // 请输入到达时间
    // 请输入票价
    // ------根据第一次提问的内容，跳转到AddTrain()或DelTrain()
    int choice;//1代表添加,2代表删除
    while(1){
        printf("请选择您要执行的操作(1/2)\n");
        printf("1.添加车次\n");
        printf("2.删除车次\n");
        scanf("%d",&choice);//假设用户输入数字后需按回车键
        if(choice==1 || choice==2)
            break;
        else
            InvalidInputs();
            getchar();
    }
    getchar();

    if(choice==1){
        char departure[MAX_STR_LEN];
        printf("请输入起始站\n");
        scanf("%s",departure);
        getchar();

        char terminal[MAX_STR_LEN];
        printf("请输入终点站\n");
        scanf("%s",terminal);
        getchar();

        Time start_time;
        while(1){
            printf("请输入出发时间(时间格式为xx： xx)\n");
            char sh1,sh2,c1,c2,sm1,sm2;
            scanf("%c%c%c%c %c%c",&sh1,&sh2,&c1,&c2,&sm1,&sm2);
            char c=getchar();
            start_time.hour = (sh1-'0')*10+(sh2-'0');
            start_time.minute = (sm1-'0')*10+(sm2-'0');
            if(start_time.hour>=0 && start_time.hour<24 && start_time.minute>=0 && start_time.minute<60)
                break;
            else
                InvalidInputs();
        }

        Time end_time;
        while(1){
            printf("请输入到达时间(时间格式为xx： xx)\n");
            char eh1,eh2,c3,c4,em1,em2;
            scanf("%c%c%c%c %c%c",&eh1,&eh2,&c3,&c4,&em1,&em2);
            getchar();
            end_time.hour = (eh1-'0')*10+(eh2-'0');
            end_time.minute = (em1-'0')*10+(em2-'0');
            if(end_time.hour>=0 && end_time.hour<24 && end_time.minute>=0 && end_time.minute<60)
                break;
            else
                InvalidInputs();
        }

        char cost_str[MAX_STR_LEN];
        double cost;
        while(1){
            printf("请输入票价\n");
            scanf("%s",cost_str);
            getchar();
            int i;
            for(i=0;cost_str[i]!='\0';i++){
                if((cost_str[i]<'0' || cost_str[i]>'9') && cost_str[i]!='.')
                    break;
            }
            if(cost_str[i]=='\0'){
                cost=atof(cost_str);
                break;
            }
            else
                InvalidInputs();
        }
        AddTrain(CMap,departure,terminal,start_time,end_time,cost);
        return CMap;
    }
    else if(choice==2)
        printf("请输入您要删除的车次的编号\n");
        char number[MAX_STR_LEN];
        scanf("%s",number);
        getchar();
        DelTrain(CMap,number);
    return CMap;
}

CityMap *AddTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    CMap->edgenum++;
    int depvertex;//始发地在表头数组中的序号
    for(depvertex=0;depvertex<CMap->vexnum;depvertex++){
        if(strcmp(departure,CMap->v[depvertex].city)==0)
            break;
    }
    int tervertex;//到达地在表头数组中的序号
    for(tervertex=0;tervertex<CMap->vexnum;tervertex++){
        if(strcmp(terminal,CMap->v[tervertex].city)==0)
            break;
    }

    int addvex;
    if(depvertex!=CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=1;//始发地与到达地均原本已存在
    else if(depvertex!=CMap->vexnum && tervertex==CMap->vexnum)
        addvex=2;//始发地原本存在，到达地原本不存在需要新建
    else if(depvertex==CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=3;//始发地原本不存在需要新建，到达地原本存在
    else
        addvex=4;//始发地与到达地均原本不存在需要新建
    
    switch (addvex){
        case 1:{
            NodeLink *p=CMap->v[depvertex].first;
            while(p && p->vindex!=tervertex && p->next!=NULL)
                p=p->next;
            if(p==NULL || (p->next==NULL && p->vindex!=tervertex)){
                //这两个地方原本没有边，需要新建线路(节点)
                NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
                q->vindex=tervertex;
                q->info[0].tag=0;
                q->info[1].tag=-1;
                CreateNumber(q->info[0].number,0,depvertex,tervertex,1);
                q->info[0].cost=cost;
                q->info[0].start_time=start_time;
                q->info[0].end_time=end_time;
                q->info[0].duration=GetDurationTime(start_time,end_time);
                if(p==NULL){
                    q->next=NULL;
                    CMap->v[depvertex].first=q;
                }
                else{
                    q->next=p->next;
                    p->next=q;
                }
            }
            else{
                //这两个地方原本有边
                int totalnum;//需要确定这两个地方原来有多少条总线路
                int num=1;//需要确定这两个地方原来有几条火车线路
                for(totalnum=0;p->info[totalnum].tag!=-1;totalnum++)
                    if(p->info[totalnum].tag==0)
                        num++;
                p->info[totalnum].tag=0;
                p->info[totalnum+1].tag=-1;
                CreateNumber(p->info[totalnum].number,0,depvertex,tervertex,num);
                p->info[totalnum].cost=cost;
                p->info[totalnum].start_time=start_time;
                p->info[totalnum].end_time=end_time;
                p->info[totalnum].duration=GetDurationTime(start_time,end_time);
            }
            break;
        }
        case 2:{
            strcpy(CMap->v[tervertex].city,terminal);
            CMap->v[tervertex].first=NULL;
            CMap->vexnum++;
            NodeLink *p=CMap->v[depvertex].first;//一定是新建一个节点
            while(p && p->next!=NULL)
                p=p->next;
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            q->vindex=tervertex;
            q->info[0].tag=0;
            q->info[1].tag=-1;
            CreateNumber(q->info[0].number,0,depvertex,tervertex,1);
            q->info[0].cost=cost;
            q->info[0].start_time=start_time;
            q->info[0].end_time=end_time;
            q->info[0].duration=GetDurationTime(start_time,end_time);
            if(p==NULL){
                CMap->v[depvertex].first=q;
                q->next=NULL;
            }
            else{
                q->next=p->next;
                p->next=q;
            }
            break;
        }
        case 3:{
            strcpy(CMap->v[depvertex].city,departure);
            CMap->v[depvertex].first=NULL;
            CMap->vexnum++;
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            q->vindex=tervertex;
            q->info[0].tag=0;
            q->info[1].tag=-1;
            CreateNumber(q->info[0].number,0,depvertex,tervertex,1);
            q->info[0].cost=cost;
            q->info[0].start_time=start_time;
            q->info[0].end_time=end_time;
            q->info[0].duration=GetDurationTime(start_time,end_time);
            q->next=NULL;
            CMap->v[depvertex].first=q;
            break;
        }
        case 4:{
            strcpy(CMap->v[depvertex].city,departure);
            CMap->v[depvertex].first=NULL;
            CMap->vexnum++;
            tervertex=CMap->vexnum;
            strcpy(CMap->v[tervertex].city,terminal);
            CMap->v[tervertex].first=NULL;
            CMap->vexnum++;
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            q->vindex=tervertex;
            q->info[0].tag=0;
            q->info[1].tag=-1;
            CreateNumber(q->info[0].number,0,depvertex,tervertex,1);
            q->info[0].cost=cost;
            q->info[0].start_time=start_time;
            q->info[0].end_time=end_time;
            q->info[0].duration=GetDurationTime(start_time,end_time);
            q->next=NULL;
            CMap->v[depvertex].first=q;
            break;
        }
        default:
            break;
    }
    return CMap;
}

CityMap *DelTrain(CityMap *CMap, char number[]){
    /*int depvertex;//始发地在表头数组中的序号
    for(depvertex=0;depvertex<CMap->vexnum;depvertex++){
        if(strcmp(departure,CMap->v[depvertex].city)==0)
            break;
    }
    int tervertex;//到达地在表头数组中的序号
    for(tervertex=0;tervertex<CMap->vexnum;tervertex++){
        if(strcmp(terminal,CMap->v[tervertex].city)==0)
            break;
    }
    if(depvertex==CMap->vexnum || tervertex==CMap->vexnum){
        NotFoundT();
        return CMap;
    }

    NodeLink *p=CMap->v[depvertex].first;
    while(p->vindex!=tervertex && p->next!=NULL)
        p=p->next;
    if(p->vindex!=tervertex && p->next==NULL){
        NotFoundT();
        return CMap;
    }

    int num;
    Info *current=p->info;
    for(num=0;current[num].tag!=-1;num++){
        if(current[num].tag==0 && current[num].start_time.hour==start_time.hour \
        && current[num].start_time.minute==start_time.minute \
        && current[num].end_time.hour==end_time.hour \
        && current[num].end_time.minute==end_time.minute && current[num].cost==cost)
            break;
    }
    if(current[num].tag==-1){
        NotFoundT();
        return CMap;
    }

    while(p->info[num+1].tag!=-1){
        p->info[num].tag=p->info[num+1].tag;
        strcpy(p->info[num].number,p->info[num+1].number);
        p->info[num].cost=p->info[num+1].cost;
        p->info[num].start_time.hour=p->info[num+1].start_time.hour;
        p->info[num].start_time.minute=p->info[num+1].start_time.minute;
        p->info[num].end_time.hour=p->info[num+1].end_time.hour;
        p->info[num].end_time.minute=p->info[num+1].end_time.minute;
        p->info[num].cost=p->info[num+1].cost;
        num++;
    }
    p->info[num].tag=-1;
    return CMap;*/
    //original version of DelTrain

    if(number[0]!='T'){
        NotFoundT();
        return CMap;
    }
    int depvertex;
    int tervertex;
    depvertex=(number[1]-'0')*10+(number[2]-'0');
    tervertex=(number[3]-'0')*10+(number[4]-'0');
    if(depvertex>=CMap->vexnum || tervertex>=CMap->vexnum || depvertex==tervertex){
        NotFoundT();
        return CMap;
    }

    NodeLink *p=CMap->v[depvertex].first;
    if(p==NULL){
        NotFoundT();
        return CMap;
    }
    while(p->vindex!=tervertex && p->next!=NULL)
        p=p->next;
    if(p->vindex!=tervertex && p->next==NULL){
        NotFoundT();
        return CMap;
    }

    int num=0;
    while(p->info[num].tag!=-1){
        if(strcmp(number,p->info[num].number)==0)
            break;
        num++;
    }
    if(p->info[num].tag==-1){
        NotFoundT();
        return CMap;
    }

    while(p->info[num+1].tag!=-1){
        p->info[num].tag=p->info[num+1].tag;
        strcpy(p->info[num].number,p->info[num+1].number);
        strsub(p->info[num].number);
        p->info[num].cost=p->info[num+1].cost;
        p->info[num].start_time.hour=p->info[num+1].start_time.hour;
        p->info[num].start_time.minute=p->info[num+1].start_time.minute;
        p->info[num].end_time.hour=p->info[num+1].end_time.hour;
        p->info[num].end_time.minute=p->info[num+1].end_time.minute;
        p->info[num].cost=p->info[num+1].cost;
        num++;
    }
    p->info[num].tag=-1;
    return CMap;
}

CityMap *EditFlight(CityMap *CMap){
    // 流程：(用户输入可能不合法，“输入无效，请重新输入！”)
    // 请问您要执行的操作（1/2）
    // 1. 添加航班
    // 2. 删除航班
    // 请输入起始站
    // 请输入终点站
    // 请输入出发时间
    // 请输入到达时间
    // 请输入票价
    // ------根据第一次提问的内容，跳转到AddFlight()或DelFlight()
    int choice;//1代表添加,2代表删除
    while(1){
        printf("请选择您要执行的操作(1/2)\n");
        printf("1.添加航班\n");
        printf("2.删除航班\n");
        scanf("%d",&choice);//假设用户输入数字后需按回车键
        if(choice==1 || choice==2)
            break;
        else
            InvalidInputs();
            getchar();
    }
    getchar();

    if(choice==1){
        char departure[MAX_STR_LEN];
        printf("请输入起始站\n");
        scanf("%s",departure);
        getchar();

        char terminal[MAX_STR_LEN];
        printf("请输入终点站\n");
        scanf("%s",terminal);
        getchar();

        Time start_time;
        while(1){
            printf("请输入出发时间(时间格式为xx： xx)\n");
            char sh1,sh2,c1,c2,sm1,sm2;
            scanf("%c%c%c%c %c%c",&sh1,&sh2,&c1,&c2,&sm1,&sm2);
            char c=getchar();
            start_time.hour = (sh1-'0')*10+(sh2-'0');
            start_time.minute = (sm1-'0')*10+(sm2-'0');
            if(start_time.hour>=0 && start_time.hour<24 && start_time.minute>=0 && start_time.minute<60)
                break;
            else
                InvalidInputs();
        }

        Time end_time;
        while(1){
            printf("请输入到达时间(时间格式为xx： xx)\n");
            char eh1,eh2,c3,c4,em1,em2;
            scanf("%c%c%c%c %c%c",&eh1,&eh2,&c3,&c4,&em1,&em2);
            getchar();
            end_time.hour = (eh1-'0')*10+(eh2-'0');
            end_time.minute = (em1-'0')*10+(em2-'0');
            if(end_time.hour>=0 && end_time.hour<24 && end_time.minute>=0 && end_time.minute<60)
                break;
            else
                InvalidInputs();
        }

        char cost_str[MAX_STR_LEN];
        double cost;
        while(1){
            printf("请输入票价\n");
            scanf("%s",cost_str);
            getchar();
            int i;
            for(i=0;cost_str[i]!='\0';i++){
                if((cost_str[i]<'0' || cost_str[i]>'9') && cost_str[i]!='.')
                    break;
            }
            if(cost_str[i]=='\0'){
                cost=atof(cost_str);
                break;
            }
            else
                InvalidInputs();
        }
        AddFlight(CMap,departure,terminal,start_time,end_time,cost);
        return CMap;
    }
    else if(choice==2)
        printf("请输入您要删除的航班的编号\n");
        char number[MAX_STR_LEN];
        scanf("%s",number);
        getchar();
        DelFlight(CMap,number);
    return CMap;
}

CityMap *AddFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    CMap->edgenum++;
    int depvertex;//始发地在表头数组中的序号
    for(depvertex=0;depvertex<CMap->vexnum;depvertex++){
        if(strcmp(departure,CMap->v[depvertex].city)==0)
            break;
    }
    int tervertex;//到达地在表头数组中的序号
    for(tervertex=0;tervertex<CMap->vexnum;tervertex++){
        if(strcmp(terminal,CMap->v[tervertex].city)==0)
            break;
    }

    int addvex;
    if(depvertex!=CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=1;//始发地与到达地均原本已存在
    else if(depvertex!=CMap->vexnum && tervertex==CMap->vexnum)
        addvex=2;//始发地原本存在，到达地原本不存在需要新建
    else if(depvertex==CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=3;//始发地原本不存在需要新建，到达地原本存在
    else
        addvex=4;//始发地与到达地均原本不存在需要新建
    
    switch (addvex){
        case 1:{
            NodeLink *p=CMap->v[depvertex].first;
            while(p && p->vindex!=tervertex && p->next!=NULL)
                p=p->next;
            if(p==NULL || (p->next==NULL && p->vindex!=tervertex)){
                //这两个地方原本没有边，需要新建线路(节点)
                NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
                q->vindex=tervertex;
                q->info[0].tag=1;
                q->info[1].tag=-1;
                CreateNumber(q->info[0].number,1,depvertex,tervertex,1);
                q->info[0].cost=cost;
                q->info[0].start_time=start_time;
                q->info[0].end_time=end_time;
                q->info[0].duration=GetDurationTime(start_time,end_time);
                if(p==NULL){
                    CMap->v[depvertex].first=q;
                    p=q;
                }
                else{
                    q->next=p->next;
                    p->next=q;
                }
            }
            else{
                //这两个地方原本有边
                int totalnum;//需要确定这两个地方原来有多少条总线路
                int num=1;//需要确定这两个地方原来有几条飞机线路
                for(totalnum=0;p->info[totalnum].tag!=-1;totalnum++)
                    if(p->info[totalnum].tag==1)
                        num++;
                p->info[totalnum].tag=1;
                p->info[totalnum+1].tag=-1;
                CreateNumber(p->info[totalnum].number,1,depvertex,tervertex,num);
                p->info[totalnum].cost=cost;
                p->info[totalnum].start_time=start_time;
                p->info[totalnum].end_time=end_time;
                p->info[totalnum].duration=GetDurationTime(start_time,end_time);
            }
            break;
        }
        case 2:{
            strcpy(CMap->v[tervertex].city,terminal);
            CMap->v[tervertex].first=NULL;
            CMap->vexnum++;
            NodeLink *p=CMap->v[depvertex].first;//一定是新建一个节点
            while(p && p->next!=NULL)
                p=p->next;
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            q->vindex=tervertex;
            q->info[0].tag=1;
            q->info[1].tag=-1;
            CreateNumber(q->info[0].number,1,depvertex,tervertex,1);
            q->info[0].cost=cost;
            q->info[0].start_time=start_time;
            q->info[0].end_time=end_time;
            q->info[0].duration=GetDurationTime(start_time,end_time);
            if(p==NULL){
                CMap->v[depvertex].first=q;
                q->next=NULL;
            }
            else{
                q->next=p->next;
                p->next=q;
            }
            break;
        }
        case 3:{
            strcpy(CMap->v[depvertex].city,departure);
            CMap->v[depvertex].first=NULL;
            CMap->vexnum++;
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            q->vindex=tervertex;
            q->info[0].tag=1;
            q->info[1].tag=-1;
            CreateNumber(q->info[0].number,1,depvertex,tervertex,1);
            q->info[0].cost=cost;
            q->info[0].start_time=start_time;
            q->info[0].end_time=end_time;
            q->info[0].duration=GetDurationTime(start_time,end_time);
            q->next=NULL;
            CMap->v[depvertex].first=q;
            break;
        }
        case 4:{
            strcpy(CMap->v[depvertex].city,departure);
            CMap->v[depvertex].first=NULL;
            CMap->vexnum++;
            tervertex=CMap->vexnum;
            strcpy(CMap->v[tervertex].city,terminal);
            CMap->v[tervertex].first=NULL;
            CMap->vexnum++;
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            q->vindex=tervertex;
            q->info[0].tag=1;
            q->info[1].tag=-1;
            CreateNumber(q->info[0].number,1,depvertex,tervertex,1);
            q->info[0].cost=cost;
            q->info[0].start_time=start_time;
            q->info[0].end_time=end_time;
            q->info[0].duration=GetDurationTime(start_time,end_time);
            q->next=NULL;
            CMap->v[depvertex].first=q;
            break;
        }
        default:
            break;
    }
    return CMap;
}

CityMap *DelFlight(CityMap *CMap, char number[]){
    if(number[0]!='F'){
        NotFoundF();
        return CMap;
    }
    int depvertex;
    int tervertex;
    depvertex=(number[1]-'0')*10+(number[2]-'0');
    tervertex=(number[3]-'0')*10+(number[4]-'0');
    if(depvertex>=CMap->vexnum || tervertex>=CMap->vexnum || depvertex==tervertex){
        NotFoundF();
        return CMap;
    }

    NodeLink *p=CMap->v[depvertex].first;
    if(p==NULL){
        NotFoundF();
        return CMap;
    }
    while(p->vindex!=tervertex && p->next!=NULL)
        p=p->next;
    if(p->vindex!=tervertex && p->next==NULL){
        NotFoundF();
        return CMap;
    }

    int num=0;
    while(p->info[num].tag!=-1){
        if(strcmp(number,p->info[num].number)==0)
            break;
        num++;
    }
    if(p->info[num].tag==-1){
        NotFoundF();
        return CMap;
    }

    while(p->info[num+1].tag!=-1){
        p->info[num].tag=p->info[num+1].tag;
        strcpy(p->info[num].number,p->info[num+1].number);
        strsub(p->info[num].number);
        p->info[num].cost=p->info[num+1].cost;
        p->info[num].start_time.hour=p->info[num+1].start_time.hour;
        p->info[num].start_time.minute=p->info[num+1].start_time.minute;
        p->info[num].end_time.hour=p->info[num+1].end_time.hour;
        p->info[num].end_time.minute=p->info[num+1].end_time.minute;
        p->info[num].cost=p->info[num+1].cost;
        num++;
    }
    p->info[num].tag=-1;
    return CMap;
}

void InvalidInputs(void){
    printf("输入无效，请重新输入！\n");
    return;
}

void NotFoundT(void){
    printf("该车次不存在，无法删除，请重新操作！\n");
    return;
}

void NotFoundF(void){
    printf("该航班不存在，无法删除，请重新操作！\n");
    return;
}

void CreateNumber(char number[], int tag, int depvexnum, int tervexnum, int num){
    if(tag==0)
        strcpy(number,"T");
    else if(tag==1)
        strcpy(number,"F");
    char depstr[3];
    char terstr[3];
    char numstr[3];
    numtostr(depvexnum,depstr);
    numtostr(tervexnum,terstr);
    numtostr(num,numstr);
    strcat(number,depstr);
    strcat(number,terstr);
    strcat(number,numstr);
}

void numtostr(int num, char *str){
    if(num<=9){
        str[0]='0';
        str[1]='0'+num;
    }
    else{
        str[0]='0'+num/10;
        str[1]='0'+num%10;
    }
    str[2]='\0';
    return;
}

void strsub(char s[]){
    if(s[6]!='0'){
        s[6]--;
        return;
    }
    else{
        s[6]='9';
        s[5]--;
        return;
    }
}