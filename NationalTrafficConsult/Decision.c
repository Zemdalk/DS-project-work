#include "NationalTrafficConsult.h"
#define INFINITY 100000
#define MAX 100

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
    getchar();

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
    //��ӡ��ͷ
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
    printf("\n");

}

//������ʱ����㷨����˼���ǣ�����㷢����ÿһ����·���յ���ΪԴ�㣬��ÿ��Դ��ʹ��Dijkstra�㷨�������������С·����ѡ��ʱ�仨�����ٵġ�

//Dijkstra�����㷨����������ʱ��ĺ�������Ҫ�����á�
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

//���ʱ�����
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


//��ͼ۸����
//����Dijkstra�㷨��ȨֵΪ�۸�
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
//����Dijkstra�㷨��ÿ���ߵ�ȨֵΪ1����ʾ��ת��1�Ρ�
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

/*---------------------------------���һ���뷨----------------------------*/
/*
��δ������ʵ������Ŀ��Ҫ�󣬶��ڲ�ͬ������ܸ�����ȷ�Ľ⣬����Ҳ�Ǳ��˸��ݱ�ѧ����ѧ�����ܸ�������õĽⷨ��
������ε���Ŀ���ǲ�����ȫ��ģ��ʵ�������������μ��ʱ�䡢���ѡ���ת·�������Լ����ͬʱ���Ƿɻ���𳵵�ʹ�õ����ⶼû�н������������
����лͬ��ͬѧ�İ�����
                                                                                2022.6.16
*/
