# 题目

暂略

可以阅读教材7.6节 最短路径（P186）。

详细的数据结构和各主要函数已经在头文件![NationalTrafficConsult.c](NationalTrafficConsult.c)中实现。

# 数据结构

## 应有信息

- 城市交通图
  - 带权无向图
- 飞机航班表
  - 起始站
  - 起始站出发时间
  - 终点站
  - 终点站到达时间
  - 票价

- 列车时刻表
    需要根据交通图给出各个路段的详细信息。

> 疑问：飞机航班表和列车时刻表有什么不同？为什么要专门指出列车时刻表还要给出各个路段的详细信息？所有航班都是直达吗？

## 存储结构

- 城市交通图
  - 带权无向图，课本P187
  - 邻接表
  - <del>注意，表示边的结点内除含有邻接点的信息外，还应该包括各段的出发时间、到达时间及票价等信息。</del>
- 列车时刻表
  - 单链表
- 飞机航班表
  - 单链表

# 功能

## 功能列表

- 用户界面-功能选择
  <!-- - 显示城市交通图 -->
  - 显示列车时刻表
  - 显示飞机航班表
  - 编辑城市信息
  - 编辑列车时刻表
  - 编辑飞机航班表
  - 进行路线规划

## 函数

下面的代码从![NationalTrafficConsult.c](NationalTrafficConsult.c)头文件中复制而来。

``` c
// 显示城市交通图
void ShowCityMap(CityMap *CMap);

// 显示列车时刻表
void ShowTrainTable(TrainTable *TTable);

// 显示飞机航班表
void ShowFlightTable(FlightTable *FTable);

// 新增城市
// 返回值设为 void 还是 CityMap * 好呢？
CityMap *AddCity(CityMap *CMap, char city[]);

// 删除城市
CityMap *DelCity(CityMap *CMap, char city[]);

// 新增路线
CityMap *AddRoute(CityMap *CMap, char city1[], char city2[], int weight);

// 删除路线
CityMap *DelRoute(CityMap *CMap, char city1[], char city2[]);

// 添加列车车次
TrainTable *AddTrain(TrainTable *TTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 删除列车车次
TrainTable *DelTrain(TrainTable *TTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 添加飞机航班
FlightTable *AddFlight(FlightTable *FTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 删除飞机航班
FlightTable *DelFlight(FlightTable *FTable, char departure[], char terminal[], Time start_time, Time end_time, double cost);

// 为乘客提供最优决策(rule: 最优决策原则   transportation: 交通工具)
void Decision(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int rule, int transportation);

// 最省时决策
void LeastDurationTime(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int transportation);

// 最省钱决策
void LeastCost(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int transportation);

// 中转次数最少决策
void LeastExchange(CityMap *CMap, TrainTable *TTable, FlightTable *FTable, char departure[], char terminal[], int transportation);
```

# 相关文件

除了代码之外，还应该有

- CityMap.txt，保存城市交通图
- TrainTable.txt，保存列车时刻表
- FlightTable.txt，保存飞机航班图

# 其它

- 输入：对交通图、列车时刻表和飞机航班表的编辑，提供两种输入方式，键盘输入和文件输入。