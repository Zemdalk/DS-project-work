#include "NationalTrafficConsult.h"
#define INFINITY 100000

void Decision(CityMap *CMap){
    int transportation;

    printf("����������ʹ�õĽ�ͨ����(0:�� 1:�ɻ�)\n");
    while (1){
        scanf("%d",&transportation);
        if(transportation==0 || transportation==1) break;
        printf("������Ч,����������\n");
    }
    
    char departure[MAX_STR_LEN],terminal[MAX_STR_LEN];
    printf("������������\n");
    scanf("%s",departure);
    printf("����������յ�\n");
    scanf("%s",terminal);

    printf("��������Ƽ���·��\n");
    printf("����ʱ����̵�·��:\n");
    LeastDurationTime(CMap,departure,terminal,transportation);
    printf("�������ٵ�·��:\n");
    LeastCost(CMap,departure,terminal,transportation);
    printf("��ת�������ٵ�·��:\n");
    LeastExchange(CMap,departure,terminal,transportation);

    // ���̣�(�û�������ܲ��Ϸ�����������Ч�����������룡��)
    // �����뽻ͨ����
    // ��������ʼվ
    // �������յ�վ
    // ���θ������־��߷�ʽ���Ƽ�·�ߡ��������費��Ҫѡ���֣��Ҿ��ÿ���ֱ�Ӱ����ֶ���������
}



/*----------------------������������ʱ�䡢���ٻ��ѡ�������ת�ĺ���������Dijkstra�㷨----------------------------------*/
typedef struct route{
    int dep,ter;
    Info information;
}Elemtype;

int* MinWeight;//��¼��㵽���ߵ����Ȩ�ء�
int* final;//��¼�����Ƿ������S����
Elemtype* RouteRecord;//��¼��㵽ÿ������·�������һ�γ�/�ɻ���

//�ж��Ƿ���������յ��Ƿ����S����
int IsEnding(int* final,CityMap* CMap,int ter_index){
    if(final[ter_index]==1) return 1;
    return 0;
}

//ѡ�����е��������Ȩ�ؾ�����С�ĵ����S����
int AddVex_To_S(CityMap* CMap,int* final,int* MinWeight){
    int min=INFINITY;
    int i,w;
    w=0;
    for(i=0;i<CMap->vexnum;i++){
        if(!final[i] && MinWeight[i]<min){
            min=MinWeight[i];
            w=i;
        }
    }
    final[w]=1;
    return w;
}

int AddVex_To_S_double(CityMap* CMap,int* final,double* MinWeight){
    double min=INFINITY;
    int i,w;
    w=0;
    for(i=0;i<CMap->vexnum;i++){
        if(!final[i] && MinWeight[i]<min){
            min=MinWeight[i];
            w=i;
        }
    }
    final[w]=1;
    return w;
}

//�ҵ����ж�Ӧ�����ֱ��
int FoundIndex(CityMap *CMap, char departure[]){
    //ͨ�����������ַ��������ڽӱ����ҵ����ж�Ӧ��������ţ������ء�
    int i;
    for(i=0;i<CMap->vexnum && strcmp(departure,CMap->v[i].city)!=0;i++);
    return i;
}



//��ӡ���·��
void Print_Route(CityMap* CMap,Elemtype* Route_Record,int ter_index,int dep_index){
    //��Ҫ��һ�������ĺ�����
    //������Ҫ�õ�ջ
    //�Ȱѱ�ͷ��ӡ����
    int i;
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    for(i=0;i<34;i++) printf(" ");
    printf("�Ƽ�·��");
    for(i=0;i<34;i++) printf(" ");
    printf("\n");
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    printf("����    ");
    printf("ʼ��վ");
    for(i=0;i<10;i++) printf(" ");
    printf("�յ�վ");
    for(i=0;i<9;i++) printf(" ");
    printf("����ʱ�� ");
    printf("����ʱ�� ");
    printf("ʱ��(����)  ");
    printf("Ʊ��(Ԫ)");
    printf("\n");
    Elemtype* PrintLink;
    PrintLink=(Elemtype*)malloc(CMap->vexnum*sizeof(Elemtype));
    int length=0;
    for(i=ter_index;i!=dep_index;i=Route_Record[i].dep){
        PrintLink[length++]=Route_Record[i];
    }
    for(i=length-1;i>=0;i--){
        PrintLine(PrintLink[i].information,CMap->v[PrintLink[i].dep].city,CMap->v[PrintLink[i].ter].city,stdout);
    }

}

