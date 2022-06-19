#include "NationalTrafficConsult.h"
//CityMap *TestData();

int main(){
    // 这里写个好看的欢迎界面，还要有作者信息
    printf("----------------------------------------------------------欢迎使用升级版12306--------------------------------------------------------\n");
    printf("\t\t\t\t\t\t开发人员：吕星宇、胡康、赵昱杰\n");
    printf("如果您还不熟悉本程序，请先查阅说明手册\n");
    printf("希望本程序能为您的出行提供便利\n");
    printf("祝您平安出行，旅途愉快!\n");

    printf("\n");
    
    char TTable[MAX_STR_LEN] = "TrainTable.txt";
    char FTable[MAX_STR_LEN] = "FlightTable.txt";

    // next few lines are used for test (noted by lxy)
    // CityMap *CMap = TestData();                 // 使用测试数据TestData.c

    // next line is used for release file (noted by lxy)
    CityMap *CMap = GetMap(TTable, FTable);  // 从文件中初始化交通图

    //用户界面展示
    

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
                Decision(CMap);
                break;
            default:
                InvalidInputs();
                func=0;
                continue;
        }
        printf("您是否要继续？(Y: 继续 N: 退出)\n");
        char c = getchar();
        getchar();
        if(c=='N') break;
    }
}