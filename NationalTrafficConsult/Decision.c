#include "NationalTrafficConsult.h"
#define INFINITY 100000

void Decision(CityMap *CMap){
    int transportation;

    printf("请输入你想使用的交通工具(0:火车 1:飞机)\n");
    while (1){
        scanf("%d",&transportation);
        if(transportation==0 || transportation==1) break;
        printf("输入无效,请重新输入\n");
    }
    
    char departure[MAX_STR_LEN],terminal[MAX_STR_LEN];
    printf("请输入你的起点\n");
    scanf("%s",departure);
    printf("请输入你的终点\n");
    scanf("%s",terminal);

    printf("下面给出推荐的路线\n");
    printf("乘坐时间最短的路线:\n");
    LeastDurationTime(CMap,departure,terminal,transportation);
    printf("花费最少的路线:\n");
    LeastCost(CMap,departure,terminal,transportation);
    printf("中转次数最少的路线:\n");
    LeastExchange(CMap,departure,terminal,transportation);

    // 流程：(用户输入可能不合法，“输入无效，请重新输入！”)
    // 请输入交通工具
    // 请输入起始站
    // 请输入终点站
    // 依次给出三种决策方式的推荐路线。（这里需不需要选哪种，我觉得可以直接把三种都给出来吗）
}



/*----------------------下面是求最少时间、最少花费、最少中转的函数，采用Dijkstra算法----------------------------------*/
typedef struct route{
    int dep,ter;
    Info information;
}Elemtype;

int* MinWeight;//记录起点到各边的最短权重。
int* final;//记录定点是否加入了S集。
Elemtype* RouteRecord;//记录起点到每点的最短路径的最后一次车/飞机。

//判断是否结束，及终点是否加如S集。
int IsEnding(int* final,CityMap* CMap,int ter_index){
    if(final[ter_index]==1) return 1;
    return 0;
}

//选择所有点中与起点权重距离最小的点加入S集。
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

//找到城市对应的数字编号
int FoundIndex(CityMap *CMap, char departure[]){
    //通过城市名的字符串，在邻接表中找到城市对应的整数编号，并返回。
    int i;
    for(i=0;i<CMap->vexnum && strcmp(departure,CMap->v[i].city)!=0;i++);
    return i;
}



//打印最短路径
void Print_Route(CityMap* CMap,Elemtype* Route_Record,int ter_index,int dep_index){
    //需要调一下其他的函数。
    //可能需要用到栈
    //先把表头打印出来
    int i;
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    for(i=0;i<34;i++) printf(" ");
    printf("推荐路线");
    for(i=0;i<34;i++) printf(" ");
    printf("\n");
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    printf("车次    ");
    printf("始发站");
    for(i=0;i<10;i++) printf(" ");
    printf("终到站");
    for(i=0;i<9;i++) printf(" ");
    printf("出发时间 ");
    printf("到达时间 ");
    printf("时长(分钟)  ");
    printf("票价(元)");
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

//最短时间决策
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

//最低价格决策
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

//最少中转次数决策
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








/*--------------------------------------------下面是求最小中转次数的结构定义以及函数--------------------------------------
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
    //这里加一个打印表头的函数
    Elemtype *e;
    e=(Elemtype *)malloc(sizeof(Elemtype));
    while(s->top){
        Pop(s,e);
        //这里加一个打印路线的函数。
    }
}

void LeastExchange(CityMap *CMap, char* departure, char* terminal, int transportation){
    int dep_index,ter_index;
    //用一个什么函数把这两个变量赋为相应的表里面的值。
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

