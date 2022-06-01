#include "NationalTrafficConsult.h"
CityMap *TestData();

int main(){
    // ����д���ÿ��Ļ�ӭ���棬��Ҫ��������Ϣ
    char TTable[MAX_STR_LEN] = "TrainTable.txt";
    char FTable[MAX_STR_LEN] = "FlightTable.txt";

    // next few lines are used for test
    CityMap *CMap = TestData();                 // ʹ�ò�������
    SetMap(CMap, TTable, FTable);               // �������ļ�
    // CityMap *CMap = GetMap(TTable, FTable);  // ���ļ��г�ʼ����ͨͼ

    while(1){
        printf("��ѡ���ܣ�(1: ��ʾ�г�ʱ�̱�  2: ��ʾ�ɻ������  3: �༭�г�ʱ�̱�  4: �༭�ɻ������  5: ����·�߹滮)\n");
        int func;
        scanf("%d",&func);
        getchar();
        switch (func){
            case 1:
                ShowTrainTable(CMap, TTable);
                break;
            case 2:
                ShowFlightTable(CMap, FTable);
                break;
            case 3:
                // CMap = EditTrain(CMap);
                break;
            case 4:
                // CMap = EditFlight(CMap);
                break;
            case 5:
                // Decision(CMap);
                break;
            default:
                printf("������Ч�����������룡\n");
                func=0;
                continue;
        }
        printf("���Ƿ�Ҫ������(Y: ���� N: �˳�)\n");
        char c = getchar();
        getchar();
        if(c=='N') break;
    }
}

CityMap *TestData(){
    CityMap *CMap=(CityMap *)malloc(sizeof(CityMap));
    CMap->vexnum=3;
    CMap->edgenum=6;
    strncpy(CMap->v[0].city, "����", MAX_STR_LEN);
    strncpy(CMap->v[1].city, "�Ϻ�", MAX_STR_LEN);
    strncpy(CMap->v[2].city, "��³ľ��", MAX_STR_LEN);
    Time t;
    NodeLink *p, *q;

    p = malloc(sizeof(NodeLink));
    p->vindex=1;
    // ���� -> �Ϻ�����
    p->info[0].tag=0;
    t.hour=10;
    t.minute=0;
    p->info[0].start_time=t;
    t.hour=15;
    t.minute=0;
    p->info[0].end_time=t;
    p->info[0].cost=350;
    p->info[0].duration=GetDurationTime(p->info[0].start_time, p->info[0].end_time);
    strncpy(p->info[0].number, "T000101", 8);
    CMap->v[0].first=p;
    // ���� -> �Ϻ����ɻ�
    p->info[1].tag=1;
    t.hour=10;
    t.minute=0;
    p->info[1].start_time=t;
    t.hour=12;
    t.minute=0;
    p->info[1].end_time=t;
    p->info[1].cost=550;
    p->info[1].duration=GetDurationTime(p->info[1].start_time, p->info[1].end_time);
    strncpy(p->info[1].number, "F000101", 8);
    p->info[2].tag=-1;
    q=p;

    // ���� -> ��³ľ�룬��
    q->next = p = malloc(sizeof(NodeLink));
    p->vindex=2;
    p->info[0].tag=0;
    t.hour=10;
    t.minute=0;
    p->info[0].start_time=t;
    t.hour=19;
    t.minute=0;
    p->info[0].end_time=t;
    p->info[0].cost=750;
    p->info[0].duration=GetDurationTime(p->info[0].start_time, p->info[0].end_time);
    strncpy(p->info[0].number, "T000201", 8);
    p->info[1].tag=-1;
    q=p;
    q->next=NULL;

    p = malloc(sizeof(NodeLink));
    p->vindex=0;
    // �Ϻ� -> ��������
    p->info[0].tag=0;
    t.hour=11;
    t.minute=0;
    p->info[0].start_time=t;
    t.hour=16;
    t.minute=0;
    p->info[0].end_time=t;
    p->info[0].cost=350.50;
    p->info[0].duration=GetDurationTime(p->info[0].start_time, p->info[0].end_time);
    strncpy(p->info[0].number, "T010001", 8);
    CMap->v[1].first = p;
    // �Ϻ� -> �������ɻ�
    p->info[1].tag=1;
    t.hour=11;
    t.minute=0;
    p->info[1].start_time=t;
    t.hour=13;
    t.minute=0;
    p->info[1].end_time=t;
    p->info[1].cost=550.72;
    p->info[1].duration=GetDurationTime(p->info[1].start_time, p->info[1].end_time);
    strncpy(p->info[1].number, "F010001", 8);
    p->info[2].tag=-1;
    q=p;
    p->next=NULL;

    // ��³ľ�� -> �Ϻ����ɻ�
    CMap->v[2].first = p = malloc(sizeof(NodeLink));
    p->vindex=1;
    p->info[0].tag=1;
    t.hour=13;
    t.minute=0;
    p->info[0].start_time=t;
    t.hour=23;
    t.minute=30;
    p->info[0].end_time=t;
    p->info[0].cost=860;
    p->info[0].duration=GetDurationTime(p->info[0].start_time, p->info[0].end_time);
    strncpy(p->info[0].number, "F020101", 8);
    p->info[1].tag=-1;
    q=p;
    p->next=NULL;

    return CMap;
}
