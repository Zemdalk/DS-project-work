#include "NationalTrafficConsult.h"

int main(){
    // 这里写个好看的欢迎界面，还要有作者信息
    
    FILE *CM = fopen("CityMap.txt", "r+");
    FILE *TT = fopen("TrainTable.txt", "r+");
    FILE *FT = fopen("FlightTable.txt", "r+");
    CityMap     *CMap   =GetCityMap(CM);
    TrainTable  *TTable =GetTrainTable(TT);
    FlightTable *FTable =GetFlightTable(FT);
    while(1){
        printf("请选择功能：(1: 显示列车时刻表  2: 显示飞机航班表  3: 编辑城市信息  4: 编辑列车时刻表  5: 编辑飞机航班表  6: 进行路线规划)\n");
        int func;
        scanf("%d",&func);
        getchar();
        switch (func){
            case 1:
                ShowTrainTable(TTable);
                break;
            case 2:
                ShowFlightTable(FTable);
                break;
            case 3:
                EditCity(CMap);
                break;
            case 4:
                EditTrain(TTable);
                break;
            case 5:
                EditFlight(FTable);
                break;
            case 6:
                Decision(CMap, TTable, FTable);
                break;
            default:
                printf("输入无效，请重新输入！\n");
                func=0;
                continue;
        }
        printf("您是否要继续？(Y: 继续 N: 退出)\n");
        char c=getchar();
        getchar();
        if(c=='N') break;
    }
}
