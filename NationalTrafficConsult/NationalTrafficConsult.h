#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>         

#define MAX_STR_LEN 500     // 字符串最大长度
#define MAX_VEX_NUM 100     // (城市交通)图中最大顶点数目
#define MAX_INFO 20         // 最大航班及车次数量和

// 时间的规整格式
typedef struct Time{
    int hour;       // 小时数
    int minute;     // 分钟数
} Time;

// 车次/航班信息
typedef struct Info{
    int tag;                // 0：火车    1：飞机
    char number[8];         // T/Fxxxxxx, 编号规则：T火车F飞机，010203表示从01号城市到02号城市的第03趟车次/航班
    double cost;            // 票价，规范为两位小数
    Time start_time;        // 起始时间
    Time end_time;          // 到达时间
    int duration;           // 时长，单位为分钟
} Info;

// 表结点
typedef struct CityNode{
    int vindex;             // 该结点在表头结点数组中的城市序号
    Info info[MAX_INFO];    // 本趟车次/航班的相关信息
    struct CityNode *next;  // 下个结点
} NodeLink;

// 城市交通图：邻接表
typedef struct CityMap{
    int vexnum, edgenum;        // 图的顶点数，边数
    struct {
        char city[MAX_STR_LEN]; // 城市名
        NodeLink *first;        // 第一个邻接点
    } v[MAX_VEX_NUM];           // 城市序号v[i]
} CityMap;

// 获取两个时刻的时间间隔(t1 < t2, 返回值的单位为分钟)
int GetDurationTime(Time t1, Time t2);

/*
功能1、2：显示时刻表和航班表。（lxy）
先调用SetMap，然后从txt文件中打印
FT: FlightTable.txt
TT: TrainTable.txt
*/

// 保存数据：把交通图的信息分别保存到TrainTable.txt和FlightTable.txt中
void SetMap(CityMap *CMap, char TTable[], char FTable[]);

// 获取数据：把现有的TrainTable.txt和FlightTable.txt中的数据存储为一张交通图
CityMap *GetMap(char TTable[], char FTable[]);

// 显示列车时刻表
void ShowTrainTable(CityMap *CMap, char TTable[]);

// 显示飞机航班表
void ShowFlightTable(CityMap *CMap, char FTable[]);

/* 
功能3、4：编辑车次及航班信息。（hk）
这里**不需要**和文件交互，从控制台上按照输入规范依次询问管理员即可
*/

// 编辑车次信息主函数
CityMap *EditTrain(CityMap *CMap);

// 添加车次
CityMap *AddTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 删除车次
CityMap *DelTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 编辑航班信息主函数
CityMap *EditFlight(CityMap *CMap);

// 添加航班
CityMap *AddFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 删除航班
CityMap *DelFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost);

//输入无效跳出提示
void InvalidInputs(void);

/* 功能5：为乘客提供最优决策。（zyj）
主函数中依次问乘客决策的相关信息，并跳转到后面三个函数之一，下面三个函数才真正实现具体算法
*/

// 决策主函数
void Decision(CityMap *CMap);

// 最省时决策(rule: 最优决策原则   transportation: 交通工具)
void LeastDurationTime(CityMap *CMap, char departure[], char terminal[], int transportation);

// 最省钱决策(rule: 最优决策原则   transportation: 交通工具)
void LeastCost(CityMap *CMap, char departure[], char terminal[], int transportation);

// 中转次数最少决策(rule: 最优决策原则   transportation: 交通工具)
void LeastExchange(CityMap *CMap, char departure[], char terminal[], int transportation);