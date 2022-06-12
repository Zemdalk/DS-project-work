#include "NationalTrafficConsult.h"

int GetDurationTime(Time t1, Time t2){
    // ���������Ļ�������д�������������ʱ��
    //t1 ��ʼʱ��  t2 ����ʱ��   
    //����ֵΪ������
    int duration;
    duration=(t2.hour-t1.hour)*60+(t2.minute-t1.minute);
    if(duration<0)
        duration+=24*60;//����
    return duration;
}

CityMap *EditTrain(CityMap *CMap){
    // ���̣�(�û�������ܲ��Ϸ�����������Ч�����������룡��)
    // ������Ҫִ�еĲ�����1/2��
    // 1. ��ӳ���
    // 2. ɾ������
    // ��������ʼվ
    // �������յ�վ
    // ���������ʱ��
    // �����뵽��ʱ��
    // ������Ʊ��
    // ------���ݵ�һ�����ʵ����ݣ���ת��AddTrain()��DelTrain()
    int choice;//1�������,2����ɾ��
    while(1){
        printf("��ѡ����Ҫִ�еĲ���(1/2)\n");
        printf("1.��ӳ���\n");
        printf("2.ɾ������\n");
        scanf("%d",&choice);//�����û��������ֺ��谴�س���
        if(choice==1 || choice==2)
            break;
        else
            InvalidInputs();
            getchar();
    }
    getchar();

    if(choice==1){
        char departure[MAX_STR_LEN];
        printf("��������ʼվ\n");
        scanf("%s",departure);
        getchar();

        char terminal[MAX_STR_LEN];
        printf("�������յ�վ\n");
        scanf("%s",terminal);
        getchar();

        Time start_time;
        while(1){
            printf("���������ʱ��(ʱ���ʽΪxx�� xx)\n");
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
            printf("�����뵽��ʱ��(ʱ���ʽΪxx�� xx)\n");
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
            printf("������Ʊ��\n");
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
        printf("��������Ҫɾ���ĳ��εı��\n");
        char number[MAX_STR_LEN];
        scanf("%s",number);
        getchar();
        DelTrain(CMap,number);
    return CMap;
}

CityMap *AddTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    CMap->edgenum++;
    int depvertex;//ʼ�����ڱ�ͷ�����е����
    for(depvertex=0;depvertex<CMap->vexnum;depvertex++){
        if(strcmp(departure,CMap->v[depvertex].city)==0)
            break;
    }
    int tervertex;//������ڱ�ͷ�����е����
    for(tervertex=0;tervertex<CMap->vexnum;tervertex++){
        if(strcmp(terminal,CMap->v[tervertex].city)==0)
            break;
    }

    int addvex;
    if(depvertex!=CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=1;//ʼ�����뵽��ؾ�ԭ���Ѵ���
    else if(depvertex!=CMap->vexnum && tervertex==CMap->vexnum)
        addvex=2;//ʼ����ԭ�����ڣ������ԭ����������Ҫ�½�
    else if(depvertex==CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=3;//ʼ����ԭ����������Ҫ�½��������ԭ������
    else
        addvex=4;//ʼ�����뵽��ؾ�ԭ����������Ҫ�½�
    
    switch (addvex){
        case 1:{
            NodeLink *p=CMap->v[depvertex].first;
            while(p && p->vindex!=tervertex && p->next!=NULL)
                p=p->next;
            if(p==NULL || (p->next==NULL && p->vindex!=tervertex)){
                //�������ط�ԭ��û�бߣ���Ҫ�½���·(�ڵ�)
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
                //�������ط�ԭ���б�
                int totalnum;//��Ҫȷ���������ط�ԭ���ж���������·
                int num=1;//��Ҫȷ���������ط�ԭ���м�������·
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
            NodeLink *p=CMap->v[depvertex].first;//һ�����½�һ���ڵ�
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
    /*int depvertex;//ʼ�����ڱ�ͷ�����е����
    for(depvertex=0;depvertex<CMap->vexnum;depvertex++){
        if(strcmp(departure,CMap->v[depvertex].city)==0)
            break;
    }
    int tervertex;//������ڱ�ͷ�����е����
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
    // ���̣�(�û�������ܲ��Ϸ�����������Ч�����������룡��)
    // ������Ҫִ�еĲ�����1/2��
    // 1. ��Ӻ���
    // 2. ɾ������
    // ��������ʼվ
    // �������յ�վ
    // ���������ʱ��
    // �����뵽��ʱ��
    // ������Ʊ��
    // ------���ݵ�һ�����ʵ����ݣ���ת��AddFlight()��DelFlight()
    int choice;//1�������,2����ɾ��
    while(1){
        printf("��ѡ����Ҫִ�еĲ���(1/2)\n");
        printf("1.��Ӻ���\n");
        printf("2.ɾ������\n");
        scanf("%d",&choice);//�����û��������ֺ��谴�س���
        if(choice==1 || choice==2)
            break;
        else
            InvalidInputs();
            getchar();
    }
    getchar();

    if(choice==1){
        char departure[MAX_STR_LEN];
        printf("��������ʼվ\n");
        scanf("%s",departure);
        getchar();

        char terminal[MAX_STR_LEN];
        printf("�������յ�վ\n");
        scanf("%s",terminal);
        getchar();

        Time start_time;
        while(1){
            printf("���������ʱ��(ʱ���ʽΪxx�� xx)\n");
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
            printf("�����뵽��ʱ��(ʱ���ʽΪxx�� xx)\n");
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
            printf("������Ʊ��\n");
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
        printf("��������Ҫɾ���ĺ���ı��\n");
        char number[MAX_STR_LEN];
        scanf("%s",number);
        getchar();
        DelFlight(CMap,number);
    return CMap;
}

CityMap *AddFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    CMap->edgenum++;
    int depvertex;//ʼ�����ڱ�ͷ�����е����
    for(depvertex=0;depvertex<CMap->vexnum;depvertex++){
        if(strcmp(departure,CMap->v[depvertex].city)==0)
            break;
    }
    int tervertex;//������ڱ�ͷ�����е����
    for(tervertex=0;tervertex<CMap->vexnum;tervertex++){
        if(strcmp(terminal,CMap->v[tervertex].city)==0)
            break;
    }

    int addvex;
    if(depvertex!=CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=1;//ʼ�����뵽��ؾ�ԭ���Ѵ���
    else if(depvertex!=CMap->vexnum && tervertex==CMap->vexnum)
        addvex=2;//ʼ����ԭ�����ڣ������ԭ����������Ҫ�½�
    else if(depvertex==CMap->vexnum && tervertex!=CMap->vexnum)
        addvex=3;//ʼ����ԭ����������Ҫ�½��������ԭ������
    else
        addvex=4;//ʼ�����뵽��ؾ�ԭ����������Ҫ�½�
    
    switch (addvex){
        case 1:{
            NodeLink *p=CMap->v[depvertex].first;
            while(p && p->vindex!=tervertex && p->next!=NULL)
                p=p->next;
            if(p==NULL || (p->next==NULL && p->vindex!=tervertex)){
                //�������ط�ԭ��û�бߣ���Ҫ�½���·(�ڵ�)
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
                //�������ط�ԭ���б�
                int totalnum;//��Ҫȷ���������ط�ԭ���ж���������·
                int num=1;//��Ҫȷ���������ط�ԭ���м����ɻ���·
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
            NodeLink *p=CMap->v[depvertex].first;//һ�����½�һ���ڵ�
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
    printf("������Ч�����������룡\n");
    return;
}

void NotFoundT(void){
    printf("�ó��β����ڣ��޷�ɾ���������²�����\n");
    return;
}

void NotFoundF(void){
    printf("�ú��಻���ڣ��޷�ɾ���������²�����\n");
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