//���ʱ�����
void LeastDurationTime(CityMap *CMap, char departure[], char terminal[], int transportation){
    MinWeight=(int*)malloc(CMap->vexnum*sizeof(int));
    final=(int*)malloc(CMap->vexnum*sizeof(int));
    RouteRecord=(Elemtype*)malloc(CMap->vexnum*sizeof(Elemtype));
    int dep_index,ter_index;
    dep_index=FoundIndex(CMap,departure);
    ter_index=FoundIndex(CMap,terminal);
    int i;
    for(i=0;i<CMap->vexnum;i++){
        final[i]=0;
        MinWeight[i]=INFINITY;
    }
    MinWeight[dep_index]=0;
    final[dep_index]=1;
    Elemtype min_route;
    NodeLink* visit;
    int min;
    min_route.dep=dep_index;
    for(visit=CMap->v[dep_index].first;visit;visit=visit->next){
        min_route.ter=visit->vindex;
        min=INFINITY;
        for(i=0;visit->info[i].tag!=-1;i++){
            if(visit->info[i].tag==transportation && GetDurationTime(visit->info[i].start_time,visit->info[i].end_time)<min){
                min=GetDurationTime(visit->info[i].start_time,visit->info[i].end_time);
                min_route.information=visit->info[i];
            }
        }
        MinWeight[visit->vindex]=min;
        RouteRecord[visit->vindex]=min_route;
    }
    int w=AddVex_To_S(CMap,final,MinWeight); 
    while(!IsEnding(final,CMap,ter_index)){
        min_route.dep=w;
        for(visit=CMap->v[w].first;visit;visit=visit->next){
            if(!final[visit->vindex]){
                for(i=0;visit->info[i].tag!=-1;i++){
                    if(visit->info[i].tag==transportation && MinWeight[visit->vindex]>(MinWeight[w]+GetDurationTime(visit->info[i].start_time,visit->info[i].end_time)+GetDurationTime(RouteRecord[w].information.end_time,visit->info[i].start_time))){
                        MinWeight[visit->vindex]=MinWeight[w]+GetDurationTime(visit->info[i].start_time,visit->info[i].end_time)+GetDurationTime(RouteRecord[w].information.end_time,visit->info[i].start_time);
                        min_route.ter=visit->vindex;
                        min_route.information=visit->info[i];
                        RouteRecord[visit->vindex]=min_route;                    
                    }   
                }
            }
        }
        w=AddVex_To_S(CMap,final,MinWeight);
    }
    Print_Route(CMap,RouteRecord,ter_index,dep_index);
    return;
}

//��ͼ۸����
void LeastCost(CityMap *CMap, char departure[], char terminal[], int transportation){
    double* MinWeight;
    MinWeight=(double*)malloc(CMap->vexnum*sizeof(double));
    final=(int*)malloc(CMap->vexnum*sizeof(int));
    RouteRecord=(Elemtype*)malloc(CMap->vexnum*sizeof(Elemtype));
    int dep_index,ter_index;
    dep_index=FoundIndex(CMap,departure);
    ter_index=FoundIndex(CMap,terminal);
    int i;
    for(i=0;i<CMap->vexnum;i++){
        final[i]=0;
        MinWeight[i]=INFINITY;
    }
    MinWeight[dep_index]=0;
    final[dep_index]=1;
    Elemtype min_route;
    NodeLink* visit;
    int w=dep_index;
    while(!IsEnding(final,CMap,ter_index)){
        min_route.dep=w;
        for(visit=CMap->v[w].first;visit;visit=visit->next){
            if(!final[visit->vindex]){
                for(i=0;visit->info[i].tag!=-1;i++){
                    if(visit->info[i].tag==transportation && MinWeight[visit->vindex]>(MinWeight[w]+visit->info[i].cost)){
                        MinWeight[visit->vindex]=MinWeight[w]+visit->info[i].cost;
                        min_route.ter=visit->vindex;
                        min_route.information=visit->info[i];
                        RouteRecord[visit->vindex]=min_route;                    
                    }   
                }
            }
        }
        w=AddVex_To_S_double(CMap,final,MinWeight);
    }
    Print_Route(CMap,RouteRecord,ter_index,dep_index);
    return;
}

//������ת��������
void LeastExchange(CityMap *CMap, char* departure, char* terminal, int transportation){
    MinWeight=(int*)malloc(CMap->vexnum*sizeof(int));
    final=(int*)malloc(CMap->vexnum*sizeof(int));
    RouteRecord=(Elemtype*)malloc(CMap->vexnum*sizeof(Elemtype));
    int dep_index,ter_index;
    dep_index=FoundIndex(CMap,departure);
    ter_index=FoundIndex(CMap,terminal);
    int i;
    for(i=0;i<CMap->vexnum;i++){
        final[i]=0;
        MinWeight[i]=INFINITY;
    }
    MinWeight[dep_index]=0;
    final[dep_index]=1;
    Elemtype min_route;
    NodeLink* visit;
    int w=dep_index;
    while(!IsEnding(final,CMap,ter_index)){
        min_route.dep=w;
        for(visit=CMap->v[w].first;visit;visit=visit->next){
            if(!final[visit->vindex]){
                for(i=0;visit->info[i].tag!=-1;i++){
                    if(visit->info[i].tag==transportation && MinWeight[visit->vindex]>(MinWeight[w]+1)){
                        MinWeight[visit->vindex]=MinWeight[w]+1;
                        min_route.ter=visit->vindex;
                        min_route.information=visit->info[i];
                        RouteRecord[visit->vindex]=min_route;                    
                    }   
                }
            }
        }
        w=AddVex_To_S(CMap,final,MinWeight);
    }
    Print_Route(CMap,RouteRecord,ter_index,dep_index);
    return;
}








