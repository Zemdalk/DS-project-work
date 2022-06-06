#include "NationalTrafficConsult.h"
//CityMap *TestData();

int main(){
    // 这里写个好看的欢迎界面，还要有作者信息
    char TTable[MAX_STR_LEN] = "TrainTable.txt";
    char FTable[MAX_STR_LEN] = "FlightTable.txt";

    // next few lines are used for test (noted by lxy)
    // CityMap *CMap = TestData();                 // 使用测试数据TestData.c

    // next line is used for release file (noted by lxy)
    CityMap *CMap = GetMap(TTable, FTable);  // 从文件中初始化交通图

    while(1){
        SetMap(CMap, TTable, FTable);
        printf("请选择功能：(1: 显示列车时刻表  2: 显示飞机航班表  3: 编辑列车时刻表  4: 编辑飞机航班表  5: 进行路线规划)\n");
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
                CMap = EditTrain(CMap);
                break;
            case 4:
                CMap = EditFlight(CMap);
                break;
            case 5:
                // Decision(CMap);
                break;
            default:
                printf("输入无效，请重新输入！\n");
                func=0;
                continue;
        }
        printf("您是否要继续？(Y: 继续 N: 退出)\n");
        char c = getchar();
        getchar();
        if(c=='N') break;
    }
}