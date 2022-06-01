#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>         

#define MAX_STR_LEN 500     // �ַ�����󳤶�
#define MAX_VEX_NUM 100     // (���н�ͨ)ͼ����󶥵���Ŀ
#define MAX_INFO 20         // ��󺽰༰����������

// ʱ��Ĺ�����ʽ
typedef struct Time{
    int hour;       // Сʱ��
    int minute;     // ������
} Time;

// ����/������Ϣ
typedef struct Info{
    int tag;                // 0����    1���ɻ�
    char number[8];         // T/Fxxxxxx, ��Ź���T��F�ɻ���010203��ʾ��01�ų��е�02�ų��еĵ�03�˳���/����
    double cost;            // Ʊ�ۣ��淶Ϊ��λС��
    Time start_time;        // ��ʼʱ��
    Time end_time;          // ����ʱ��
    int duration;           // ʱ������λΪ����
} Info;

// ����
typedef struct CityNode{
    int vindex;             // �ý���ڱ�ͷ��������еĳ������
    Info info[MAX_INFO];    // ���˳���/����������Ϣ
    struct CityNode *next;  // �¸����
} NodeLink;

// ���н�ͨͼ���ڽӱ�
typedef struct CityMap{
    int vexnum, edgenum;        // ͼ�Ķ�����������
    struct {
        char city[MAX_STR_LEN]; // ������
        NodeLink *first;        // ��һ���ڽӵ�
    } v[MAX_VEX_NUM];           // �������v[i]
} CityMap;

// ��ȡ����ʱ�̵�ʱ����(t1 < t2, ����ֵ�ĵ�λΪ����)
int GetDurationTime(Time t1, Time t2);

/*
����1��2����ʾʱ�̱�ͺ������lxy��
�ȵ���SetMap��Ȼ���txt�ļ��д�ӡ
FT: FlightTable.txt
TT: TrainTable.txt
*/

// �������ݣ��ѽ�ͨͼ����Ϣ�ֱ𱣴浽TrainTable.txt��FlightTable.txt��
void SetMap(CityMap *CMap, char TTable[], char FTable[]);

// ��ȡ���ݣ������е�TrainTable.txt��FlightTable.txt�е����ݴ洢Ϊһ�Ž�ͨͼ
CityMap *GetMap(char TTable[], char FTable[]);

// ��ʾ�г�ʱ�̱�
void ShowTrainTable(CityMap *CMap, char TTable[]);

// ��ʾ�ɻ������
void ShowFlightTable(CityMap *CMap, char FTable[]);

/* 
����3��4���༭���μ�������Ϣ����hk��
����**����Ҫ**���ļ��������ӿ���̨�ϰ�������淶����ѯ�ʹ���Ա����
*/

// �༭������Ϣ������
CityMap *EditTrain(CityMap *CMap);

// ��ӳ���
CityMap *AddTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// ɾ������
CityMap *DelTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// �༭������Ϣ������
CityMap *EditFlight(CityMap *CMap);

// ��Ӻ���
CityMap *AddFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// ɾ������
CityMap *DelFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

//������Ч������ʾ
void InvalidInputs(void);

/* ����5��Ϊ�˿��ṩ���ž��ߡ���zyj��
�������������ʳ˿;��ߵ������Ϣ������ת��������������֮һ��������������������ʵ�־����㷨
*/

// ����������
void Decision(CityMap *CMap);

// ��ʡʱ����(rule: ���ž���ԭ��   transportation: ��ͨ����)
void LeastDurationTime(CityMap *CMap, char departure[], char terminal[], int transportation);

// ��ʡǮ����(rule: ���ž���ԭ��   transportation: ��ͨ����)
void LeastCost(CityMap *CMap, char departure[], char terminal[], int transportation);

// ��ת�������پ���(rule: ���ž���ԭ��   transportation: ��ͨ����)
void LeastExchange(CityMap *CMap, char departure[], char terminal[], int transportation);