/*--------------------------------------------����������С��ת�����Ľṹ�����Լ�����--------------------------------------
typedef int Status;
typedef struct route{
    int dep,ter;
    Info information;
}Elemtype;

typedef struct QueueNode{
    Elemtype route;
    struct QueueNode* pior;
    struct QueueNode* next;
}QNode,*PTR_To_QNode;

typedef struct LinkedQueue{
    PTR_To_QNode front;
    PTR_To_QNode rear;
}LinkedQueue, *PTR_To_LQ;

typedef struct sqtack{
    int top;
    ElemType *base;
}SqStack, *PTR_To_SqStack;

Status Init_LQ(PTR_To_LQ s){
    if(!s) return ERROR;
    s->front=(PTR_To_QNode)malloc(sizeof(QNode));
    s->rear=s->front;
    return OK;
}

int IsEmpty_LQ(PTR_To_LQ s){
    if(s->front==s->rear) return 1;
    else return 0;
}

Status EnQueue(PTR_To_LQ s,Elemtype r,PTR_To_QNode p){
    if(!s) return ERROR;
    PTR_To_QNode new;
    new=(PTR_To_QNode)malloc(sizeof(QNode));
    new->next=NULL;
    new->route=r;
    new->pior=p;
    s->rear->next=new;
    s->rear=new;
    return OK;
}

Status GetHead(PTR_To_LQ s, PTR_To_QNode p){
    if(IsEmpty_LQ(s)) return ERROR;
    *p=*(s->front->next);
    s->front->next=s->front->next->next;
    if(!s->front->next) s->rear=s->front;
    return OK;
}

Status Init_SqStack(PTR_To_SqStack s){
    s->base=(ElemType*)malloc(MAXSIZE*sizeof(ElemType));
    if(!s->base) return ERROR;
    s->top=0;
    return OK;
}

Status Push(PTR_To_SqStack s, ElemType r){
    if(!s) return ERROR;
    s->base[s->top++]=r;
    return OK;
}

Status Pop(PTR_To_SqStack s, ElemType* e){
    if(!s) return ERROR;
    s->top--;
    *e=s->base[s->top];
    if(s->top<0) return ERROR;
    return OK;
}
void Print_Route(PTR_To_QNode p){
    PTR_To_SqStack s;
    s=(PTR_To_SqStack)malloc(sizeof(SqStack));
    Init_SqStack(s);
    PTR_To_QNode visit;
    for(visit=p;visit;visit=visit->pior){
        Push(s,visit->route);
    }
    //�����һ����ӡ��ͷ�ĺ���
    Elemtype *e;
    e=(Elemtype *)malloc(sizeof(Elemtype));
    while(s->top){
        Pop(s,e);
        //�����һ����ӡ·�ߵĺ�����
    }
}

void LeastExchange(CityMap *CMap, char* departure, char* terminal, int transportation){
    int dep_index,ter_index;
    //��һ��ʲô������������������Ϊ��Ӧ�ı������ֵ��
    int* Mark;
    Mark=(int*)malloc(CMap->vexnum*sizeof(int));
    int i;
    for(i=0;i<vexnum;i++){
        Mark[i]=0;
    }
    Elemtype r;
    PTR_To_QNode p=NULL;
    PTR_To_LQ s;
    s=(PTR_To_LQ)malloc(sizeof(LinkedQueue));
    Init_LQ(s);
    NodeLink* visit;
    Mark[dep_index]=1;
    for(visit=CMap->v[dep_index].first;visit;visit=visit->next){
        r.dep=dep_index;
        r.ter=visit.vindex;
        Mark[r.ter]=1;
        for(i=0;visit->info[i].tag!=-1;i++){
            if(visit->info[i].tag==transportation){
                r.information=visit->info[i]; 
                EnQueue(s,r,p);
            }
        }
    }
    while(!IsEmpty_LQ(s)){
            p=(PTR_To_QNode)malloc(sizeof(QNode));
            GetHead(s,p);
            if(p->route.ter==ter_index){
                Print_Route(p);
                return;
            }else{
                r.dep=p->route.ter;
                for(visit=CMap->v[r.dep].first;visit;visit=visit->next){
                    if(!Mark[visit->vindex]){
                        r.ter=visit->vindex;
                        Mark[r.ter]=1;
                        for(i=0;visit->info[i].tag!=-1;i++){
                            if(visit->info[i].tag==transportation){
                                r.information=visit->info[i];
                                EnQueue(s,r,p);
                            }
                        }
                    }
                }
            }
    }
}
*/

