# 题目

暂略

可以阅读教材7.6节 最短路径（P186）。

详细的数据结构和各主要函数已经在头文件[NationalTrafficConsult.c](NationalTrafficConsult.c)中实现。

# 数据结构

- 时间的规整格式 `Time`
- 城市交通图 `CityMap`
  - 邻接表，和PPT上讲的基本一样
- 列车时刻表 `TrainTable`
  - 单链表
- 飞机航班表 `TrainTable`
  - 单链表

# 功能

![Flowchart](Flowchart.png)

## 执行流程

- 选择功能 `main()`
  - 显示列车时刻表 `ShowTrainTable()`
  - 显示飞机航班表 `ShowFlightTable()`
  - 编辑城市信息   `EditCity()`
    - 新增城市 `AddCity()`
    - 删除城市 `DelCity()`
    - 新增路线 `AddRoute()`
    - 删除路线 `DelRoute()`
  - 编辑列车时刻表 `EditTrain()`
    - 添加列车车次 `AddTrain()`
    - 删除列车车次 `DelTrain()`
  - 编辑飞机航班表 `EditFlight()`
    - 添加飞机航班 `AddFlight()`
    - 删除飞机航班 `DelFlight()`
  - 进行路线规划   `Decision()`
    - 最省时决策      `LeastDurationTime()`
    - 最省钱决策      `LeastCost()`
    - 中转次数最少决策 `LeastExchange()`

# 相关文件

除了代码之外，还应该有

- CityMap.txt，保存城市交通图
- TrainTable.txt，保存列车时刻表
- FlightTable.txt，保存飞机航班图

# 其它

- 输入：对交通图、列车时刻表和飞机航班表的编辑，提供两种输入方式，键盘输入和文件输入。