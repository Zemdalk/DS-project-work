#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 500     // 字符串最大长度
#define MAX_VEX_NUM 100     // (城市交通)图中最大顶点数目

// 时间的规整格式
typedef struct Time{
    int hour;       // 小时数
    int minute;     // 分钟数
} Time;

// 表结点
typedef struct CityNode{
    int vindex;             // 该结点在表头结点数组中的城市序号
    struct CityNode *next;  // 下个结点
} NodeLink;

// 城市交通图：正邻接表
typedef struct CityMap{
    int vexnum, edgenum;        // 图的顶点数，边数
    struct {
        char city[MAX_STR_LEN]; // 城市名
        NodeLink *first;        // 第一个邻接点
    } v[MAX_VEX_NUM];
} CityMap;

// 列车时刻表：单链表
typedef struct TrainTable{
    int num;                            // 列车总数，或车次编号
    struct Train{
        char departure[MAX_STR_LEN];    // 始发站
        char terminal[MAX_STR_LEN];     // 终点站
        Time start_time;                // 起始时间
        Time end_time;                  // 到达时间
        int duration_time;              // 路途用时
        double cost;                    // 票价
    } Train;
    struct TrainTable *next;            // 下趟车次
} TrainNode, TrainTable;

// 飞机航班表：单链表
typedef struct FlightTable{
    int num;                            // 航班总数，或航班编号
    struct Flight{
        char departure[MAX_STR_LEN];    // 始发站
        char terminal[MAX_STR_LEN];     // 终点站
        Time start_time;                // 起始时间
        Time end_time;                  // 到达时间
        int duration_time;              // 路途用时
        double cost;                    // 票价
    } Flight;
    struct FlightTable *next;
} FlightNode, FlightTable;              // 下趟航班

// 获取两个时刻的时间间隔(t1 < t2, 返回值的单位为分钟)
int GetDurationTime(Time t1, Time t2);

/* 
setters and getters
- setter: 形如void SetElem(Type *T, FILE *F)，意为把数据结构T中的内容保存到文件F中去
- getter: 形如Type *GetElem(FILE *F)，意为获取文件F中的内容，并转换到Type类型的数据结构，作为返回值
*/

// 获取城市交通图
CityMap *GetCityMap(FILE *CM);

// 获取列车时刻表
TrainTable *GetTrainTable(FILE *TT);

// 获取飞机航班表
FlightTable *GetFlightTable(FILE *FT);

// 保存城市交通图
void SetCityMap(CityMap *CMap, FILE *CM);

// 保存列车时刻表
void SetTrainTable(TrainTable *TTable, FILE *TT);

// 保存飞机航班表
void SetFlightTable(FlightTable *FTable, FILE *FT);

// 核心功能
// 显示列车时刻表
void ShowTrainTable(TrainTable *TTable);

// 显示飞机航班表
void ShowFlightTable(FlightTable *FTable);

// 编辑城市信息
CityMap *EditCity(CityMap *CMap);

// 新增城市
CityMap *AddCity(CityMap *CMap, char city[]);

// 删除城市
CityMap *DelCity(CityMap *CMap, char city[]);

// 新增路线
CityMap *AddRoute(CityMap *CMap, char city1[], char city2[], int weight);

// 删除路线
CityMap *DelRoute(CityMap *CMap, char city1[], char city2[], int weight);

// 编辑列车信息
TrainTable *EditTrain(TrainTable *TTable);

// 添加列车车次
TrainTable *AddTrain(TrainTable *TTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 删除列车车次
TrainTable *DelTrain(TrainTable *TTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 编辑航班信息
FlightTable *EditFlight(FlightTable *FTable);

// 添加飞机航班
FlightTable *AddFlight(FlightTable *FTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 删除飞机航班
FlightTable *DelFlight(FlightTable *FTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 为乘客提供最优决策
void Decision(CityMap *CMap, TrainTable *TTable, FlightTable *FTable);

// 最省时决策(rule: 最优决策原则   transportation: 交通工具)
void LeastDurationTime(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int transportation);

// 最省钱决策(rule: 最优决策原则   transportation: 交通工具)
void LeastCost(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int transportation);

// 中转次数最少决策(rule: 最优决策原则   transportation: 交通工具)
void LeastExchange(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int transportation);