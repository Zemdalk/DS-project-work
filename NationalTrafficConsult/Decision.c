#include "NationalTrafficConsult.h"
#define INFINITY 100000
#define MAX 100

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
    getchar();

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
    //打印表头
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
    printf("\n");

}

//求最少时间的算法核心思想是：将起点发出的每一条线路的终点作为源点，对每个源点使用Dijkstra算法，最后在所有最小路径中选择时间花费最少的。

//Dijkstra核心算法，在求最少时间的函数中需要被调用。
int Dijkstra(int dep_index,int ter_index,int*MinWeight_ptr[],int* final_ptr[],Elemtype* RouteRecord_ptr[],int length,CityMap* CMap,int transportation){
    int least_time=0;
    Elemtype min_route;
    int w=dep_index;
    NodeLink* visit;
    int i;
    while(!IsEnding(final_ptr[length],CMap,ter_index)){
        min_route.dep=w;
        for(visit=CMap->v[w].first;visit;visit=visit->next){
            if(!final_ptr[length][visit->vindex]){
                for(i=0;visit->info[i].tag!=-1;i++){
                    if(visit->info[i].tag==transportation && MinWeight_ptr[length][visit->vindex]>(MinWeight_ptr[length][w]+visit->info[i].duration+GetDurationTime(RouteRecord_ptr[length][w].information.end_time,visit->info[i].start_time))){
                        MinWeight_ptr[length][visit->vindex]=MinWeight_ptr[length][w]+visit->info[i].duration+GetDurationTime(RouteRecord_ptr[length][w].information.end_time,visit->info[i].start_time);
                        min_route.ter=visit->vindex;
                        min_route.information=visit->info[i];
                        RouteRecord_ptr[length][visit->vindex]=min_route;                    
                    }   
                }
            }
        }
        w=AddVex_To_S(CMap,final_ptr[length],MinWeight_ptr[length]);
        least_time=MinWeight_ptr[length][w];
    }
    return least_time;
}

//最短时间决策
void LeastDurationTime(CityMap *CMap, char departure[], char terminal[], int transportation){
    int* MinWeight_ptr[MAX];
    int* final_ptr[MAX];
    Elemtype* RouteRecord_ptr[MAX];
    int mintime[MAX];
    int length=0;
    int dep_index,ter_index;
    dep_index=FoundIndex(CMap,departure);
    ter_index=FoundIndex(CMap,terminal);
    NodeLink* visit;
    Elemtype min_route;
    int i;
    for(visit=CMap->v[dep_index].first;visit;visit=visit->next){
        min_route.dep=dep_index;
        min_route.ter=visit->vindex;
        for(i=0;visit->info[i].tag!=-1;i++){
            if(visit->info[i].tag==transportation){
                min_route.information=visit->info[i];
                MinWeight_ptr[length]=(int*)malloc(CMap->vexnum*sizeof(int));
                final_ptr[length]=(int*)malloc(CMap->vexnum*sizeof(int));
                RouteRecord_ptr[length]=(Elemtype*)malloc(CMap->vexnum*sizeof(Elemtype));
                int j;
                for(j=0;j<CMap->vexnum;j++){
                    final_ptr[length][j]=0;
                    MinWeight_ptr[length][j]=INFINITY;
                }
                MinWeight_ptr[length][dep_index]=0;
                MinWeight_ptr[length][visit->vindex]=visit->info[i].duration;
                final_ptr[length][dep_index]=1;
                final_ptr[length][visit->vindex]=1;
                RouteRecord_ptr[length][visit->vindex]=min_route;
                mintime[length]=Dijkstra(visit->vindex,ter_index,MinWeight_ptr,final_ptr,RouteRecord_ptr,length,CMap,transportation);
                length++;
            }
        }
    }
    int min=INFINITY;
    int m;
    for(i=0;i<length;i++){
        if(mintime[i]<min){
            min=mintime[i];
            m=i;
        }
    }
    Print_Route(CMap,RouteRecord_ptr[m],ter_index,dep_index);
    return;


//最低价格决策
//采用Dijkstra算法，权值为价格
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
//采用Dijkstra算法，每条边的权值为1，表示中转了1次。
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

/*---------------------------------最后一点想法----------------------------*/
/*
这次代码基本实现了题目的要求，对于不同的情况能给出正确的解，并且也是本人根据本学期所学内容能给出的最好的解法。
但是这次的项目还是不能完全地模拟实际情况，比如如何兼顾时间、花费、中转路次数，以及如何同时考虑飞机与火车的使用等问题都没有解决。。。。。
最后感谢同组同学的帮助。
                                                                                2022.6.16
*/
